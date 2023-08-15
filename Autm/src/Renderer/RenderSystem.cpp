#include "RenderSystem.h"

void RenderSystem::clear_color(glm::vec4 color) {
    clear_color(color.r, color.g, color.b, color.a);
}

void RenderSystem::clear_color(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    clear(GL_COLOR_BUFFER_BIT);
}

void RenderSystem::clear(int mask) {
    glClear(mask);
}

/**
 * Vertex array must be bound before calling draw.
 *
 * @param vertex_array
 * @param mode
 * @param count
 */
void RenderSystem::draw(const std::shared_ptr<VertexArray> &vertex_array, GLenum mode, uint32_t index_count) {
    uint32_t count = index_count == 0 ? vertex_array->get_index_buffer()->getCount() : index_count;
    glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);
}

void RenderSystem::draw_indexed(const std::shared_ptr<VertexArray>& vertex_array, uint32_t index_count) {
    vertex_array->bind();
    uint32_t count = index_count == 0 ? vertex_array->get_index_buffer()->getCount() : index_count;
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

