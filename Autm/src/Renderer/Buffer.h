#ifndef AUTM_BUFFER_H
#define AUTM_BUFFER_H

/**
 * Base class for most things OpenGL, used in VertexBuffer, IndexBuffer and VertexArray
 */
class Buffer {
public:
    Buffer() : m_rendererId(0) {}
    virtual ~Buffer() = default;

    virtual void bind() const = 0;

    virtual void unbind() const = 0;
protected:
    GLuint m_rendererId;
};

#endif
