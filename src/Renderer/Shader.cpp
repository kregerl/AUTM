#include <gtc/type_ptr.hpp>
#include "Core/Log.h"
#include "Shader.h"

Shader::Shader() : m_programId(0) {}

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
    std::string vertexShader, fragmentShader;
    std::ifstream vertexShaderFile, fragmentShaderFile;

    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);
        std::stringstream vertexStream, fragmentStream;
        vertexStream << vertexShaderFile.rdbuf();
        fragmentStream << fragmentShaderFile.rdbuf();
        vertexShaderFile.close();
        fragmentShaderFile.close();
        vertexShader = vertexStream.str();
        fragmentShader = fragmentStream.str();
    }
    catch (std::ifstream::failure& e) {
        AUTM_CORE_ERROR("Couldn't read shaders at V:{}F:{}", vertexPath, fragmentPath);
    }
    const char* vshCode = vertexShader.c_str();
    const char* fshCode = fragmentShader.c_str();

    //Compile shaders
    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vshCode, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fshCode, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    m_programId = glCreateProgram();
    glAttachShader(m_programId, vertex);
    glAttachShader(m_programId, fragment);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    if (geometryPath) {
        std::string geometryCode;
        std::ifstream gshFile;

        gshFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            gshFile.open(geometryPath);
            std::stringstream gshStream;
            gshStream << gshFile.rdbuf();
            gshFile.close();
            geometryCode = gshStream.str();
        }
        catch (std::ifstream::failure e) {
            AUTM_CORE_ERROR("Couldn't read geometry shader at {}", geometryPath);
        }
        const char* gshCode = geometryCode.c_str();

        unsigned int geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gshCode, nullptr);
        glCompileShader(geometry);
        checkCompileErrors(geometry, "GEOMETRY");
        glAttachShader(m_programId, geometry);
        glDeleteShader(geometry);
    }

    glLinkProgram(m_programId);
    checkCompileErrors(m_programId, "PROGRAM");
}

Shader::~Shader() {
    glDeleteProgram(m_programId);
}
void Shader::bind() const {
    glUseProgram(m_programId);
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(m_programId, name.c_str()), (int) value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(m_programId, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(m_programId, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const {
    glUniform2fv(glGetUniformLocation(m_programId, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec2(const std::string& name, float x, float y) const {
    glUniform2f(glGetUniformLocation(m_programId, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(m_programId, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(m_programId, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const {
    glUniform4fv(glGetUniformLocation(m_programId, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(m_programId, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat) const {
    glUniformMatrix2fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat) const {
    glUniformMatrix3fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::checkCompileErrors(unsigned int shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            AUTM_CORE_ERROR("Could not compile {} shader\n Log: {}", type, infoLog);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            AUTM_CORE_ERROR("Shader linking error \n Log: {}", type, infoLog);
        }
    }
}


