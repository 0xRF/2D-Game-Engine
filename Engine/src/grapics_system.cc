#include "../include/common.hh"
#include "../include/components/position.hh"
#include "../include/components/renderer.hh"
#include "../include/components/rotatable.hh"
#include "../include/components/scale.hh"
#include "../include/engine.hh"
#include "../include/graphics.hh"
#include "../include/log.hh"
#include "../include/window.hh"
#include "../internal/graphics_system.hh"
#include <SDL.h>
#include <SDL_image.h>
#include <functional>
#include <imgui.h>
#include <imgui_sdl.h>

namespace engine::internal {

GraphicsSystem *GraphicsSystem::m_instance = nullptr;

GraphicsSystem *GraphicsSystem::create(Engine *engine) {
  logl("Creating GraphicsSystem");

  if (m_instance) {
    log("ComponentManager already initalized");
    return nullptr;
  }

  int flags = IMG_INIT_JPG | IMG_INIT_JPG;
  if (!(IMG_Init(flags) & flags)) {
    log("Failed to init img");
    return nullptr;
  }

  m_instance = new GraphicsSystem;

  m_instance->m_renderer = SDL_CreateRenderer(engine->get_window()->m_window,
                                              -1, SDL_RENDERER_ACCELERATED);
  if (!m_instance->m_renderer) {
    logl("failed to load renderer");
    logl("%s", SDL_GetError());
    return nullptr;
  }

  Graphics::renderer = m_instance->m_renderer;

  ImGui::CreateContext();
  ImGuiSDL::Initialize(m_instance->m_renderer,
                       engine->get_window()->get_width(),
                       engine->get_window()->get_height());

  engine->subscibe_to_event(SDL_WINDOWEVENT, [](SDL_Event e) {
    ImGuiIO &io = ImGui::GetIO();
    if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
      io.DisplaySize.x = static_cast<float>(e.window.data1);
      io.DisplaySize.y = static_cast<float>(e.window.data2);
    } else if (e.type == SDL_MOUSEWHEEL) {
      io.MouseWheel = static_cast<float>(e.wheel.y);
    }
  });

  if (!m_instance->m_renderer) {
    logl("Failed to create renderer %s", SDL_GetError());
    delete m_instance;
    return nullptr;
  }

  return m_instance;
}

GraphicsSystem::GraphicsSystem() {}

void GraphicsSystem::render_begin(entt::registry &registry) {
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
    Rect rect(posit, width, height );

    SDL_RenderCopyEx(m_renderer, (SDL_Texture *)renderer.texture->m_handle,
                     (SDL_Rect *)renderer.mapping, (SDL_Rect *)&rect,
                     rotation.rotation, NULL, SDL_FLIP_NONE);
  });
}

void GraphicsSystem::render_end() {
  ImGui::Render();
  ImGuiSDL::Render(ImGui::GetDrawData());
  SDL_RenderPresent(m_renderer);
}

void GraphicsSystem::update(float dt, entt::registry &registry) {}
void GraphicsSystem::update_end(float dt, entt::registry &registry) {}
void GraphicsSystem::scene_end(entt::registry &registry) {}
void GraphicsSystem::scene_load(entt::registry &registry) {}
void GraphicsSystem::shutdown(entt::registry &registry) {}

void GraphicsSystem::on_render(entt::registry &registry) {}
} // namespace engine::internal
