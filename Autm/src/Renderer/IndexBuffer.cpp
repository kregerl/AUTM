#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(uint32_t *indices, uint32_t count) : m_count(count) {
    glCreateBuffers(1, &m_renderer_id);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_renderer_id);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
