#include "../include/texture_manager.hh"
#include "../include/engine.hh"
#include "../include/graphics.hh"
#include "../include/log.hh"
#include "../include/texture.hh"
#include <SDL_image.h>
#include <functional>
namespace engine {

std::shared_ptr<Texture>
TextureManager::Load(const std::filesystem::path file) {

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
      (SDL_Renderer *)Graphics::GetRenderer(), surface);

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
