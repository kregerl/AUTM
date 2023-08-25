#include <Core/Assert.h>
#include "EntityContactListener.h"
#include "Entity.h"
#include "Scene.h"

EntityContactListener::EntityContactListener(Scene* scene) : m_scene(scene) {}

void EntityContactListener::BeginContact(b2Contact* contact) {
    Entity entity0 = {*(entt::entity*) contact->GetFixtureA()->GetBody()->GetUserData().pointer, m_scene};
    Entity entity1 = {*(entt::entity*) contact->GetFixtureB()->GetBody()->GetUserData().pointer, m_scene};

    if (m_begin_contact_callback)
        m_begin_contact_callback(entity0, entity1);
}

void EntityContactListener::EndContact(b2Contact* contact) {
    Entity entity0 = {*(entt::entity*) contact->GetFixtureA()->GetBody()->GetUserData().pointer, m_scene};
    Entity entity1 = {*(entt::entity*) contact->GetFixtureB()->GetBody()->GetUserData().pointer, m_scene};

    if (m_end_contact_callback)
        m_end_contact_callback(entity0, entity1);
}

void EntityContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {}

void EntityContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}

