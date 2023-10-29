#ifndef AUTM_COORDINATE_H
#define AUTM_COORDINATE_H

#include <autmpch.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_projection.hpp>
#include "App/Application.h"

namespace Coordinate {
    /**
     * Maps the coordinates of the mouse on the screen to the coordinates in world space.
     */
    static glm::vec3 map_screen_coords_to_world_coords(
            const glm::vec3 &mouse_coords,
            const glm::mat4 &projection_matrix) {

        auto screen_width = static_cast<float>(Application::get_window().get_width());
        auto screen_height = static_cast<float>(Application::get_window().get_height());

        return glm::unProject(
                glm::vec3(mouse_coords.x, screen_height - mouse_coords.y, mouse_coords.z),
                glm::mat4(1.0f),
                projection_matrix,
                glm::vec4(0, 0, screen_width, screen_height));
    }
}

#endif //AUTM_COORDINATE_H
