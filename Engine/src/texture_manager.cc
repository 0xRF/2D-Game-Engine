#include "../include/texture_manager.hh"
#include "../include/engine.hh"
#include "../include/log.hh"
#include "../include/texture.hh"
#include "../internal/graphics_system.hh"
#include <SDL_image.h>
#include <functional>
namespace engine {

TextureManager *TextureManager::m_instance = nullptr;

TextureManager *TextureManager::create(Engine *engine)
{
    logl("Creating TextureManager");
    if (m_instance) {
        log("ComponentManager already initalized");
        return nullptr;
    }
    m_instance = new TextureManager;
    m_instance->m_engine = engine;

    return m_instance;
}

TextureManager::TextureManager()
{
}

std::shared_ptr<Texture> TextureManager::Load(const std::filesystem::path file)
{

    if (!std::filesystem::exists(file)) {
        logl("file does not exist");
        return nullptr;
    }

    SDL_Surface *surface = nullptr;
    surface = IMG_Load(file.c_str());
    if (!surface) {
        log("Couldn't load file %s", file.c_str());
        return nullptr;
    }

    SDL_Texture *texture = NULL;
    texture = SDL_CreateTextureFromSurface(
        m_instance->m_engine->m_graphics->m_renderer, surface);

    if (!texture) {
        logl("Failed to convet sruface to texture");
        return nullptr;
    }

    std::shared_ptr<Texture> ptr =
        std::make_shared<Texture>(Texture(file, (void *)texture));
    logl("Loaded texture %p %s", ptr.get(), file.filename().c_str());
    return ptr;
}

} // namespace engine
