#ifndef AUTM_VERTEXBUFFER_H
#define AUTM_VERTEXBUFFER_H

#include <glad/glad.h>

#include "Buffer.h"
#include "VertexBufferLayout.h"

class VertexBuffer : Buffer {
public:
    VertexBuffer(float *vertices, size_t size);

    ~VertexBuffer() override;

    void bind() const override;

    void unbind() const override;

    void setLayout(const VertexBufferLayout &layout) { m_layout = layout; }

    inline const VertexBufferLayout &getLayout() { return m_layout; }

private:
    VertexBufferLayout m_layout;
};


#endif
