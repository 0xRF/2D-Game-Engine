
#include "vector.hh"
struct SDL_Renderer;
namespace engine {
namespace internal {
class GraphicsSystem;
}
class Graphics {
public:
  static void DrawLine(Vector2 a, Vector2 b);

private:
  static SDL_Renderer *renderer;
  friend internal::GraphicsSystem;
};
} // namespace engine
