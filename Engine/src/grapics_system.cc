#include "../include/common.hh"
#include "../include/components/renderer.hh"
#include "../include/components/transform.hh"
#include "../include/engine.hh"
#include "../include/log.hh"
#include "../include/window.hh"
#include "../internal/graphics_system.hh"
#include <SDL.h>
#include <SDL_image.h>
#include <functional>

namespace engine::internal {

GraphicsSystem *GraphicsSystem::m_instance = nullptr;

GraphicsSystem *GraphicsSystem::create(Engine *engine)
{
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
        logl("Failed to create renderer %s", SDL_GetError());
        delete m_instance;
        return nullptr;
    }

    return m_instance;
}

GraphicsSystem::GraphicsSystem()
{
}

void GraphicsSystem::render(entt::registry &registry)
{

    auto view = registry.view<const Transform, Renderer>();
    view.each([&](const Transform transform, Renderer renderer) {
        Rect rect(transform.positon, renderer.texture->get_width(),
                  renderer.texture->get_height());

        SDL_RenderCopyEx(m_renderer, (SDL_Texture *)renderer.texture->handle,
                         (SDL_Rect *)renderer.mapping, (SDL_Rect *)&rect,
                         transform.rotation, NULL, SDL_FLIP_NONE);
    });
}
void GraphicsSystem::update(float dt, entt::registry &registry)
{
}
void GraphicsSystem::update_end(entt::registry &registry)
{
}
void GraphicsSystem::scene_end(entt::registry &registry)
{
}
void GraphicsSystem::scene_load(entt::registry &registry)
{
}
void GraphicsSystem::shutdown(entt::registry &registry)
{
}

} // namespace engine::internal

