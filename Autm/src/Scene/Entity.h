#ifndef AUTM_ENTITY_H
#define AUTM_ENTITY_H

#include "entt/entt.hpp"

#include "Scene.h"

class Entity {
public:
    Entity(entt::entity handle, Scene* scene);
    Entity(const Entity&) = default;

    template<typename T, typename... Args>
    T& addComponent(Args&&... args) {
        // TODO: Asserts
        return m_scene->m_registry.emplace<T>(m_entity_handle, std::forward<Args>(args)...);
    }

    template<typename T>
    T& getComponent() {
        // TODO: Asserts
        return m_scene->m_registry.get<T>(m_entity_handle);
    }

    template<typename T>
    bool hasComponent() {
        return m_scene->m_registry.all_of<T>(m_entity_handle);
    }

    template<typename T>
    void removeComponent() {
        m_scene->m_registry.remove<T>(m_entity_handle);
    }

private:
    entt::entity m_entity_handle;
    // Maybe a weak ptr
    Scene* m_scene;
};

#endif //AUTM_ENTITY_H
