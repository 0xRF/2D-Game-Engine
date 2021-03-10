#pragma once

#include "common.hh"
#include "log.hh"

union SDL_Event;

namespace engine {

class Window;
struct Frame;
class TextureManager;
class System;

using eventfn = std::function<void(const SDL_Event)>;
using updatefn = std::function<void(Scene&, float)>;
using renderfn = std::function<void()>;
using startfn = std::function<void(Scene&)>;

class Engine {
public:
  Engine();
  Engine(const Engine &) = delete;
  ~Engine();

  bool initialize();

  void run();

  void stop();

  template <typename T> void disable_system() {
    std::remove_if(m_systems.begin(), m_systems.end(), [](auto sys) -> bool {
      return dynamic_cast<T *>(sys) != nullptr;
    });
  }

  template <typename T> void register_system() {
    static bool enabled = false;
    DEBUG_ASSERT(!enabled);
    m_systems.push_back(new T());
  }

  static void SubscribeToStart(startfn func);
  static void SubscibeToEvent(uint32_t type, eventfn func);
  static void SubscribeToUpdate(updatefn func);
  static void SubscribeToPostUpdate(updatefn func);
  static void SubscribeToRender(renderfn func);

private:
  std::unique_ptr<Window> m_window;
  std::vector<System *> m_systems{};

  bool m_alive = false;
  std::vector<std::pair<uint32_t, eventfn>> m_event_queue{};
  std::vector<updatefn> m_update_queue{};
  std::vector<updatefn> m_post_update_queue{};
  std::vector<renderfn> m_render_queue{};
  std::vector<startfn> m_start_queue{};
  Scene* m_scene = nullptr;

  friend TextureManager;
};
} // namespace engine
