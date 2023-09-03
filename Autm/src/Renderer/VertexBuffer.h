#ifndef AUTM_VERTEXBUFFER_H
#define AUTM_VERTEXBUFFER_H

#include "Buffer.h"
#include "VertexBufferLayout.h"

class VertexBuffer : Buffer {
public:
    VertexBuffer(float *vertices, uint32_t size);

    explicit VertexBuffer(uint32_t size);

    ~VertexBuffer() override;

    void bind() const override;

    void unbind() const override;

    void set_data(const void* data, uint32_t size = 0);

    void set_layout(const VertexBufferLayout &layout) { m_layout = layout; }

    inline const VertexBufferLayout &get_layout() { return m_layout; }

private:
    VertexBufferLayout m_layout;
};


#endif
