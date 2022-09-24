#ifndef AUTM_VERTEXBUFFERLAYOUT_H
#define AUTM_VERTEXBUFFERLAYOUT_H

#include "autmpch.h"

#include <glad/glad.h>

 /**
  * Classes responsible for handling the vertex attribute system
  */
enum class ShaderDataType {
    None = 0, Bool, Int, Vec2i, Vec3i, Vec4i, Float, Vec2f, Vec3f, Vec4f, Mat3, Mat4
};

static unsigned int ShaderDataTypeSize(ShaderDataType type) {
    switch (type) {
        case ShaderDataType::None:
            return 0;
        case ShaderDataType::Bool:
            return 1;
        case ShaderDataType::Int:
            return 4;
        case ShaderDataType::Vec2i:
            return 4 * 2;
        case ShaderDataType::Vec3i:
            return 4 * 3;
        case ShaderDataType::Vec4i:
            return 4 * 4;
        case ShaderDataType::Float:
            return 4;
        case ShaderDataType::Vec2f:
            return 4 * 2;
        case ShaderDataType::Vec3f:
            return 4 * 3;
        case ShaderDataType::Vec4f:
            return 4 * 4;
        case ShaderDataType::Mat3:
            return 4 * 3 * 3;
        case ShaderDataType::Mat4:
            return 4 * 4 * 4;
        default:
            return -1;
    }
}


// TODO: Replace std::strings with std::string_view
struct VertexBufferElement {
    std::string name;
    ShaderDataType type;
    size_t size;
    size_t offset;
    bool normalized;

    VertexBufferElement(ShaderDataType type, std::string name, bool normalized = false)
            : name(std::move(name)), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized) {}

    inline GLenum getNormalized() const { return normalized ? GL_TRUE : GL_FALSE; }

    unsigned int getElementCount() const {
        switch (type) {
            case ShaderDataType::None:
                return 0;
            case ShaderDataType::Bool:
                return 1;
            case ShaderDataType::Int:
                return 1;
            case ShaderDataType::Vec2i:
                return 2;
            case ShaderDataType::Vec3i:
                return 3;
            case ShaderDataType::Vec4i:
                return 4;
            case ShaderDataType::Float:
                return 1;
            case ShaderDataType::Vec2f:
                return 2;
            case ShaderDataType::Vec3f:
                return 3;
            case ShaderDataType::Vec4f:
                return 4;
            case ShaderDataType::Mat3:
                return 3 * 3;
            case ShaderDataType::Mat4:
                return 4 * 4;
            default:
                return -1;
        }
    }
};

class VertexBufferLayout {
public:
    VertexBufferLayout() {}
    VertexBufferLayout(const std::initializer_list<VertexBufferElement> &elements);

    const std::vector<VertexBufferElement> &getElements() const;

    size_t getStride() const;

private:
    void computeStrideAndOffsets();
private:
    std::vector<VertexBufferElement> m_elements;
    size_t m_stride;
};


#endif