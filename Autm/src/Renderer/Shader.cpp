#include <gtc/type_ptr.hpp>
#include "Core/Log.h"
#include "Shader.h"

Shader::Shader() : m_program_id(0) {}

Shader::Shader(std::string_view vertexPath, std::string_view fragmentPath, std::string_view geometryPath) {
    std::string vertexShader, fragmentShader;
    std::ifstream vertexShaderFile, fragmentShaderFile;

    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vertexShaderFile.open(vertexPath.data());
        fragmentShaderFile.open(fragmentPath.data());
        std::stringstream vertexStream, fragmentStream;
        vertexStream << vertexShaderFile.rdbuf();
        fragmentStream << fragmentShaderFile.rdbuf();
        vertexShaderFile.close();
        fragmentShaderFile.close();
        vertexShader = vertexStream.str();
        fragmentShader = fragmentStream.str();
    }
    catch (std::ifstream::failure& e) {
        AUTM_CORE_ERROR("Couldn't read shaders at V:{}\nF:{}", vertexPath, fragmentPath);
    }
    const char* vshCode = vertexShader.c_str();
    const char* fshCode = fragmentShader.c_str();

    //Compile shaders
    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vshCode, nullptr);
    glCompileShader(vertex);
    check_compile_errors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fshCode, nullptr);
    glCompileShader(fragment);
    check_compile_errors(fragment, "FRAGMENT");

    m_program_id = glCreateProgram();
    glAttachShader(m_program_id, vertex);
    glAttachShader(m_program_id, fragment);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    if (!geometryPath.empty()) {
        std::string geometryCode;
        std::ifstream gshFile;

        gshFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            gshFile.open(geometryPath.data());
            std::stringstream gshStream;
            gshStream << gshFile.rdbuf();
            gshFile.close();
            geometryCode = gshStream.str();
        }
        catch (std::ifstream::failure& e) {
            AUTM_CORE_ERROR("Couldn't read geometry shader at {}", geometryPath);
        }
        const char* gshCode = geometryCode.c_str();

        unsigned int geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gshCode, nullptr);
        glCompileShader(geometry);
        check_compile_errors(geometry, "GEOMETRY");
        glAttachShader(m_program_id, geometry);
        glDeleteShader(geometry);
    }

    glLinkProgram(m_program_id);
    check_compile_errors(m_program_id, "PROGRAM");
}

Shader::~Shader() {
    glDeleteProgram(m_program_id);
}

void Shader::bind() const {
    glUseProgram(m_program_id);
}

void Shader::unbind() const {
    glUseProgram(0);
}

void Shader::set_bool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(m_program_id, name.c_str()), (int) value);
}

void Shader::set_int(const std::string& name, int value) const {
    set_intv(name, &value, 1);
}

void Shader::set_intv(const std::string& name, const int* value, uint32_t count) const {
    glUniform1iv(glGetUniformLocation(m_program_id, name.c_str()), (GLsizei) count, value);
}

void Shader::set_uint(const std::string& name, uint32_t value) const {
    glUniform1ui(glGetUniformLocation(m_program_id, name.c_str()), value);
}

void Shader::set_float(const std::string& name, float value) const {
    set_floatv(name, &value, 1);
}

void Shader::set_floatv(const std::string& name, const float* value, uint32_t count) const {
    glUniform1fv(glGetUniformLocation(m_program_id, name.c_str()), (GLsizei) count, value);
}

void Shader::set_vec2(const std::string& name, const glm::vec2& value) const {
    glUniform2fv(glGetUniformLocation(m_program_id, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::set_vec2(const std::string& name, float x, float y) const {
    glUniform2f(glGetUniformLocation(m_program_id, name.c_str()), x, y);
}

void Shader::set_vec3(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(m_program_id, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::set_vec3(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(m_program_id, name.c_str()), x, y, z);
}

void Shader::set_vec4(const std::string& name, const glm::vec4& value) const {
    glUniform4fv(glGetUniformLocation(m_program_id, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::set_vec4(const std::string& name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(m_program_id, name.c_str()), x, y, z, w);
}

void Shader::set_mat2(const std::string& name, const glm::mat2& mat) const {
    glUniformMatrix2fv(glGetUniformLocation(m_program_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::set_mat3(const std::string& name, const glm::mat3& mat) const {
    glUniformMatrix3fv(glGetUniformLocation(m_program_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::set_mat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(m_program_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::check_compile_errors(unsigned int shader_program, const std::string& type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader_program, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader_program, 1024, nullptr, infoLog);
            AUTM_CORE_ERROR("Could not compile {} shader\n Log: {}", type, infoLog);
        }
    } else {
        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader_program, 1024, nullptr, infoLog);
            AUTM_CORE_ERROR("Shader linking error \n Log: {}", type, infoLog);
        }
    }
}




