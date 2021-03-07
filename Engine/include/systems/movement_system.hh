#pragma once

#include "../system.hh"


namespace engine {

namespace systems {

class MovementSystem : public System {

public:
    static MovementSystem *create(Engine *engine);


private:
    static MovementSystem *m_instance;
    static Engine* m_engine;

    void update(float dt, const Scene& scene);
    void update_end(float dt, const Scene scene);
    void scene_end(const Scene& scene);
    void scene_load(const Scene& scene);
    void shutdown(const Scene& scene);
    void render_begin(const Scene& scene);
    void on_render(const Scene& scene);
};

} // namespace internal
} // namespace engine
