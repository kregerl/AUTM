#include "Renderer2D.h"
#include "RenderSystem.h"
#include "Texture2D.h"
#include "UniformBuffer.h"

#include <ext/matrix_transform.hpp>
#include <Core/Log.h>

struct QuadVertex {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texture_coordinate;
    float texture_index;
    float tiling_factor;
};

struct RendererData {
    const uint32_t MAX_QUADS = 10000;
    const uint32_t MAX_VERTICES = MAX_QUADS * 4;
    const uint32_t MAX_INDICES = MAX_VERTICES * 6;
    static const uint32_t MAX_TEXTURE_SLOTS = 32;

    uint32_t quad_index_count = 0;
    QuadVertex* quad_vertex_buffer_base = nullptr;
    QuadVertex* quad_vertex_buffer_ptr = nullptr;

    glm::mat4 view_projection_matrix;
    std::shared_ptr<VertexArray> quad_vertex_array;
    std::shared_ptr<VertexBuffer> quad_vertex_buffer;
    std::shared_ptr<Shader> textured_quad_shader;

    std::shared_ptr<Texture2D> white_texture;

    std::array<std::shared_ptr<Texture2D>, MAX_TEXTURE_SLOTS> texture_slots;
    uint32_t texture_index = 1;

    glm::vec4 quad_vertex_positions[4];
    std::shared_ptr<UniformBuffer> camera_uniform_buffer;

    //    std::shared_ptr<VertexArray> lineVertexArray;
//    std::shared_ptr<Shader> textureShader;
//    std::shared_ptr<Shader> flatColorShader;
//    std::shared_ptr<Texture2D> arrowTexture;
//    std::shared_ptr<Texture2D> whiteTexture;
};


// This has to be heap allocated because static fields last until the end of the program's lifetime,
// meaning the texture's destructor will be called after the OpenGL context is already destroyed.
static RendererData* s_data = new RendererData();

void Renderer2D::init() {
    AUTM_CORE_DEBUG("Thread id: {}", std::this_thread::get_id());

    s_data->quad_vertex_array = std::make_shared<VertexArray>();
    s_data->quad_vertex_buffer = std::make_shared<VertexBuffer>(s_data->MAX_VERTICES * sizeof(QuadVertex));
    s_data->quad_vertex_buffer->set_layout(
            {
                    {ShaderDataType::Vec3f, "a_position",          false},
                    {ShaderDataType::Vec4f, "a_color",             false},
                    {ShaderDataType::Vec2f, "a_textureCoordinate", false},
                    {ShaderDataType::Float, "a_textureIndex",      false},
                    {ShaderDataType::Float, "a_tilingFactor",      false},
            }
    );
    s_data->quad_vertex_array->add_vertex_buffer(s_data->quad_vertex_buffer);

    s_data->quad_vertex_buffer_base = new QuadVertex[s_data->MAX_VERTICES];

    // Heap allocated to prevent stack overflows
    // TODO: should be ref counted
    uint32_t* quad_indices = new uint32_t[s_data->MAX_INDICES];

    uint32_t offset = 0;
    for (uint32_t i = 0; i < s_data->MAX_INDICES; i += 6) {
        quad_indices[i + 0] = offset + 0;
        quad_indices[i + 1] = offset + 1;
        quad_indices[i + 2] = offset + 2;

        quad_indices[i + 3] = offset + 2;
        quad_indices[i + 4] = offset + 3;
        quad_indices[i + 5] = offset + 0;

        offset += 4;
    }

    std::shared_ptr<IndexBuffer> quad_index_buffer = std::make_shared<IndexBuffer>(quad_indices, s_data->MAX_INDICES);
    s_data->quad_vertex_array->set_index_buffer(quad_index_buffer);
    delete[] quad_indices;

    s_data->textured_quad_shader = std::make_shared<Shader>(
            "/home/loucas/CLionProjects/Autm/assets/shaders/TexturedQuadVertex.glsl",
            "/home/loucas/CLionProjects/Autm/assets/shaders/TexturedQuadFragment.glsl");
    s_data->white_texture = std::make_shared<Texture2D>(1, 1);
    uint32_t white = 0xFFFFFFFF;
    s_data->white_texture->set_data(sizeof(uint32_t), &white);

    s_data->quad_vertex_positions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
    s_data->quad_vertex_positions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
    s_data->quad_vertex_positions[2] = {0.5f, 0.5f, 0.0f, 1.0f};
    s_data->quad_vertex_positions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};

    s_data->camera_uniform_buffer = std::make_shared<UniformBuffer>(sizeof(glm::mat4), 0);

    s_data->texture_slots[0] = s_data->white_texture;
}

