#ifndef AUTM_ENTITY_H
#define AUTM_ENTITY_H

#include "entt/entt.hpp"

#include "Scene.h"
#include <Core/Assert.h>

class Entity {
public:
    Entity() = default;

    Entity(entt::entity handle, Scene* scene);

    Entity(const Entity&) = default;

    template<typename T, typename... Args>
    T& add_component(Args&& ... args) {
        ASSERT(!has_components<T>(), "Entity already has the component");
        return m_scene->m_registry.emplace<T>(m_entity_handle, std::forward<Args>(args)...);
    }

    template<typename T>
    T& get_component() {
        ASSERT(has_components<T>(), "Entity does not have the component");
        return m_scene->m_registry.get<T>(m_entity_handle);
    }

    template<typename ...T>
    bool has_components() {
        return m_scene->m_registry.all_of<T...>(m_entity_handle);
    }

    template<typename T>
    void remove_component() {
        ASSERT(has_components<T>(), "Entity does not have the component");
        m_scene->m_registry.remove<T>(m_entity_handle);
    }
private:
    entt::entity m_entity_handle = entt::null;
    // Maybe a weak ptr
    Scene* m_scene = nullptr;
};


#endif //AUTM_ENTITY_H
