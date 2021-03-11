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
#include <resource.hh>
#include <resource_manager.hh>
#include <texture_manager.hh>
#include <window.hh>

#include "../include/inspector_window.hh"
#include "../include/resource_window.hh"
#include "../include/systems/collision_system.hh"
#include "../include/systems/movement_system.hh"
#include "../include/systems/physics_system.hh"

using namespace engine;

int main(int argc, char **argv) {

  Engine instance;
  if (!instance.initialize())
    return EXIT_FAILURE;

  instance.disable_system<systems::PhysicsSystem>();
  instance.disable_system<systems::CollisionSystem>();
  instance.disable_system<systems::MovementSystem>();

  instance.register_system<InspectorWindow>();
  instance.register_system<ResourceWindow>();

  ResourceManager::SetResouceFile(
      "/home/rf/Projects/c++/gaiyas/resources.json");

  Engine::SubscribeToStart([](Scene &scene) -> void {});
  Engine::SubscribeToUpdate([&](Scene &scene, float dt) -> void {
    if (Input::GetKeyDown(KeyCode::ESCAPE))
      instance.stop();
  });

  instance.run();

  return 0;
}
