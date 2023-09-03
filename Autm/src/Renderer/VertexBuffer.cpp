#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(float *vertices, uint32_t size) {
    glCreateBuffers(1, &m_renderer_id);

    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(uint32_t size) {
    glCreateBuffers(1, &m_renderer_id);

    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_renderer_id);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
}

void VertexBuffer::set_data(const void* data, uint32_t size) {
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}


