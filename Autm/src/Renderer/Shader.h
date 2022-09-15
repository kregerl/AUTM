#ifndef AUTM_SHADER_H
#define AUTM_SHADER_H

#include "autmpch.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

/**
 * Generic shader class that accepts the standard vertex and fragment shaders, but geometry shaders aswell.
 */
class Shader {
public:
    Shader();

    Shader(std::string_view vertexPath, std::string_view fragmentPath,
           std::string_view geometryPath = "");

    virtual ~Shader();

    void bind() const;

    virtual void setBool(const std::string& name, bool value) const;

    virtual void setInt(const std::string& name, int value) const;

    virtual void setFloat(const std::string& name, float value) const;

    virtual void setVec2(const std::string& name, const glm::vec2& value) const;

    virtual void setVec2(const std::string& name, float x, float y) const;

    virtual void setVec3(const std::string& name, const glm::vec3& value) const;

    virtual void setVec3(const std::string& name, float x, float y, float z) const;

    virtual void setVec4(const std::string& name, const glm::vec4& value) const;

    virtual void setVec4(const std::string& name, float x, float y, float z, float w) const;

    virtual void setMat2(const std::string& name, const glm::mat2& mat) const;

    virtual void setMat3(const std::string& name, const glm::mat3& mat) const;

    virtual void setMat4(const std::string& name, const glm::mat4& mat) const;

protected:
    static void checkCompileErrors(unsigned int shaderProgram, const std::string& type);

protected:
    GLuint m_programId;
};


#endif //AUTM_SHADER_H
