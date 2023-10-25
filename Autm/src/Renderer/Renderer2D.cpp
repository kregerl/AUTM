#include "Renderer2D.h"
#include "RenderSystem.h"
#include "Texture2D.h"
#include "UniformBuffer.h"
#include <ext/matrix_transform.hpp>
#include <Core/Log.h>

static const uint32_t MAX_QUADS = 10000;
static const uint32_t MAX_VERTICES = MAX_QUADS * 4;
static const uint32_t MAX_INDICES = MAX_VERTICES * 6;
static const uint32_t MAX_TEXTURE_SLOTS = 32;
static const float DEFAULT_LINE_WIDTH = 2.0f;

struct QuadVertex {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texture_coordinate;
    float texture_index;
    float tiling_factor;
};

struct LineVertex {
    glm::vec3 position;
    glm::vec4 color;
};

struct CircleVertex {
    glm::vec3 world_position;
    glm::vec3 local_position;
    glm::vec4 color;
    glm::vec2 texture_coordinate;
    float texture_index;
    float tiling_factor;
    float thickness;
    float fade;
};

struct RendererData {
    glm::mat4 view_projection_matrix;

    uint32_t quad_index_count = 0;
    QuadVertex* quad_vertex_buffer_base = nullptr;
    QuadVertex* quad_vertex_buffer_ptr = nullptr;
    std::shared_ptr<VertexArray> quad_vertex_array;
    std::shared_ptr<VertexBuffer> quad_vertex_buffer;
    std::shared_ptr<Shader> textured_quad_shader;

    uint32_t line_vertex_count = 0;
    LineVertex* line_vertex_buffer_base = nullptr;
    LineVertex* line_vertex_buffer_ptr = nullptr;
    std::shared_ptr<VertexArray> line_vertex_array;
    std::shared_ptr<VertexBuffer> line_vertex_buffer;
    std::shared_ptr<Shader> line_shader;

    uint32_t circle_index_count = 0;
    CircleVertex* circle_vertex_buffer_base = nullptr;
    CircleVertex* circle_vertex_buffer_ptr = nullptr;
    std::shared_ptr<VertexArray> circle_vertex_array;
    std::shared_ptr<VertexBuffer> circle_vertex_buffer;
    std::shared_ptr<Shader> circle_shader;

    std::shared_ptr<Texture2D> white_texture;
    std::array<std::shared_ptr<Texture2D>, MAX_TEXTURE_SLOTS> texture_slots;
    uint32_t texture_index = 1;

    glm::vec4 quad_vertex_positions[4];
    std::shared_ptr<UniformBuffer> camera_uniform_buffer;
};


// This has to be heap allocated because static fields last until the end of the program's lifetime,
// meaning the texture's destructor will be called after the OpenGL context is already destroyed.
static RendererData* s_data = new RendererData();

void Renderer2D::init() {
    AUTM_CORE_DEBUG("Thread id: {}", std::this_thread::get_id());

    // Heap allocated to prevent stack overflows
    // TODO: should be ref counted
    auto* quad_indices = new uint32_t[MAX_INDICES];

    // Assigning quad indices
    uint32_t offset = 0;
    for (uint32_t i = 0; i < MAX_INDICES; i += 6) {
        quad_indices[i + 0] = offset + 0;
        quad_indices[i + 1] = offset + 1;
        quad_indices[i + 2] = offset + 2;

        quad_indices[i + 3] = offset + 2;
        quad_indices[i + 4] = offset + 3;
        quad_indices[i + 5] = offset + 0;

        offset += 4;
    }

    std::shared_ptr<IndexBuffer> quad_index_buffer = std::make_shared<IndexBuffer>(quad_indices, MAX_INDICES);

    init_quad(quad_index_buffer);
    init_line();
    init_circle(quad_index_buffer);

    delete[] quad_indices;

    s_data->white_texture = std::make_shared<Texture2D>(1, 1);
    uint32_t white = 0xFFFFFFFF;
    s_data->white_texture->set_data(sizeof(uint32_t), &white);
    s_data->texture_slots[0] = s_data->white_texture;

    s_data->camera_uniform_buffer = std::make_shared<UniformBuffer>(sizeof(glm::mat4), 0);
}

