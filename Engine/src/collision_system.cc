#include "../internal/collision_system.hh"
#include "../include/components/box_collider.hh"
#include "../include/components/polygon_collider.hh"
#include "../include/components/position.hh"
#include "../include/components/rigidbody.hh"
#include "../include/components/rotatable.hh"
#include "../include/engine.hh"
#include "../include/graphics.hh"
#include "../include/log.hh"
#include "../include/math.hh"
#include "../include/utils.hh"
#include "../include/window.hh"
#include "../internal/graphics_system.hh"
#include <SDL_render.h>
#include <algorithm>
#include <imgui.h>
#include <limits>
#include <memory>
#include <vector>

std::vector<Vector2> collisions{};

namespace engine::internal {

CollisionSystem *CollisionSystem::m_instance = nullptr;
Engine *CollisionSystem::m_engine = nullptr;

std::unique_ptr<Vector2>
CollisionSystem::Collides(Position t1, PolygonCollider p1, Rotatable rot1,
                          Scale scale1, Position t2, PolygonCollider p2,
                          Rotatable rot2, Scale scale2) {

  std::vector<Vector2> poly1 = ScaleVectors(p1.points, scale1);
  std::vector<Vector2> poly2 = ScaleVectors(p2.points, scale2);

  poly1 = RebaseVectors(poly1, t1);
  poly2 = RebaseVectors(poly2, t2);

  Vector2 proj_axis;

  for (int i = 0; i < 2; i++) {

    for (int a = 0; a < poly1.size(); a++) {
      int c = a + 1;
      int b = c % poly1.size();

      proj_axis = poly1[a].twopoints(poly1[b]).perpendicular();

      auto handler = std::bind(&DotProduct, proj_axis, std::placeholders::_1);

      auto r1 = utils::find_min_max<float, Vector2>(poly1, handler);
      auto r2 = utils::find_min_max<float, Vector2>(poly2, handler);

      if (!(r2.second >= r1.first && r1.second >= r2.first))
        return std::unique_ptr<Vector2>{nullptr};
    }
    std::swap(poly1, poly2);
    collisions.push_back(Normalize(proj_axis));
  }
  return std::make_unique<Vector2>(Normalize(proj_axis));
}

CollisionSystem *CollisionSystem::create(Engine *engine) {
  m_instance = new CollisionSystem;
  m_instance->m_engine = engine;
  return m_instance;
}

void CollisionSystem::update(float dt, entt::registry &registry) {

  auto movables =
      registry.view<Position, PolygonCollider, Rotatable, RigidBody, Scale>();
  auto collidables =
      registry.view<Position, PolygonCollider, Rotatable, Scale>();

  for (auto mv = movables.begin(); mv != movables.end(); mv++) {
    PolygonCollider collider1 = movables.get<PolygonCollider>(*mv);
    Position positon1 = movables.get<Position>(*mv);
    RigidBody &rigidbody1 = movables.get<RigidBody>(*mv);
    Rotatable rotation1 = movables.get<Rotatable>(*mv);
    Scale scale1 = movables.get<Scale>(*mv);

    for (auto col = collidables.begin(); col != collidables.end(); col++) {
      if (*mv == *col)
        continue;

      PolygonCollider collider2 = collidables.get<PolygonCollider>(*col);
      Position positon2 = collidables.get<Position>(*col);
      Rotatable rotation2 = collidables.get<Rotatable>(*col);
      Scale scale2 = movables.get<Scale>(*mv);

      auto coll = Collides(positon1, collider1, rotation1, scale1, positon2,
                           collider2, rotation2, scale2);
      if (coll) {
        engine::logl("%f %f", coll->x, coll->y);
        float a1 = rigidbody1.velocity.dot(*coll);
        Vector2 subVel = {coll->x * a1 * dt, coll->y * a1 * dt};
        rigidbody1.velocity -= subVel;
      }
    }
  }
}
void CollisionSystem::update_end(float dt, entt::registry &registry) {}
void CollisionSystem::scene_end(entt::registry &registry) {}
void CollisionSystem::scene_load(entt::registry &registry) {}
void CollisionSystem::shutdown(entt::registry &registry) {}
void CollisionSystem::render_begin(entt::registry &registry) {}
void CollisionSystem::on_render(entt::registry &registry) {

  auto polygons = registry.view<Position, PolygonCollider, Rotatable, Scale>();

  auto ent = *(polygons.begin());
  Position &position = polygons.get<Position>(ent);
  ImGui::Begin("Win");
  ImGui::SliderFloat("Pos X", &position.x, 0, 1280);
  ImGui::SliderFloat("Pos Y", &position.y, 0, 720);
  ImGui::End();

  for (auto mv = polygons.begin(); mv != polygons.end(); mv++) {
    auto pos = polygons.get<Position>(*mv);
    auto col = polygons.get<PolygonCollider>(*mv);
    auto rot = polygons.get<Rotatable>(*mv);
    auto scale = polygons.get<Scale>(*mv);

    for (int a = 0; a < col.points.size(); a++) {

      Vector2 point1 = col.points[a];
      Vector2 point2 = col.points[(a + 1) % col.points.size()];

      /*      point1 = RotateVector2D(point1, rot.rotation);
            point2 = RotateVector2D(point2, rot.rotation);*/

      point1 *= scale;
      point2 *= scale;
      point1 += pos;
      point2 += pos;

      Graphics::DrawLine(point1, point2);
    }
  }

  auto window = m_engine->get_window();
  Vector2 center = {(float)window->get_width() / 2,
                    (float)window->get_height() / 2};

  collisions = ScaleVectors(collisions, 200.0f);
  for (auto mv = collisions.begin(); mv != collisions.end(); mv++) {
    Graphics::DrawLine(center, center + (*mv));
  }
  collisions.clear();
}

} // namespace engine::internal
