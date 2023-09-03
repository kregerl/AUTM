#include <Core/Log.h>
#include "ComputeShader.h"

ComputeShader::ComputeShader(std::string_view compute_path) {
    std::string compute_shader;
    std::ifstream computer_shader_file;

    computer_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        computer_shader_file.open(compute_path.data());
        std::stringstream compute_shader_stream;
        compute_shader_stream << computer_shader_file.rdbuf();
        computer_shader_file.close();
        compute_shader = compute_shader_stream.str();
    }
    catch (std::ifstream::failure &e) {
        AUTM_CORE_ERROR("Couldn't read compute shader at {}", compute_path);
    }
    const char *compute_shader_code = compute_shader.c_str();

    unsigned int compute = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(compute, 1, &compute_shader_code, nullptr);
    glCompileShader(compute);
    check_compile_errors(compute, "COMPUTE");
    m_program_id = glCreateProgram();
    glAttachShader(m_program_id, compute);
    glDeleteShader(compute);

    glLinkProgram(m_program_id);
    check_compile_errors(m_program_id, "PROGRAM");
}

void ComputeShader::dispatch(unsigned int groups_x, unsigned int groups_y, unsigned int groups_z) {
    glDispatchCompute(groups_x, groups_y, groups_z);
}
