#include "UniformBuffer.h"
#include <glad/glad.h>

UniformBuffer::UniformBuffer(uint32_t size, uint32_t binding) {
    glCreateBuffers(1, &m_renderer_id);
    glNamedBufferData(m_renderer_id, size, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_renderer_id);
}

UniformBuffer::~UniformBuffer() {
    glDeleteBuffers(1, &m_renderer_id);
}

void UniformBuffer::set_data(const void* data, uint32_t size, uint32_t offset) {
    glNamedBufferSubData(m_renderer_id, offset, size, data);
}


