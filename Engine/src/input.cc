#include "../include/input.hh"
#include "../include/engine.hh"
#include "../include/log.hh"
#include "imgui.h"
#include <SDL.h>
#include <SDL_keycode.h>
#include <map>

namespace engine {

enum KeyState { NONE = 0, DOWN, UP };

std::map<SDL_Keycode, KeyState> m_key_states{};

void Input::post_update(Scene& scene, float dt) {
  for (auto key : m_key_states)
    if (key.second == KeyState::UP)
      m_key_states[key.first] = KeyState::NONE;
}

void Input::handle_key_up(const SDL_Event &event) {
  m_key_states[event.key.keysym.sym] = KeyState::UP;
}

void Input::handle_key_down(const SDL_Event &event) {
  m_key_states[event.key.keysym.sym] = KeyState::DOWN;
}

bool Input::Initialize() {
  if (SDL_InitSubSystem(SDL_INIT_EVENTS) != 0) {
    log("Failed to initialize input %s", SDL_GetError());
    return false;
  }
  Engine::SubscibeToEvent(SDL_EventType::SDL_KEYUP, (eventfn)&handle_key_up);
  Engine::SubscibeToEvent(SDL_EventType::SDL_KEYDOWN,
                          (eventfn)&handle_key_down);

  Engine::SubscribeToPostUpdate((updatefn)&post_update);

  ImGuiIO &io = ImGui::GetIO();
  io.KeyMap[ImGuiKey_Tab] = SDL_SCANCODE_TAB;
  io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
  io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
  io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
  io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
  io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
  io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
  io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
  io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
  io.KeyMap[ImGuiKey_Insert] = SDL_SCANCODE_INSERT;
  io.KeyMap[ImGuiKey_Delete] = SDL_SCANCODE_DELETE;
  io.KeyMap[ImGuiKey_Backspace] = SDL_SCANCODE_BACKSPACE;
  io.KeyMap[ImGuiKey_Space] = SDL_SCANCODE_SPACE;
  io.KeyMap[ImGuiKey_Enter] = SDL_SCANCODE_RETURN;
  io.KeyMap[ImGuiKey_Escape] = SDL_SCANCODE_ESCAPE;
  io.KeyMap[ImGuiKey_KeyPadEnter] = SDL_SCANCODE_KP_ENTER;

  return true;
}

bool Input::GetKeyDown(const KeyCode key) {
  if (m_key_states.count((SDL_KeyCode)key) > 0)
    return m_key_states[(SDL_KeyCode)key] == KeyState::DOWN;
  return false;
}

bool Input::GetKeyUp(KeyCode key) {
  if (m_key_states.count((SDL_KeyCode)key) > 0)
    return m_key_states[(SDL_KeyCode)key] == KeyState::UP;
  return false;
}
} // namespace engine
