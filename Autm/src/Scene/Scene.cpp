#include <Renderer/Renderer2D.h>
#include "autmpch.h"
#include "Scene.h"
#include "Entity.h"
#include "Components.h"

#include <box2d/box2d.h>

Scene::Scene() {}

Scene::~Scene() {}

Entity Scene::create_entity() {
    Entity entity = {m_registry.create(), this};
    entity.add_component<IdentifierComponent>();
    entity.add_component<TransformComponent>();
    return entity;
}

void Scene::on_update(float ts) {
    {
        const uint32_t velocity_iter = 6;
        const uint32_t position_iter = 2;
        m_physics_world->Step(ts, velocity_iter, position_iter);

        // Update the transform of the entity to the new positions after a physics step.
        auto rigidbody_group = m_registry.view<Rigidbody2DComponent>();
        for (auto rigibody_entity: rigidbody_group) {
            Entity entity = {rigibody_entity, this};

            auto& identifier = entity.get_component<IdentifierComponent>();
            auto& transform = entity.get_component<TransformComponent>();

            b2Body* body = m_physics_bodies.at(identifier.id);
            const auto& position = body->GetPosition();
            transform.translation.x = position.x;
            transform.translation.y = position.y;
            transform.rotation.z = body->GetAngle();
        }
    }

    // Render sprites
    {
        auto sprite_group = m_registry.view<TransformComponent, SpriteRendererComponent>();
        for (auto entity: sprite_group) {
            auto[transform, sprite] =sprite_group.get<TransformComponent, SpriteRendererComponent>(entity);

            if (sprite.texture) {
                Renderer2D::draw_quad(transform.get_transform(), sprite.texture, sprite.tiling_factor, sprite.color);
            } else {
                Renderer2D::draw_quad(transform.get_transform(), sprite.color);
            }
        }
    }

    // Render circles
    {
        auto circle_group = m_registry.view<TransformComponent, CircleRendererComponent>();
        for (auto entity: circle_group) {
            auto[transform, circle] = circle_group.get<TransformComponent, CircleRendererComponent>(entity);

            if (circle.texture) {
                Renderer2D::draw_circle(transform.get_transform(), circle.texture, circle.color, circle.tiling_factor,
                                        circle.thickness, circle.fade);
            } else {
                Renderer2D::draw_circle(transform.get_transform(), circle.color, circle.tiling_factor, circle.thickness,
                                        circle.fade);
            }
        }
    }
}

void Scene::begin_physics_runtime() {
    m_physics_world = new b2World({0.0f, -9.8f});

    for (auto rigibdoy_entity: m_registry.view<Rigidbody2DComponent>()) {
        Entity entity = {rigibdoy_entity, this};
        // All entities have IdentifierComponent and TransformComponent
        auto& identifier = entity.get_component<IdentifierComponent>();
        auto& transform = entity.get_component<TransformComponent>();
        auto& rigidbody = entity.get_component<Rigidbody2DComponent>();

        b2BodyDef body_def;
        body_def.type = (b2BodyType) rigidbody.type;
        body_def.position.Set(transform.translation.x, transform.translation.y);
        body_def.angle = transform.rotation.z;

        b2Body* body = m_physics_world->CreateBody(&body_def);
        body->SetFixedRotation(rigidbody.can_rotate);
        m_physics_bodies[identifier.id] = body;

        if (entity.has_component<BoxCollider2DComponent>()) {
            auto& box_collider = entity.get_component<BoxCollider2DComponent>();

            b2PolygonShape shape;
            shape.SetAsBox(box_collider.size.x * transform.scale.x, box_collider.size.y * transform.scale.y,
                           b2Vec2(box_collider.offset.x, box_collider.offset.y), 0.0f);

            b2FixtureDef fixture_def;
            fixture_def.shape = &shape;
            fixture_def.density = box_collider.density;
            fixture_def.friction = box_collider.friction;
            fixture_def.restitution = box_collider.restitution;
            fixture_def.restitutionThreshold = box_collider.restitution_threshold;
            body->CreateFixture(&fixture_def);
        }

        if (entity.has_component<CircleCollider2DComponent>()) {
            auto& circle_collider = entity.get_component<CircleCollider2DComponent>();

            b2CircleShape shape;
            shape.m_p.Set(circle_collider.offset.x, circle_collider.offset.y);
            shape.m_radius = circle_collider.radius * transform.scale.x;

            b2FixtureDef fixture_def;
            fixture_def.shape = &shape;
            fixture_def.density = circle_collider.density;
            fixture_def.friction = circle_collider.friction;
            fixture_def.restitution = circle_collider.restitution;
            fixture_def.restitutionThreshold = circle_collider.restitution_threshold;
            body->CreateFixture(&fixture_def);
        }
    }
}

void Scene::end_physics_runtime() {
    delete m_physics_world;
    m_physics_world = nullptr;
}
