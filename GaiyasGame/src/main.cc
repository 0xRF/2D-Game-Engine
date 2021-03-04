#include "vector.hh"
#include <components/box_collider.hh>
#include <components/component.hh>
#include <components/position.hh>
#include <components/renderer.hh>
#include <components/rigidbody.hh>
#include <components/rotatable.hh>
#include <engine.hh>
#include <graphics.hh>
#include <imgui.h>
#include <input.hh>
#include <log.hh>
#include <math.hh>
#include <texture_manager.hh>
#include <window.hh>

using namespace engine;

int main(int argc, char **argv) {

  Engine instance;
  instance.initialize();
  Engine::SubscribeToStart([](entt::registry &registry) -> void {
    auto texture =
        TextureManager::Load("/home/rf/Projects/c++/gaiyas/assets/frame-1.png");
    if (!texture) {
      logl("Failed to load texture");
      return;
    }

    auto entity = registry.create();
    registry.emplace<Position>(entity, Position(500, 500));
    registry.emplace<Renderer>(entity, texture);
    registry.emplace<Rotatable>(entity, Rotatable());
    registry.emplace<PolygonCollider>(
        entity, BoxCollider(texture->get_width(), texture->get_height()));
    registry.emplace<Scale>(entity, 0.1f);

    entity = registry.create();
    registry.emplace<Position>(entity, Position(10.0f, 10.0f));
    registry.emplace<Renderer>(entity, texture);
    registry.emplace<Rotatable>(entity, Rotatable());
    registry.emplace<PolygonCollider>(
        entity, BoxCollider(texture->get_width(), texture->get_height()));
    registry.emplace<RigidBody>(entity, RigidBody());
    registry.emplace<Scale>(entity, 0.1f);
  });

  Engine::SubscribeToUpdate(
      [&](entt::registry &registry, float deltaTime) -> void {
        if (Input::GetKeyDown(KeyCode::ESCAPE))
          instance.stop();

        auto view = registry.view<RigidBody>();
        for (auto mv = view.begin(); mv != view.end(); mv++) {
          static float vel = 32.0f;

          auto &rigid = registry.get<RigidBody>(*mv);
          if (Input::GetKeyDown(KeyCode::A))
            rigid.velocity.x = -vel;

          else if (Input::GetKeyDown(KeyCode::D))
            rigid.velocity.x = vel;

          else if (Input::GetKeyDown(KeyCode::W))
            rigid.velocity.y = -vel;

          else if (Input::GetKeyDown(KeyCode::S))
            rigid.velocity.y = vel;
          if (Input::GetKeyDown(KeyCode::SPACE)) {
            rigid.velocity.y = 0;
            rigid.velocity.x = 0;
          }
        }
      });

  float angle = 0.0f;
  float mag = 0.0f;
  Vector2 center = {(float)Window::GetWidth() / 2,
                    (float)Window::GetHeight() / 2};
  Vector2 vec = {1, 0};

  Engine::SubscribeToRender([&]() -> void {
    ImGui::SliderFloat("Angle", &angle, 0, 360);
    ImGui::SliderFloat("Magnitude", &mag, 0, 500);
    Vector2 v = RotateVector2D(vec, angle);
    v *= mag;
    Graphics::DrawLine(center, v + center);
    Graphics::DrawLine(center, v + center);
  });
  instance.run();

  return 0;
}
