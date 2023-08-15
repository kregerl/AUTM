#ifndef AUTM_SCENE_H
#define AUTM_SCENE_H

#include "entt/entt.hpp"

class Entity;

class Scene {
public:
    Scene();
    ~Scene();

    Entity create_entity();

    void on_update(float ts);
private:
    entt::registry m_registry;

    friend class Entity;
};


#endif //AUTM_SCENE_H
