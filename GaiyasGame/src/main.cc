#include <components/box_collider.hh>
#include <components/component.hh>
#include <components/position.hh>
#include <components/renderer.hh>
#include <components/rigidbody.hh>
#include <components/rotatable.hh>
#include <engine.hh>
#include <imgui.h>
#include <input.hh>
#include <log.hh>
#include <texture_manager.hh>

using namespace engine;

static Engine *instance = nullptr;

int main(int argc, char **argv) {

  instance = Engine::initialize();

  instance->subscribe_to_start((startfn)[](entt::registry & registry)->void {
    auto texture =
        TextureManager::Load("/home/rf/Projects/c++/gaiyas/assets/frame-1.png");
    if (!texture) {
      logl("Failed to load texture");
      return;
    }

    auto entity = registry.create();
    registry.emplace<Position>(entity, Position(500, 500));
    registry.emplace<Renderer>(entity, texture).scale(0.1f);
    registry.emplace<Rotatable>(entity, Rotatable());
    registry.emplace<PolygonCollider>(
        entity, BoxCollider(texture->get_width(), texture->get_height()));

    entity = registry.create();
    registry.emplace<Position>(entity, Position(10.0f, 10.0f));
    registry.emplace<Renderer>(entity, texture).scale(0.1f);
    registry.emplace<Rotatable>(entity, Rotatable());
    registry.emplace<PolygonCollider>(
        entity, BoxCollider(texture->get_width(), texture->get_height()));
    registry.emplace<RigidBody>(entity, RigidBody());

  });

  instance->subscribe_to_update(
      (updatefn)[](entt::registry & registry, float deltaTime)->void {
        if (Input::GetKeyDown(KeyCode::ESCAPE))
          instance->stop();
      });

  instance->subscribe_to_render([]() -> void { ImGui::ShowDemoWindow(); });
  instance->run();

  return 0;
}
