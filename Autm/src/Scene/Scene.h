#ifndef AUTM_SCENE_H
#define AUTM_SCENE_H

#include "EntityContactListener.h"
#include <Core/UUID.h>
#include "entt/entt.hpp"

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

    void set_begin_contact_callback(std::function<void(Entity&, Entity&)> callback);

    void set_end_contact_callback(std::function<void(Entity&, Entity&)> callback);

//    void set_pre_solve_callback();
//
//    void set_post_solve_callback();

private:
    entt::registry m_registry;

    b2World* m_simulation_world;
    std::unordered_map<UUID, b2Body*> m_physics_bodies;
    std::unique_ptr<EntityContactListener> m_contact_listener;

    friend class Entity;
};


#endif //AUTM_SCENE_H
