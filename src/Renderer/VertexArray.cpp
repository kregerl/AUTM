#include "VertexArray.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_rendererId);
}

void VertexArray::bind() const {
    glBindVertexArray(m_rendererId);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

void VertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) {
    glBindVertexArray(m_rendererId);
    vertexBuffer->bind();

    auto layout = vertexBuffer->getLayout();
    for (int i = 0; i < layout.getElements().size(); i++) {
        const VertexBufferElement element = layout.getElements()[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.getElementCount(), VertexArray::getOpenglType(element.type),
                              element.getNormalized(),
                              layout.getStride(), (void *) element.offset);
    }
    m_vertexBuffers.push_back(vertexBuffer);
}

void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) {
    glBindVertexArray(m_rendererId);
    indexBuffer->bind();
    m_indexBuffer = indexBuffer;
}

GLenum VertexArray::getOpenglType(ShaderDataType type) {
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
    }
}
