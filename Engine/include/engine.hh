#pragma once

#include "common.hh"

union SDL_Event;

namespace engine {

class Window;
struct Frame;
class TextureManager;
namespace internal {
    class GraphicsSystem;
}
class System;

using eventfn = std::function<void(const SDL_Event)>;
using updatefn = std::function<void(entt::registry &, float)>;
using renderfn = std::function<void()>;
using startfn = std::function<void(entt::registry &)>;

class Engine {
public:
  Engine();
  Engine(const Engine &) = delete;
  ~Engine();

  static std::optional<Engine> Initialize();

  Window *get_window() const;

  void run();

  void stop();

  template <typename T> T *register_system(T *sys) {

    auto it =
        std::find_if(m_systems.begin(), m_systems.end(), [](auto sys) -> bool {
          return dynamic_cast<T *>(sys) != nullptr;
        });

    if (it != m_systems.end())
      return dynamic_cast<T *>(*it);

    m_systems.push_back(sys);
    return sys;
  }

  static void SubscribeToStart(startfn func);
  static void SubscibeToEvent(uint32_t type, eventfn func);
  static void SubscribeToUpdate(updatefn func);
  static void SubscribeToPostUpdate(updatefn func);
  static void SubscribeToRender(renderfn func);

  template <typename T> void disable_system() {
    std::remove_if(m_systems.begin(), m_systems.end(), [](auto sys) -> bool {
      return dynamic_cast<T *>(sys) != nullptr;
    });
  }
  internal::GraphicsSystem *m_graphics;

private:
  Window *m_window;
  TextureManager *m_texture_manager;
  std::vector<System *> m_systems{};

  bool m_alive = false;
  std::vector<std::pair<uint32_t, eventfn>> m_event_queue{};
  std::vector<updatefn> m_update_queue{};
  std::vector<updatefn> m_post_update_queue{};
  std::vector<renderfn> m_render_queue{};
  std::vector<startfn> m_start_queue{};
  entt::registry registry;

  friend TextureManager;
};
} // namespace engine
