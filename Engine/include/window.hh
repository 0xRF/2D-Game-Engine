#pragma once

#include "common.hh"

struct SDL_Window;

namespace engine {

class Engine;

class Window {
public:
  const static std::string &GetName(void);
  static void SetName(const std::string &name);

  static uint32_t GetWidth();
  static uint32_t GetHeight();
  static Vector2 GetCenter();
  static Vector2 GetDimensions();

  static void *GetWindowHandle();

private:
  static bool Initialize(const std::string &name, unsigned int width,
                         unsigned int height);

  static std::string m_name;
  static SDL_Window *m_window;
  friend Engine;
};
} // namespace engine
