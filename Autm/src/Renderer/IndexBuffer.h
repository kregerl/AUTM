#ifndef AUTM_INDEXBUFFER_H
#define AUTM_INDEXBUFFER_H

#include <glad/glad.h>
#include <cstddef>

#include "Buffer.h"


class IndexBuffer : Buffer {
public:
    IndexBuffer(uint32_t *indices, uint32_t count);

    ~IndexBuffer() override;

    void bind() const override;

    void unbind() const override;

    uint32_t getCount() const {return m_count;}
private:
    uint32_t m_count;

};


#endif
