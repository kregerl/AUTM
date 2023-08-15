#ifndef AUTM_VERTEXARRAY_H
#define AUTM_VERTEXARRAY_H

#include "autmpch.h"

#include <glad/glad.h>

#include "Buffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArray : Buffer {
public:
    static GLenum get_opengl_type(ShaderDataType type);

    VertexArray();

    void bind() const override;

    void unbind() const override;

    void add_vertex_buffer(const std::shared_ptr<VertexBuffer> &vertex_buffer);

    void set_index_buffer(const std::shared_ptr<IndexBuffer> &index_buffer);

    const std::shared_ptr<IndexBuffer> &get_index_buffer() { return m_index_buffer; }

private:
    std::vector<std::shared_ptr<VertexBuffer>> m_vertex_buffers;
    std::shared_ptr<IndexBuffer> m_index_buffer;
};


#endif
