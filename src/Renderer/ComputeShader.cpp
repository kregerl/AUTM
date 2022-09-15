#include <Core/Log.h>
#include "ComputeShader.h"

ComputeShader::ComputeShader(std::string_view computePath) {
    std::string computeShader;
    std::ifstream computeShaderFile;

    computeShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        computeShaderFile.open(computePath.data());
        std::stringstream cshStream;
        cshStream << computeShaderFile.rdbuf();
        computeShaderFile.close();
        computeShader = cshStream.str();
    }
    catch (std::ifstream::failure &e) {
        AUTM_CORE_ERROR("Couldn't read compute shader at {}", computePath);
    }
    const char *cshCode = computeShader.c_str();

    unsigned int compute = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(compute, 1, &cshCode, nullptr);
    glCompileShader(compute);
    checkCompileErrors(compute, "COMPUTE");
    m_programId = glCreateProgram();
    glAttachShader(m_programId, compute);
    glDeleteShader(compute);

    glLinkProgram(m_programId);
    checkCompileErrors(m_programId, "PROGRAM");
}

void ComputeShader::dispatch(unsigned int groupsX, unsigned int groupsY, unsigned int groupsZ) {
    glDispatchCompute(groupsX, groupsY, groupsZ);
}
