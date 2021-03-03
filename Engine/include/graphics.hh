#pragma once

#include "common.hh"

struct SDL_Renderer;
union SDL_Event;
namespace engine {

class Engine;

class Graphics {
public:
  Graphics(const Graphics &) = delete;

  static void DrawLine(Vector2 a, Vector2 b);
  static void* GetRenderer();

private:
  friend Engine;

  static void WindowResized(SDL_Event e);

  static bool Initialize();
  static void render_begin(entt::registry &registry);
  static void render_end();

  static SDL_Renderer *m_renderer;
};
} // namespace engine
