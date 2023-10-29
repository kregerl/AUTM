#include "Primitives.h"

std::shared_ptr<VertexArray> Primitives::generate_fullscreen_quad(float aspect_ratio, float zoom) {
    float vertices[4 * 5] = {
            -aspect_ratio * zoom, -zoom, 0.0f, 0.0f, 0.0f,
            aspect_ratio * zoom, -zoom, 0.0f, 1.0f, 0.0f,
            aspect_ratio * zoom, zoom, 0.0f, 1.0f, 1.0f,
            -aspect_ratio * zoom, zoom, 0.0f, 0.0f, 1.0f
    };
    uint32_t indices[2 * 3] = {
            0, 1, 3,
            1, 2, 3
    };
    auto vertex_array = std::make_shared<VertexArray>();
    std::shared_ptr<VertexBuffer> vertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
    vertexBuffer->set_layout({
                                     {ShaderDataType::Vec3f, "a_position"},
                                     {ShaderDataType::Vec2f, "a_texture_coordinate"},
                             });
    vertex_array->add_vertex_buffer(vertexBuffer);
    std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(indices,
                                                                             sizeof(indices) / sizeof(uint32_t));
    vertex_array->set_index_buffer(indexBuffer);
    return vertex_array;
}
