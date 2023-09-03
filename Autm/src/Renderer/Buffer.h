#ifndef AUTM_BUFFER_H
#define AUTM_BUFFER_H

#include "autmpch.h"

/**
 * Base class for most things OpenGL, used in VertexBuffer, IndexBuffer and VertexArray
 */
class Buffer {
public:
    Buffer() : m_renderer_id(0) {}
    virtual ~Buffer() = default;

    virtual void bind() const = 0;

    virtual void unbind() const = 0;
protected:
    uint32_t m_renderer_id;
};

#endif
