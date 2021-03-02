#include "../include/engine.hh"
#include "../include/input.hh"
#include "../include/log.hh"
#include "../include/system.hh"
#include "../include/systems/collision_system.hh"
#include "../include/systems/movement_system.hh"
#include "../include/systems/physics_system.hh"
#include "../include/texture.hh"
#include "../include/texture_manager.hh"
#include "../include/window.hh"
#include "../internal/graphics_system.hh"

#include <SDL.h>

namespace engine {
static std::shared_ptr<Engine> instance;

Engine::Engine() { instance->m_window = Window::create("Test", 1280, 720); }

std::optional<Engine> Engine::Initialize() {

  Engine engine = Engine();

  if (SDL_Init(0) != 0) {
    logl("Failed to init sdl");
    return std::nullopt;
  }

  if (!Window::Initialize()) {
    logl("Failed to init Window");
    return std::nullopt;
  }

  if (!Input::Initialize()) {
    logl("Failed to init input");
    return std::nullopt;
  }
  if(!internal::GraphicsSystem::Initialize())
  {
      logl("Failed to init graphics_system");
      return std::nullopt;
  }

  instance->m_graphics = internal::GraphicsSystem::Create(instance);
  if (!instance->register_system(instance->m_graphics)) {
    logl("Failed to init texture_manager");
    return std::nullopt;
  }

  instance->m_texture_manager = TextureManager::create(instance);
  if (!instance->m_texture_manager) {
    logl("Failed to init texture_manager");
    return std::nullopt;
  }

  if (!instance->register_system(systems::PhysicsSystem::create(instance))) {
    logl("Failed to init physics_system");
    return std::nullopt;
  }
  if (!instance->register_system(systems::CollisionSystem::create(instance))) {
    logl("Failed to init collision_system");
    return std::nullopt;
  }

  if (!instance->register_system(systems::MovementSystem::create(instance))) {
    logl("Failed to init movement_system");
    return std::nullopt;
  }

  return instance;
}

Window *Engine::get_window() const { return m_window; }

void Engine::run() {
  m_alive = true;
  float deltaTime = 0.0f;

  for (auto fn : m_start_queue)
    fn(registry);

  for (auto sys : m_systems)
    sys->scene_load(registry);

  while (m_alive) {

    SDL_Event event;
    while (SDL_PollEvent(&event))
      for (auto fn : m_event_queue)
        if (event.type == fn.first)
          fn.second(event);

    Uint32 t1 = SDL_GetTicks();

    for (auto fn : m_update_queue)
      fn(registry, deltaTime);

    for (auto sys : m_systems)
      sys->update(deltaTime, registry);

    for (auto fn : m_post_update_queue)
      fn(registry, deltaTime);

    for (auto sys : m_systems)
      sys->update_end(deltaTime, registry);

    m_graphics->render_begin(registry);

    for (auto fn : m_render_queue)
      fn();

    for (auto sys : m_systems)
      sys->on_render(registry);

    m_graphics->render_end();

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

Engine::Engine() {}
Engine::~Engine() { delete m_window; }

}; // namespace engine
