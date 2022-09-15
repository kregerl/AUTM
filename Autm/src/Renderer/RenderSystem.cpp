#include "RenderSystem.h"

void RenderSystem::clearColor(glm::vec4 color) {
    clearColor(color.r, color.g, color.b, color.a);
}

void RenderSystem::clearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    clear(GL_COLOR_BUFFER_BIT);
}

void RenderSystem::clear(int mask) {
    glClear(mask);
}

/**
 * Vertex array must be bound before calling draw.
 *
 * @param vertexArray
 * @param mode
 * @param count
 */
void RenderSystem::draw(std::shared_ptr<VertexArray> &vertexArray, GLenum mode, int count) {
    int indexCount = count == 0 ? vertexArray->getIndexBuffer()->getCount() : count;
    glDrawElements(mode, indexCount, GL_UNSIGNED_INT, nullptr);
}