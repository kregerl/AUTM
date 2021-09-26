#include "ComputeShader.h"

ComputeShader::ComputeShader(const char *computePath) {
    std::string computeShader;
    std::ifstream computeShaderFile;

    computeShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        computeShaderFile.open(computePath);
        std::stringstream cshStream;
        cshStream << computeShaderFile.rdbuf();
        computeShaderFile.close();
        computeShader = cshStream.str();
    }
    catch (std::ifstream::failure &e) {
        std::cout << "Couldn't read compute shader file.\n";
    }
    const char *cshCode = computeShader.c_str();

    unsigned int compute = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(compute, 1, &cshCode, nullptr);
    glCompileShader(compute);
    checkCompileErrors(compute, "COMPUTE");
    id = glCreateProgram();
    glAttachShader(id, compute);
    glDeleteShader(compute);

    glLinkProgram(id);
    checkCompileErrors(id, "PROGRAM");
}

void ComputeShader::dispatch(unsigned int groupsX, unsigned int groupsY, unsigned int groupsZ) {
    glDispatchCompute(groupsX, groupsY, groupsZ);
}