void Renderer2D::shutdown() {
    delete[] s_data->quad_vertex_buffer_base;
    delete[] s_data->line_vertex_buffer_base;
    delete[] s_data->circle_vertex_buffer_base;
    delete s_data;
}

void Renderer2D::begin(OrthographicCamera camera) {
    // Set camera view projection matrix uniform buffer so it can be reused
    s_data->view_projection_matrix = camera.get_view_projection_matrix();
    s_data->camera_uniform_buffer->set_data(&s_data->view_projection_matrix, sizeof(s_data->view_projection_matrix));

    start_batch();
}

void Renderer2D::end() {
    flush();
}

// Zero out the batch
void Renderer2D::start_batch() {
    s_data->quad_index_count = 0;
    s_data->quad_vertex_buffer_ptr = s_data->quad_vertex_buffer_base;

    s_data->line_vertex_count = 0;
    s_data->line_vertex_buffer_ptr = s_data->line_vertex_buffer_base;

    s_data->circle_index_count = 0;
    s_data->circle_vertex_buffer_ptr = s_data->circle_vertex_buffer_base;

    s_data->texture_index = 1;
}

void Renderer2D::flush() {
    // If the renderer should draw any quads
    if (s_data->quad_index_count) {
        auto data_size = (uint32_t) ((uint8_t*) s_data->quad_vertex_buffer_ptr -
                                     (uint8_t*) s_data->quad_vertex_buffer_base);
        s_data->quad_vertex_buffer->set_data(s_data->quad_vertex_buffer_base, data_size);

        for (uint32_t i = 0; i < s_data->texture_index; i++) {
            s_data->texture_slots[i]->bind(i);
        }

        s_data->textured_quad_shader->bind();
        RenderSystem::draw_indexed(s_data->quad_vertex_array, s_data->quad_index_count);
    }

    if (s_data->circle_index_count) {
        auto data_size = (uint32_t) ((uint8_t*) s_data->circle_vertex_buffer_ptr -
                                     (uint8_t*) s_data->circle_vertex_buffer_base);
        s_data->circle_vertex_buffer->set_data(s_data->circle_vertex_buffer_base, data_size);

        for (uint32_t i = 0; i < s_data->texture_index; i++) {
            s_data->texture_slots[i]->bind(i);
        }

        s_data->circle_shader->bind();
        RenderSystem::draw_indexed(s_data->circle_vertex_array, s_data->circle_index_count);
    }

    if (s_data->line_vertex_count) {
        auto data_size = (uint32_t) ((uint8_t*) s_data->line_vertex_buffer_ptr -
                                     (uint8_t*) s_data->line_vertex_buffer_base);
        s_data->line_vertex_buffer->set_data(s_data->line_vertex_buffer_base, data_size);

        s_data->line_shader->bind();
        RenderSystem::set_line_width(DEFAULT_LINE_WIDTH);
        RenderSystem::draw_lines(s_data->line_vertex_array, s_data->line_vertex_count);
    }
}

void Renderer2D::draw_quad(const glm::mat4& transform, const glm::vec4& color) {
    draw_quad(transform, s_data->white_texture, 1.0f, color);
}

void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                          * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    draw_quad(transform, color);
}

void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture,
                           float tiling_factor, const glm::vec4& color) {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                          * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    draw_quad(transform, texture, tiling_factor, color);
}

void Renderer2D::draw_quad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, float tiling_factor,
                           const glm::vec4& color) {
    constexpr uint32_t quad_vertex_count = 4;
    constexpr glm::vec2 texture_coords[] = {{0.0f, 0.0f},
                                            {1.0f, 0.0f},
                                            {1.0f, 1.0f},
                                            {0.0f, 1.0f}};
    float texture_index = determine_texture_index(texture);

    for (uint32_t i = 0; i < quad_vertex_count; i++) {
        s_data->quad_vertex_buffer_ptr->position = transform * s_data->quad_vertex_positions[i];
        s_data->quad_vertex_buffer_ptr->color = color;
        s_data->quad_vertex_buffer_ptr->texture_coordinate = texture_coords[i];
        s_data->quad_vertex_buffer_ptr->texture_index = texture_index;
        s_data->quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
        s_data->quad_vertex_buffer_ptr++;
    }
    s_data->quad_index_count += 6;
}

