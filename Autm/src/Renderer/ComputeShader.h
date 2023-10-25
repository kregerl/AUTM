#ifndef AUTM_COMPUTESHADER_H
#define AUTM_COMPUTESHADER_H

#include "Shader.h"

class ComputeShader : public Shader {
public:
    explicit ComputeShader(std::string_view compute_path);

    static void dispatch(unsigned int groups_x, unsigned int groups_y, unsigned groups_z);

};


#endif
