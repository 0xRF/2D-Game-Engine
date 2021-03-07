#include "../include/engine.hh"
#include "../include/graphics.hh"
#include "../include/input.hh"
#include "../include/log.hh"
#include "../include/system.hh"
#include "../include/systems/collision_system.hh"
#include "../include/systems/movement_system.hh"
#include "../include/systems/physics_system.hh"
#include "../include/texture.hh"
#include "../include/texture_manager.hh"
#include "../include/window.hh"

#include <SDL.h>

namespace engine {
static std::shared_ptr<Engine> instance;

Engine::Engine() {
  DEBUG_ASSERT(instance == nullptr);
  instance = std::shared_ptr<Engine>(this);
}

Engine::~Engine() {}

bool Engine::initialize() {

  if (SDL_Init(0) != 0) {
    logl("Failed to init sdl");
    return false;
  }

  if (!Window::Initialize("Test", 1280, 720)) {
    logl("Failed to init Window");
    return false;
  }
  if (!Graphics::Initialize()) {
    logl("Failed to init graphics_system");
    return false;
  }

  if (!Input::Initialize()) {
    logl("Failed to init input");
    return false;
  }

  /*
  if (!TextureManager::Initialize()) {
    logl("Failed to init texture_manager");
    return false;
  }
  */

  instance->register_system<systems::PhysicsSystem>();
  instance->register_system<systems::CollisionSystem>();
  instance->register_system<systems::MovementSystem>();

  return true;
}

void Engine::run() {
  m_alive = true;
  float deltaTime = 0.0f;

  for (auto fn : m_start_queue)
    fn(m_registry);

  for (auto sys : m_systems)
    sys->scene_load(m_registry);

  while (m_alive) {

    SDL_Event event;
    while (SDL_PollEvent(&event))
      for (auto fn : m_event_queue)
        if (event.type == fn.first)
          fn.second(event);

    Uint32 t1 = SDL_GetTicks();

    for (auto fn : m_update_queue)
      fn(m_registry, deltaTime);

    for (auto sys : m_systems)
      sys->update(deltaTime, m_sce);

    for (auto fn : m_post_update_queue)
      fn(m_registry, deltaTime);

    for (auto sys : m_systems)
      sys->update_end(deltaTime, m_registry);

    Graphics::render_begin(m_registry);

    for (auto fn : m_render_queue)
      fn();

    for (auto sys : m_systems)
      sys->on_render(m_registry);

    Graphics::render_end();

    Uint32 t2 = SDL_GetTicks();

    deltaTime = (float)(t2 - t1) / 1000;
  }
}

void Engine::stop() {
  if (!m_alive)
    log("Already shutting down");
  m_alive = false;
}

void Engine::SubscibeToEvent(uint32_t type, eventfn func) {
  instance->m_event_queue.emplace_back(type, func);
}
void Engine::SubscribeToUpdate(updatefn func) {
  instance->m_update_queue.emplace_back(func);
}

void Engine::SubscribeToPostUpdate(updatefn func) {
  instance->m_post_update_queue.emplace_back(func);
}

void Engine::SubscribeToStart(startfn func) {
  instance->m_start_queue.push_back(func);
}

void Engine::SubscribeToRender(renderfn func) {
  instance->m_render_queue.push_back(func);
}
}; // namespace engine
