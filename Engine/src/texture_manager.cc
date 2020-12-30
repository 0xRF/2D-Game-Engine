#include "../include/texture_manager.hh"
#include "../internal/graphics_system.hh"
#include "../include/engine.hh"
#include "../include/log.hh"
#include <SDL_image.h>
#include <functional>
namespace engine {

TextureManager *TextureManager::m_instance = nullptr;

TextureManager* TextureManager::create(Engine *engine)
{
    if (m_instance) {
        log("ComponentManager already initalized");
        return nullptr;
    }
    m_instance = new TextureManager;

    return m_instance;
}

TextureManager::TextureManager()
{
}


std::shared_ptr<Texture> TextureManager::Load(const std::filesystem::path file){
    if(!std::filesystem::exists(file)){
        log("file does not exist");
        return nullptr;
    }


    SDL_Surface* surface = nullptr;
    surface = IMG_Load(file.c_str());
    if(!surface)    
    {   
        log("Couldn't load file %s", file.c_str());
        return nullptr;
    }


//    m_instance->m_engine->m_graphics->m_renderer


    return nullptr;
}

} // namespace engine
