#include "vector.hh"
#include <components/box_collider.hh>
#include <components/component.hh>
#include <components/position.hh>
#include <components/renderer.hh>
#include <components/rigidbody.hh>
#include <components/rotatable.hh>
#include <engine.hh>
#include <entity.hh>
#include <graphics.hh>
#include <imgui.h>
#include <input.hh>
#include <log.hh>
#include <math.hh>
#include <scene.hh>
#include <texture_manager.hh>
#include <window.hh>

using namespace engine;

int main(int argc, char **argv) {

  Engine instance;
  instance.initialize();
  Engine::SubscribeToStart([](Scene &scene) -> void {
    auto texture =
        TextureManager::Load("/home/rf/Projects/c++/gaiyas/assets/frame-1.png");
    if (!texture) {
      logl("Failed to load texture");
      return;
    }

    Entity entity = scene.create_entity();
    entity.add<Position>(entity, Position(500, 500));
    entity.add<Renderer>(entity, texture);
    entity.add<Rotatable>(entity);
    entity.add<PolygonCollider>(
        entity, BoxCollider(texture->get_width(), texture->get_height()));
    entity.add<Scale>(entity, 0.1f);

   entity = scene.create_entity();
    entity.add<Position>(entity, Position(500, 500));
    entity.add<Renderer>(entity, texture);
    entity.add<Rotatable>(entity);
    entity.add<PolygonCollider>(
        entity, BoxCollider(texture->get_width(), texture->get_height()));
    entity.add<RigidBody>(entity);
    entity.add<Scale>(entity, 0.1f);
  });

  Engine::SubscribeToUpdate([&](Scene &scene, float deltaTime) -> void {
    if (Input::GetKeyDown(KeyCode::ESCAPE))
      instance.stop();

    auto view = scene.get_entity_list().view<RigidBody>();
    for (auto mv = view.begin(); mv != view.end(); mv++) {
      static float vel = 32.0f;

      auto &rigid = scene.get_entity_list().get<RigidBody>(*mv);
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