void Renderer2D::draw_rect(const glm::mat4& transform, const glm::vec4& color) {
    constexpr uint32_t line_vertex_count = 4;
    glm::vec3 line_vertices[line_vertex_count];
    for (uint32_t i = 0; i < line_vertex_count; i++) {
        line_vertices[i] = transform * s_data->quad_vertex_positions[i];
    }

    draw_line(line_vertices[0], line_vertices[1], color);
    draw_line(line_vertices[1], line_vertices[2], color);
    draw_line(line_vertices[2], line_vertices[3], color);
    draw_line(line_vertices[3], line_vertices[0], color);
}

void Renderer2D::draw_rect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                          * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    draw_rect(transform, color);
}

void Renderer2D::draw_line(const glm::vec3& position0, const glm::vec3& position1, const glm::vec4& color) {
    s_data->line_vertex_buffer_ptr->position = position0;
    s_data->line_vertex_buffer_ptr->color = color;
    s_data->line_vertex_buffer_ptr++;

    s_data->line_vertex_buffer_ptr->position = position1;
    s_data->line_vertex_buffer_ptr->color = color;
    s_data->line_vertex_buffer_ptr++;

    s_data->line_vertex_count += 2;
}

void Renderer2D::draw_circle_with_radius(const glm::vec3& position, float radius, const glm::vec4& color) {
    draw_circle(position, glm::vec2(radius * 2), color);
}

void Renderer2D::draw_circle(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color,
                             float tiling_factor, float thickness, float fade) {
    draw_circle(position, size, s_data->white_texture, color, tiling_factor, thickness, fade);
}

void Renderer2D::draw_circle(const glm::vec3& position, const glm::vec2& size,
                             const std::shared_ptr<Texture2D>& texture, const glm::vec4& color, float tiling_factor,
                             float thickness, float fade) {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                          * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    draw_circle(transform, texture, color, tiling_factor, thickness, fade);
}


void Renderer2D::draw_circle(
        const glm::mat4& transform,
        const std::shared_ptr<Texture2D>& texture,
        const glm::vec4& color,
        float tiling_factor,
        float thickness, float fade) {

    constexpr uint32_t circle_vertex_count = 4;
    constexpr glm::vec2 texture_coords[] = {{0.0f, 0.0f},
                                            {1.0f, 0.0f},
                                            {1.0f, 1.0f},
                                            {0.0f, 1.0f}};

    float texture_index = determine_texture_index(texture);

    for (uint32_t i = 0; i < circle_vertex_count; i++) {
        s_data->circle_vertex_buffer_ptr->world_position = transform * s_data->quad_vertex_positions[i];
        s_data->circle_vertex_buffer_ptr->local_position = s_data->quad_vertex_positions[i] * 2.0f;
        s_data->circle_vertex_buffer_ptr->color = color;
        s_data->circle_vertex_buffer_ptr->texture_coordinate = texture_coords[i];
        s_data->circle_vertex_buffer_ptr->texture_index = texture_index;
        s_data->circle_vertex_buffer_ptr->tiling_factor = tiling_factor;
        s_data->circle_vertex_buffer_ptr->thickness = thickness;
        s_data->circle_vertex_buffer_ptr->fade = fade;
        s_data->circle_vertex_buffer_ptr++;
    }
    s_data->circle_index_count += 6;
}

void Renderer2D::draw_circle(const glm::mat4& transform, const glm::vec4& color, float tiling_factor, float thickness,
                             float fade) {
    draw_circle(transform, s_data->white_texture, color, tiling_factor, thickness, fade);
}

void Renderer2D::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray,
                        const glm::mat4& modelMatrix) {
    shader->bind();
    vertexArray->bind();
    RenderSystem::draw(vertexArray);
    vertexArray->unbind();
}

