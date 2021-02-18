#include "../include/window.hh"
#include "../include/log.hh"
#include <SDL.h>
#include <utility>

namespace engine {

Window *Window::m_instance = nullptr;

bool Window::initialize() {
  logl("Initing window");
  if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
    log("Failed to initialize Window %s", SDL_GetError());
    return false;
  }
  return true;
}

Window *Window::create(const std::string &name, unsigned int w,
                       unsigned int h) {
  logl("Creating Window");
  SDL_Window *window =
      SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_ALLOW_HIGHDPI);

  if (!window) {
    log("Failed to create Window\n %s\n", SDL_GetError());
    return nullptr;
  }

  m_instance = new Window(name, window);
  return m_instance;
}

const std::string &Window::GetName(void) { return m_instance->m_name; }

void Window::SetName(const std::string &name) {
  m_instance->m_name = name; // Todo add string santiation
}

uint32_t Window::GetWidth() {
  int x;
  SDL_GetWindowSize(m_instance->m_window, &x, nullptr);
  return x;
}
uint32_t Window::GetHeight() {
  int y;
  SDL_GetWindowSize(m_instance->m_window, nullptr, &y);
  return y;
}

Window::Window(std::string name, SDL_Window *window)
    : m_name(std::move(name)), m_window(window) {}
}; // namespace engine
