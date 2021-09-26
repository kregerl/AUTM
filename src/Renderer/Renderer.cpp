#include "Renderer.h"

void Renderer::clearColor(glm::vec4 color) {
    clearColor(color.r, color.g, color.b, color.a);
}

void Renderer::clearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    clear(GL_COLOR_BUFFER_BIT);
}

void Renderer::clear(int mask) {
    glClear(mask);
}

void Renderer::draw(std::shared_ptr<VertexArray> &vertexArray, GLenum mode, int count) {
    int indexCount = count == 0 ? vertexArray->getIndexBuffer()->getCount() : count;
    vertexArray->bind();
    glDrawElements(mode, indexCount, GL_UNSIGNED_INT, nullptr);
}
