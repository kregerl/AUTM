#include "RenderSystem.h"
#include "Core/Log.h"

void RenderSystem::set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    AUTM_CORE_DEBUG("Setting viewport to x={}, y={}, width={}, height={}", x, y, width, height);
    glViewport(x, y, width, height);
}

void RenderSystem::clear_color(glm::vec4 color) {
    clear_color(color.r, color.g, color.b, color.a);
}

void RenderSystem::clear_color(glm::vec3 color) {
    clear_color(color.r, color.g, color.b, 1.0f);
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
    glDrawElements(mode, (GLsizei) count, GL_UNSIGNED_INT, nullptr);
}

void RenderSystem::draw_indexed(const std::shared_ptr<VertexArray> &vertex_array, uint32_t index_count) {
    vertex_array->bind();
    uint32_t count = index_count == 0 ? vertex_array->get_index_buffer()->getCount() : index_count;
    glDrawElements(GL_TRIANGLES, (GLsizei) count, GL_UNSIGNED_INT, nullptr);
}

void RenderSystem::set_line_width(float line_width) {
    glLineWidth(line_width);
}

void RenderSystem::draw_lines(const std::shared_ptr<VertexArray> &vertex_array, uint32_t vertex_count) {
    vertex_array->bind();
    glDrawArrays(GL_LINES, 0, (GLsizei) vertex_count);
}


