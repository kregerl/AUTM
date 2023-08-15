#ifndef AUTM_COMPONENTS_H
#define AUTM_COMPONENTS_H

#include <glm/glm.hpp>

struct TransformComponent {
    glm::mat4 transform{1.0f};

    TransformComponent() = default;

    TransformComponent(const TransformComponent&) = default;

    TransformComponent(const glm::mat4& transform) : transform(transform) {}
};

struct SpriteRendererComponent {
    glm::vec4 color{1.0f, 1.0f, 1.0f, 1.0f};

    SpriteRendererComponent() = default;

    SpriteRendererComponent(const SpriteRendererComponent&) = default;

    SpriteRendererComponent(const glm::vec4& color) : color(color) {}
};


#endif //AUTM_COMPONENTS_H