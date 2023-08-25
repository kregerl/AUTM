#ifndef AUTM_ENTITYCONTACTLISTENER_H
#define AUTM_ENTITYCONTACTLISTENER_H

#include "autmpch.h"
#include <box2d/box2d.h>

class Entity;

class Scene;

class EntityContactListener : public b2ContactListener {
public:
    explicit EntityContactListener(Scene* scene);

    ~EntityContactListener() override = default;

    void set_begin_contact_callback(std::function<void(Entity&, Entity&)> callback) {
        m_begin_contact_callback = std::move(callback);
    }

    void set_end_contact_callback(std::function<void(Entity&, Entity&)> callback) {
        m_end_contact_callback = std::move(callback);
    }

private:
    void BeginContact(b2Contact* contact) override;

    void EndContact(b2Contact* contact) override;

    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

private:
    std::function<void(Entity&, Entity&)> m_begin_contact_callback;
    std::function<void(Entity&, Entity&)> m_end_contact_callback;
    Scene* m_scene;
};


#endif //AUTM_ENTITYCONTACTLISTENER_H
