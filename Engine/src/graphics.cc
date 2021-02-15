#include "../include/graphics.hh"
#include "SDL_render.h"
#include <SDL_render.h>

namespace engine {
SDL_Renderer *Graphics::renderer = nullptr;
void Graphics::DrawLine(Vector2 a, Vector2 b) {
  SDL_SetRenderDrawColor(renderer, 255,0,0, 125);
  SDL_RenderDrawLineF(renderer, a.x, a.y, b.x, b.y);
}
} // namespace engine
