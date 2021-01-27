#include "../internal/collision_system.hh"
#include "../include/components/box_collider.hh"
#include "../include/components/polygon_collider.hh"
#include "../include/components/position.hh"
#include "../include/components/rigidbody.hh"
#include "../include/components/rotatable.hh"
#include "../include/engine.hh"
#include "../include/log.hh"
#include "../include/math.hh"
#include "../include/utils.hh"
#include "../internal/graphics_system.hh"
#include <SDL_render.h>
#include <algorithm>
#include <imgui.h>
#include <limits>
#include <vector>

namespace engine::internal {

CollisionSystem *CollisionSystem::m_instance = nullptr;
Engine *CollisionSystem::m_engine = nullptr;

bool CollisionSystem::Collides(Position t1, PolygonCollider p1, Rotatable rot1,
                               Position t2, PolygonCollider p2,
                               Rotatable rot2) {
  std::vector<Vector2> poly1 = RebaseVectors(p1.points, t1);
  std::vector<Vector2> poly2 = RebaseVectors(p2.points, t2);

  for (int i = 0; i < 2; i++) {

    for (int a = 0; a < poly1.size(); a++) {
      int c = a + 1;
      int b = c % poly1.size();

      Vector2 proj_axis = poly1[a].twopoints(poly1[b]).perpendicular();

      auto handler = std::bind(&DotProduct, proj_axis, std::placeholders::_1);

      auto r1 = utils::find_min_max<float, Vector2>(poly1, handler);
      auto r2 = utils::find_min_max<float, Vector2>(poly2, handler);

      if (!(r2.second >= r1.first && r1.second >= r2.first))
        return false;
    }
    std::swap(poly1, poly2);
  }
  return true;
}

CollisionSystem *CollisionSystem::create(Engine *engine) {
  m_instance = new CollisionSystem;
  m_instance->m_engine = engine;
  return m_instance;
}

void CollisionSystem::update(float dt, entt::registry &registry) {
  auto movables =
      registry.view<Position, PolygonCollider, Rotatable, RigidBody>();
  auto collidables = registry.view<Position, PolygonCollider, Rotatable>();

  for (auto mv = movables.begin(); mv != movables.end(); mv++) {
    PolygonCollider collider1 = movables.get<PolygonCollider>(*mv);
    Position positon1 = movables.get<Position>(*mv);
    RigidBody &rigidbody1 = movables.get<RigidBody>(*mv);
    Rotatable rotation1 = movables.get<Rotatable>(*mv);

    for (auto col = collidables.begin(); col != collidables.end(); col++) {
      if (*mv == *col)
        continue;

      PolygonCollider collider2 = collidables.get<PolygonCollider>(*col);
      Position positon2 = collidables.get<Position>(*col);
      Rotatable rotation2 = collidables.get<Rotatable>(*col);

      if (Collides(positon1, collider1, rotation1, positon2, collider2,
                   rotation2)) {
        rigidbody1.velocity.y = 0.0f;
      }
    }
  }
}
void CollisionSystem::update_end(entt::registry &registry) {}
void CollisionSystem::scene_end(entt::registry &registry) {}
void CollisionSystem::scene_load(entt::registry &registry) {}
void CollisionSystem::shutdown(entt::registry &registry) {}
void CollisionSystem::render_begin(entt::registry &registry) {}
void CollisionSystem::on_render(entt::registry &registry) {

  auto polygons = registry.view<Position, PolygonCollider, Rotatable>();

  auto ent = *(polygons.begin());
  Position &position = polygons.get<Position>(ent);
  ImGui::Begin("Win");
  ImGui::SliderFloat("Pos X", &position.x, 0, 1280);
  ImGui::SliderFloat("Pos Y", &position.y, 0, 720);
  ImGui::End();

  auto renderer = m_engine->m_graphics->m_renderer;
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);

  for (auto mv = polygons.begin(); mv != polygons.end(); mv++) {
    auto pos = polygons.get<Position>(*mv);
    auto col = polygons.get<PolygonCollider>(*mv);
    auto rot = polygons.get<Rotatable>(*mv);

    for (int a = 0; a < col.points.size(); a++) {

      Vector2 point1 = col.points[a];
      Vector2 point2 = col.points[(a + 1) % col.points.size()];

      /*      point1 = RotateVector2D(point1, rot.rotation);
            point2 = RotateVector2D(point2, rot.rotation);*/
      point1 += pos;
      point2 += pos;

      SDL_RenderDrawLineF(renderer, point1.x, point1.y, point2.x, point2.y);
    }
  }
}

} // namespace engine::internal
