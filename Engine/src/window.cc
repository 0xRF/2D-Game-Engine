#include "../include/window.hh"
#include "../include/log.hh"
#include <SDL.h>
#include <utility>

namespace engine {

std::string Window::m_name{};
SDL_Window *Window::m_window = nullptr;

bool Window::Initialize(const std::string &name, unsigned int w,
                        unsigned int h) {

  _debug_assert(m_window == nullptr);

  if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
    log("Failed to initialize Window %s", SDL_GetError());
    return false;
  }

  m_window =
      SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_ALLOW_HIGHDPI);

  if (!m_window) {
    log("Failed to create Window\n %s\n", SDL_GetError());
    return false;
  }

  return true;
}

const std::string &Window::GetName(void) { return m_name; }

void Window::SetName(const std::string &name) {
  m_name = name; // Todo add string santiation
}

uint32_t Window::GetWidth() {
  int x;
  SDL_GetWindowSize(m_window, &x, nullptr);
  return x;
}
uint32_t Window::GetHeight() {
  int y;
  SDL_GetWindowSize(m_window, nullptr, &y);
  return y;
}

Vector2 Window::GetCenter() {
  int x, y;
  SDL_GetWindowSize(m_window, &x, &y);
  return {(float)x / 2, (float)y / 2};
}
Vector2 Window::GetDimensions() {
  int x, y;
  SDL_GetWindowSize(m_window, &x, &y);
  return {(float)x, (float)y};
}

void *Window::GetWindowHandle() { return (void *)m_window; }
} // namespace engine
