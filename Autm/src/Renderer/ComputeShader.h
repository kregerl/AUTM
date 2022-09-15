#ifndef AUTM_COMPUTESHADER_H
#define AUTM_COMPUTESHADER_H

#include "Shader.h"

class ComputeShader : Shader {
public:
    explicit ComputeShader(std::string_view computePath);

    static void dispatch(unsigned int groupsX, unsigned int groupsY, unsigned groupsZ);

};


#endif
