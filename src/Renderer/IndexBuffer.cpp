#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(GLuint *indices, size_t count) : m_count(count) {
    glCreateBuffers(1, &m_rendererId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_rendererId);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
