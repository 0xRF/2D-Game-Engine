#pragma once

#include "../system.hh"


namespace engine {

namespace systems {

class MovementSystem : public System {

public:

private:

    void update(float dt, Scene& scene);
    void update_end(float dt, Scene& scene);
    void scene_end(Scene& scene);
    void scene_load(Scene& scene);
    void shutdown(Scene& scene);
    void render_begin(Scene& scene);
    void on_render(Scene& scene);
};

} // namespace internal
} // namespace engine
