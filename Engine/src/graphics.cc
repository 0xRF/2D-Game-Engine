#include "../include/graphics.hh"
#include "../include/common.hh"
#include "../include/components/position.hh"
#include "../include/components/renderer.hh"
#include "../include/components/rotatable.hh"
#include "../include/components/scale.hh"
#include "../include/engine.hh"
#include "../include/log.hh"
#include "../include/window.hh"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <functional>
#include <imgui.h>
#include <imgui_sdl.h>

namespace engine {
SDL_Renderer *Graphics::m_renderer = nullptr;
void Graphics::DrawLine(Vector2 a, Vector2 b) {
  SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 125);
  SDL_RenderDrawLineF(m_renderer, a.x, a.y, b.x, b.y);
}

void *Graphics::GetRenderer() { return (void *)m_renderer; }

bool Graphics::Initialize() {
  int flags = IMG_INIT_JPG | IMG_INIT_JPG;
  if (!(IMG_Init(flags) & flags)) {
    log("Failed to init img");
    return false;
  }

  m_renderer = SDL_CreateRenderer((SDL_Window *)Window::GetWindowHandle(), -1,
                                  SDL_RENDERER_ACCELERATED);
  if (!m_renderer)
    return false;

  ImGui::CreateContext();

  ImGuiSDL::Initialize(m_renderer, Window::GetWidth(), Window::GetHeight());

  Engine::SubscibeToEvent(SDL_WINDOWEVENT, WindowResized);

  return true;
}

void Graphics::WindowResized(SDL_Event e) {

  ImGuiIO &io = ImGui::GetIO();

  if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
    io.DisplaySize.x = static_cast<float>(e.window.data1);
    io.DisplaySize.y = static_cast<float>(e.window.data2);
  } else if (e.type == SDL_MOUSEWHEEL) {
    io.MouseWheel = static_cast<float>(e.wheel.y);
  } else if (e.type == SDL_KEYDOWN) {
  }
}

void Graphics::render_begin(entt::registry &registry) {
  ImGuiIO &io = ImGui::GetIO();
  int mouseX, mouseY;
  const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

  io.DeltaTime = 1.0f / 60.0f;
  io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
  io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
  io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

  ImGui::NewFrame();
  SDL_SetRenderDrawColor(m_renderer, 114, 144, 154, 255);
  SDL_RenderClear(m_renderer);

  auto view =
      registry.view<const Position, Renderer, const Rotatable, const Scale>();

  view.each([&](const Position pos, Renderer renderer, const Rotatable rotation,
                const Scale scale) {
    int width = renderer.width * scale;
    int height = renderer.height * scale;
    Vector2 posit = {pos.x - width / 2.0f, pos.y - height / 2.0f};
    Rect rect(posit, width, height);

    SDL_RenderCopyEx(m_renderer, (SDL_Texture *)renderer.texture->m_handle,
                     (SDL_Rect *)renderer.mapping, (SDL_Rect *)&rect,
                     rotation.rotation, NULL, SDL_FLIP_NONE);
  });
}

void Graphics::render_end() {
  ImGui::Render();
  ImGuiSDL::Render(ImGui::GetDrawData());
  SDL_RenderPresent(m_renderer);
}

} // namespace engine