float Renderer2D::determine_texture_index(const std::shared_ptr<Texture2D>& texture) {
    float texture_index = 0.0f;
    for (uint32_t i = 1; i < s_data->texture_index; i++) {
        if (s_data->texture_slots[i].get() == texture.get()) {
            texture_index = (float) i;
            break;
        }
    }

    if (texture_index == 0.0f) {
        texture_index = (float) s_data->texture_index;
        s_data->texture_slots[s_data->texture_index] = texture;
        s_data->texture_index++;
    }
    return texture_index;
}

void Renderer2D::init_quad(const std::shared_ptr<IndexBuffer>& index_buffer) {
    s_data->quad_vertex_array = std::make_shared<VertexArray>();
    s_data->quad_vertex_buffer = std::make_shared<VertexBuffer>(MAX_VERTICES * sizeof(QuadVertex));
    s_data->quad_vertex_buffer->set_layout(
            {
                    {ShaderDataType::Vec3f, "a_position",           false},
                    {ShaderDataType::Vec4f, "a_color",              false},
                    {ShaderDataType::Vec2f, "a_texture_coordinate", false},
                    {ShaderDataType::Float, "a_texture_index",      false},
                    {ShaderDataType::Float, "a_tiling_factor",      false},
            }
    );
    s_data->quad_vertex_array->add_vertex_buffer(s_data->quad_vertex_buffer);
    s_data->quad_vertex_buffer_base = new QuadVertex[MAX_VERTICES];

    s_data->quad_vertex_array->set_index_buffer(index_buffer);

    s_data->textured_quad_shader = std::make_shared<Shader>(
            "/home/loucas/CLionProjects/autm/assets/shaders/core/TexturedQuadVertex.glsl",
            "/home/loucas/CLionProjects/autm/assets/shaders/core/TexturedQuadFragment.glsl");

    s_data->quad_vertex_positions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
    s_data->quad_vertex_positions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
    s_data->quad_vertex_positions[2] = {0.5f, 0.5f, 0.0f, 1.0f};
    s_data->quad_vertex_positions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};
}

void Renderer2D::init_line() {
    s_data->line_vertex_array = std::make_shared<VertexArray>();
    s_data->line_vertex_buffer = std::make_shared<VertexBuffer>(MAX_VERTICES * sizeof(LineVertex));
    s_data->line_vertex_buffer->set_layout(
            {
                    {ShaderDataType::Vec3f, "a_position", false},
                    {ShaderDataType::Vec4f, "a_color",    false},
            });
    s_data->line_vertex_array->add_vertex_buffer(s_data->line_vertex_buffer);
    s_data->line_vertex_buffer_base = new LineVertex[MAX_VERTICES];

    s_data->line_shader = std::make_shared<Shader>(
            "/home/loucas/CLionProjects/autm/assets/shaders/core/LineVertex.glsl",
            "/home/loucas/CLionProjects/autm/assets/shaders/core/LineFragment.glsl");
}

void Renderer2D::init_circle(const std::shared_ptr<IndexBuffer>& index_buffer) {
    s_data->circle_vertex_array = std::make_shared<VertexArray>();
    s_data->circle_vertex_buffer = std::make_shared<VertexBuffer>(MAX_VERTICES * sizeof(CircleVertex));
    s_data->circle_vertex_buffer->set_layout(
            {
                    {ShaderDataType::Vec3f, "a_world_position",     false},
                    {ShaderDataType::Vec3f, "a_local_position",     false},
                    {ShaderDataType::Vec4f, "a_color",              false},
                    {ShaderDataType::Vec2f, "a_texture_coordinate", false},
                    {ShaderDataType::Float, "a_texture_index",      false},
                    {ShaderDataType::Float, "a_tiling_factor",      false},
                    {ShaderDataType::Float, "a_thickness",          false},
                    {ShaderDataType::Float, "a_fade",               false},
            });
    s_data->circle_vertex_array->add_vertex_buffer(s_data->circle_vertex_buffer);
    s_data->circle_vertex_array->set_index_buffer(index_buffer);

    s_data->circle_vertex_buffer_base = new CircleVertex[MAX_VERTICES];

    s_data->circle_shader = std::make_shared<Shader>(
            "/home/loucas/CLionProjects/autm/assets/shaders/core/TexturedCircleVertex.glsl",
            "/home/loucas/CLionProjects/autm/assets/shaders/core/TexturedCircleFragment.glsl");
}


