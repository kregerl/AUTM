#include "VertexArray.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_renderer_id);
}

void VertexArray::bind() const {
    glBindVertexArray(m_renderer_id);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

void VertexArray::add_vertex_buffer(const std::shared_ptr<VertexBuffer> &vertex_buffer) {
    glBindVertexArray(m_renderer_id);
    vertex_buffer->bind();

    auto layout = vertex_buffer->get_layout();
    for (int i = 0; i < layout.get_elements().size(); i++) {
        const VertexBufferElement element = layout.get_elements()[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.get_element_count(), VertexArray::get_opengl_type(element.type),
                              element.get_normalized(),
                              layout.get_stride(), (void *) element.offset);
    }
    m_vertex_buffers.push_back(vertex_buffer);
}

void VertexArray::set_index_buffer(const std::shared_ptr<IndexBuffer> &index_buffer) {
    glBindVertexArray(m_renderer_id);
    index_buffer->bind();
    m_index_buffer = index_buffer;
}

GLenum VertexArray::get_opengl_type(ShaderDataType type) {
    switch (type) {
        case ShaderDataType::None:
            return GL_NONE;
        case ShaderDataType::Bool:
            return GL_BOOL;
        case ShaderDataType::Int:
            return GL_INT;
        case ShaderDataType::Vec2i:
            return GL_INT;
        case ShaderDataType::Vec3i:
            return GL_INT;
        case ShaderDataType::Vec4i:
            return GL_INT;
        case ShaderDataType::Float:
            return GL_FLOAT;
        case ShaderDataType::Vec2f:
            return GL_FLOAT;
        case ShaderDataType::Vec3f:
            return GL_FLOAT;
        case ShaderDataType::Vec4f:
            return GL_FLOAT;
        case ShaderDataType::Mat3:
            return GL_FLOAT;
        case ShaderDataType::Mat4:
            return GL_FLOAT;
        default:
            return GL_NONE;
    }
}
