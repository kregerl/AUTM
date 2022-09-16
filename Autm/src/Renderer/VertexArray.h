#ifndef AUTM_VERTEXARRAY_H
#define AUTM_VERTEXARRAY_H

#include "autmpch.h"

#include <glad/glad.h>

#include "Buffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArray : Buffer {
public:
    static GLenum getOpenglType(ShaderDataType type);

    VertexArray();

    void bind() const override;

    void unbind() const override;

    void addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer);

    void setIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer);

    const std::shared_ptr<IndexBuffer> &getIndexBuffer() { return m_indexBuffer; }

private:
    std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
    std::shared_ptr<IndexBuffer> m_indexBuffer;
};


#endif
