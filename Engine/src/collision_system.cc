#include "../internal/collision_system.hh"
#include "../include/components/box_collider.hh"
#include "../include/components/polygon_collider.hh"
#include "../include/components/position.hh"
#include "../include/components/rigidbody.hh"
#include "../include/components/rotatable.hh"
#include "../include/engine.hh"
#include "../include/log.hh"
#include "../include/math.hh"
#include "../internal/graphics_system.hh"
#include <SDL_render.h>
#include <imgui.h>
#include <limits>
#include <vector>

namespace engine::internal {

CollisionSystem *CollisionSystem::m_instance = nullptr;
Engine *CollisionSystem::m_engine = nullptr;

bool CollisionSystem::Collides(Position t1, PolygonCollider p1, Rotatable rot1,
                               Position t2, PolygonCollider p2,
                               Rotatable rot2) {
  std::vector<Vector2> _poly1(p1.points.size());
  std::vector<Vector2> _poly2(p2.points.size());

  for (int i = 0; i < _poly1.size(); i++) {
    _poly1[i] = RotateVector2D(p1.points[i], rot2.rotation);
    _poly1[i].x += t1.x;
    _poly1[i].y += t1.y;
  }

  for (int i = 0; i < _poly2.size(); i++) {
    _poly2[i] = RotateVector2D(p2.points[i], rot2.rotation);
    _poly2[i].x += t2.x;
    _poly2[i].y += t2.y;
  }
  std::vector<Vector2> *poly1 = &_poly1;
  std::vector<Vector2> *poly2 = &_poly2;

  for (int i = 0; i < 2; i++) {
    if (i == 1) {
      poly1 = &_poly2;
      poly2 = &_poly1;
    }

    for (int a = 0; i < poly1->size(); a++) {
      int b = (a + 1) % poly1->size();
      Vector2 proj_axis = {-(poly1->at(b).y - poly1->at(a).y),
                           poly1->at(b).x - poly1->at(a).x};

      float min_r1 = std::numeric_limits<float>::max();
      float max_r1 = -std::numeric_limits<float>::max();
      for (int p = 0; i < poly1->size(); p++) {
        float q = DotProduct(poly1->at(p), proj_axis);

        max_r1 = std::max(max_r1, q);
        min_r1 = std::max(min_r1, q);
      }

      float min_r2 = std::numeric_limits<float>::max();
      float max_r2 = -std::numeric_limits<float>::max();
      for (int p = 0; i < poly2->size(); p++) {
        float q = DotProduct(poly2->at(p), proj_axis);

        max_r2 = std::max(max_r2, q);
        min_r2 = std::max(min_r2, q);
      }

      if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
        return false;
    }
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
    RigidBody rigidbody1 = movables.get<RigidBody>(*mv);
    Rotatable rotation1 = movables.get<Rotatable>(*mv);

    for (auto col = collidables.begin(); col != collidables.end(); col++) {
      if (*mv == *col)
        continue;

      PolygonCollider collider2 = collidables.get<PolygonCollider>(*col);
      Position positon2 = collidables.get<Position>(*col);
      Rotatable rotation2 = collidables.get<Rotatable>(*col);

      if (Collides(positon1, collider1, rotation1, positon2, collider2,
                   rotation2)) {

        rigidbody1.velocity = 0.0f;
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

      int b = a + 1;
      Vector2 point1 = col.points[a];
      Vector2 point2 = col.points[b % col.points.size()];

      engine::logl("%d ---> %d : (%f %f) --> (%f %f)", a, b % col.points.size(),
                   point1.x, point1.y, point2.x, point2.y);
      /*      point1 = RotateVector2D(point1, rot.rotation);
            point2 = RotateVector2D(point2, rot.rotation);*/
      point1 += pos;
      point2 += pos;

      SDL_RenderDrawLineF(renderer, point1.x, point1.y, point2.x, point2.y);
    }
  }
}

} // namespace engine::internal
