#ifndef AUTM_PRIMITIVES_H
#define AUTM_PRIMITIVES_H


#include <Renderer/VertexArray.h>

class Primitives {
public:

    /**
     * Generates a fullscreen quad based on the aspect ratio.<br>
     * The vertex buffer layout is:<br>
     * - a_position (vec3)<br>
     * - a_texture_coordinate (vec2)<br>
     *
     * @return A shared pointer to the vertex array
     */
    [[nodiscard]] static std::shared_ptr<VertexArray> generate_fullscreen_quad(float aspect_ratio, float zoom = 1.0f);

};


#endif //AUTM_PRIMITIVES_H
