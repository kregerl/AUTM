#include <Renderer/Renderer2D.h>
#include "autmpch.h"
#include "Scene.h"
#include "Entity.h"
#include "Components.h"

Scene::Scene() {

}

Scene::~Scene() {

}

Entity Scene::create_entity() {
    return { m_registry.create(), this};
}

void Scene::on_update(float ts) {
    auto entityGroup = m_registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
    for (auto entity : entityGroup) {
        auto [transform, sprite] = entityGroup.get<TransformComponent, SpriteRendererComponent>(entity);
        Renderer2D::draw_quad(transform.transform, sprite.color);
    }


}
