#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(float *vertices, size_t size) {
    glCreateBuffers(1, &m_rendererId);

    glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_rendererId);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
}