void Renderer2D::shutdown() {
    delete[] s_data->quad_vertex_buffer_base;
    delete s_data;
}

void Renderer2D::begin(OrthographicCamera camera) {
    s_data->view_projection_matrix = camera.get_view_projection_matrix();
    s_data->camera_uniform_buffer->set_data(&s_data->view_projection_matrix, sizeof(s_data->view_projection_matrix));

    s_data->quad_index_count = 0;
    s_data->quad_vertex_buffer_ptr = s_data->quad_vertex_buffer_base;

    s_data->texture_index = 1;
}

void Renderer2D::end() {
    flush();
}

void Renderer2D::flush() {
    if (s_data->quad_index_count) {
        auto dataSize = (uint32_t) ((uint8_t*) s_data->quad_vertex_buffer_ptr -
                                    (uint8_t*) s_data->quad_vertex_buffer_base);
        s_data->quad_vertex_buffer->set_data(s_data->quad_vertex_buffer_base, dataSize);

        for (uint32_t i = 0; i < s_data->texture_index; i++) {
            s_data->texture_slots[i]->bind(i);
        }

        s_data->textured_quad_shader->bind();
        RenderSystem::draw_indexed(s_data->quad_vertex_array, s_data->quad_index_count);
    }
}

void Renderer2D::draw_quad(const glm::mat4& transform, const glm::vec4& color) {
    draw_quad(transform, s_data->white_texture, 1.0f, color);
}

void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
    glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    draw_quad(transform, color);
}

void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture,
                           float tiling_factor, const glm::vec4& color) {
    glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    draw_quad(transform, texture, tiling_factor, color);
}

void Renderer2D::draw_quad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, float tiling_factor,
                           const glm::vec4& color) {
    constexpr size_t quad_vertex_count = 4;
    constexpr glm::vec2 texture_coords[] = {{0.0f, 0.0f},
                                            {1.0f, 0.0f},
                                            {1.0f, 1.0f},
                                            {0.0f, 1.0f}};

    float texture_index = 0.0f;
    for (uint32_t i = 0; i < s_data->texture_index; i++) {
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

    for (size_t i = 0; i < quad_vertex_count; i++) {
        s_data->quad_vertex_buffer_ptr->position = transform * s_data->quad_vertex_positions[i];
        s_data->quad_vertex_buffer_ptr->color = color;
        s_data->quad_vertex_buffer_ptr->texture_coordinate = texture_coords[i];
        s_data->quad_vertex_buffer_ptr->texture_index = texture_index;
        s_data->quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
        s_data->quad_vertex_buffer_ptr++;
    }
    s_data->quad_index_count += 6;
}

void Renderer2D::draw_line(glm::vec3 position, glm::vec2 size, float rotation, float lineWidth) {
//    glm::mat4 modelMatrix = glm::mat4(1.0f);
//    modelMatrix = glm::translate(modelMatrix, position);
//    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
//    modelMatrix = glm::scale(modelMatrix, {size.x, size.y, 1.0f});
//
//    s_data->lineVertexArray->bind();
//    s_data->flatColorShader->bind();
//    s_data->flatColorShader->setMat4("u_viewProjectionMatrix", s_data->viewProjectionMatrix);
//    s_data->flatColorShader->setMat4("u_modelMatrix", modelMatrix);
//
//    glLineWidth(lineWidth);
//    RenderSystem::draw(s_data->lineVertexArray, GL_LINES);
//    s_data->lineVertexArray->unbind();
}

void Renderer2D::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray,
                        const glm::mat4& modelMatrix) {
    shader->bind();
    shader->set_mat4("u_viewProjectionMatrix", s_data->view_projection_matrix);
    shader->set_mat4("u_modelMatrix", modelMatrix);

    vertexArray->bind();
    RenderSystem::draw(vertexArray);
    vertexArray->unbind();
}


