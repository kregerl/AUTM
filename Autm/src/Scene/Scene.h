#ifndef AUTM_SCENE_H
#define AUTM_SCENE_H

#include "EntityContactListener.h"
#include <Core/UUID.h>
#include "entt/entt.hpp"
#include <glm/glm.hpp>

class b2World;

class b2Body;

class Entity;

class Scene {
public:
    Scene();

    ~Scene();

    void begin_simulation();

    void end_simulation();

    Entity create_entity();

    void on_update(float ts);

    void set_paused(bool paused) { m_paused = paused; }

    bool get_paused() const { return m_paused; }

    void set_continuous_contact_callback(std::function<void(Entity&, Entity&, float)> callback);

    void set_begin_contact_callback(std::function<void(Entity&, Entity&)> callback) {
        m_contact_listener->set_begin_contact_callback(std::move(callback));
    }

    void set_end_contact_callback(std::function<void(Entity&, Entity&)> callback) {
        m_contact_listener->set_end_contact_callback(std::move(callback));
    }

    void set_pre_solve_callback(std::function<void(Entity&, Entity&)> callback) {
        m_contact_listener->set_pre_solve_callback(std::move(callback));
    }

    void set_post_solve_callback(std::function<void(Entity&, Entity&)> callback) {
        m_contact_listener->set_post_solve_callback(std::move(callback));
    }

    void apply_force_by_id(const UUID& uuid, const glm::vec2& force);

private:
    entt::registry m_registry;

    b2World* m_simulation_world;
    std::unordered_map<UUID, b2Body*> m_physics_bodies;
    std::unique_ptr<EntityContactListener> m_contact_listener;
    std::function<void(Entity&, Entity&, float)> m_continuous_contact_callback;

    bool m_paused = false;

    friend class Entity;
};


#endif //AUTM_SCENE_H
