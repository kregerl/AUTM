#ifndef AUTM_SCENE_H
#define AUTM_SCENE_H

#include <Core/UUID.h>
#include "entt/entt.hpp"

class b2World;

class b2Body;

class Entity;

class Scene {
public:
    Scene();

    ~Scene();

    void begin_physics_runtime();

    void end_physics_runtime();

    Entity create_entity();

    void on_update(float ts);

private:
    entt::registry m_registry;

    b2World* m_physics_world;
    std::unordered_map<UUID, b2Body*> m_physics_bodies;

    friend class Entity;
};


#endif //AUTM_SCENE_H
