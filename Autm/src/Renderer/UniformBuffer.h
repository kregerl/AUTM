#ifndef AUTM_UNIFORMBUFFER_H
#define AUTM_UNIFORMBUFFER_H

#include <glad/glad.h>

class UniformBuffer {
public:
    UniformBuffer(uint32_t size, uint32_t binding);
    ~UniformBuffer();

    void set_data(const void* data, uint32_t size, uint32_t offset = 0);
private:
    GLuint m_renderer_id;
};


#endif //AUTM_UNIFORMBUFFER_H
