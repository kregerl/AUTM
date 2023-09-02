#ifndef AUTM_COMPONENTS_H
#define AUTM_COMPONENTS_H

#include <Renderer/VertexBufferLayout.h>
#include <Core/UUID.h>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <utility>


struct IdentifierComponent {
    UUID id;

    IdentifierComponent() = default;

    IdentifierComponent(const IdentifierComponent&) = default;
};

struct TransformComponent {
    glm::vec3 translation = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);

    TransformComponent() = default;

    TransformComponent(const TransformComponent&) = default;

    explicit TransformComponent(const glm::vec3& translation, const glm::vec3& rotation = glm::vec3(0.0f),
                                const glm::vec3& scale = glm::vec3(1.0f))
            : translation(translation), rotation(rotation), scale(scale) {}

    [[nodiscard]] glm::mat4 get_transform() const {
        return glm::translate(glm::mat4(1.0f), translation)
               * glm::toMat4(glm::quat(rotation))
               * glm::scale(glm::mat4(1.0f), scale);
    }
};

struct SpriteRendererComponent {
    glm::vec4 color = glm::vec4(1.0f);
    std::shared_ptr<Texture2D> texture = nullptr;
    float tiling_factor = 1.0f;

    SpriteRendererComponent() = default;

    SpriteRendererComponent(const SpriteRendererComponent&) = default;

    explicit SpriteRendererComponent(const glm::vec4& color) : color(color) {}

    explicit SpriteRendererComponent(std::shared_ptr<Texture2D> texture, const glm::vec4& color = glm::vec4(1.0f),
                                     float tiling_factor = 1.0f)
            : texture(std::move(texture)), color(color), tiling_factor(tiling_factor) {}
};

struct CircleRendererComponent {
    glm::vec4 color = glm::vec4(1.0f);
    std::shared_ptr<Texture2D> texture = nullptr;
    float tiling_factor = 1.0f;
    float thickness = 1.0f;
    float fade = 0.05f;

    CircleRendererComponent() = default;

    CircleRendererComponent(const CircleRendererComponent&) = default;

    explicit CircleRendererComponent(const glm::vec4& color) : color(color) {}

    explicit CircleRendererComponent(std::shared_ptr<Texture2D> texture, const glm::vec4& color = glm::vec4(1.0f))
            : texture(std::move(texture)), color(color) {}
};

struct RectRendererComponent {
    glm::vec4 color = glm::vec4(1.0f);

    RectRendererComponent() = default;

    RectRendererComponent(const RectRendererComponent&) = default;
};

struct Rigidbody2DComponent {
    enum class Type {
        Static = 0, Kinematic, Dynamic
    };

    Type type = Type::Static;
    bool can_rotate = false;

    Rigidbody2DComponent() = default;

    Rigidbody2DComponent(const Rigidbody2DComponent&) = default;

    explicit Rigidbody2DComponent(Type type) : type(type) {}
};

struct BoxCollider2DComponent {
    glm::vec2 offset = glm::vec2(0.0f);
    glm::vec2 size = glm::vec2(0.5f);

    float density = 1.0f;
    float friction = 0.5f;
    // "Boundiness" of the object
    float restitution = 0.0f;
    // The velocity at which the entity stops bouncing
    float restitution_threshold = 0.5f;

    BoxCollider2DComponent() = default;

    BoxCollider2DComponent(const BoxCollider2DComponent&) = default;
};

struct CircleCollider2DComponent {
    glm::vec2 offset = glm::vec2(0.0f);
    float radius = 0.5f;

    float density = 1.0f;
    float friction = 0.5f;
    // "Boundiness" of the object
    float restitution = 0.0f;
    // The velocity at which the entity stops bouncing
    float restitution_threshold = 0.5f;

    CircleCollider2DComponent() = default;

    CircleCollider2DComponent(const CircleCollider2DComponent&) = default;
};

struct RectCollider2DComponent {
    // https://box2d.org/documentation/md__d_1__git_hub_box2d_docs_collision.html - Chain Shapes
    // The edge normal depends on the winding order. A counter-clockwise winding order orients the
    // normal outwards and a clockwise winding order orients the normal inwards.
    enum class WindingOrder {
        Inwards = 0, Outwards
    };

    WindingOrder winding_order = WindingOrder::Inwards;
    glm::vec2 offset = glm::vec2(0.0f);
    glm::vec2 size = glm::vec2(0.5f);
    float radius = 0.5f;

    float density = 1.0f;
    float friction = 0.5f;
    // "Boundiness" of the object
    float restitution = 0.0f;
    // The velocity at which the entity stops bouncing
    float restitution_threshold = 0.5f;

    RectCollider2DComponent() = default;

    RectCollider2DComponent(const RectCollider2DComponent&) = default;
};

#endif //AUTM_COMPONENTS_H
