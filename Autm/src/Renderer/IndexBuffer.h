#ifndef AUTM_INDEXBUFFER_H
#define AUTM_INDEXBUFFER_H

#include <glad/glad.h>
#include <cstddef>

#include "Buffer.h"


class IndexBuffer : Buffer {
public:
    IndexBuffer(GLuint *indices, size_t count);

    ~IndexBuffer() override;

    void bind() const override;

    void unbind() const override;

    int getCount() const {return m_count;}
private:
    int m_count;

};


#endif
