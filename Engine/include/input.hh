#pragma once

#include "common.hh"

union SDL_Event;

namespace engine {
    class Engine;

    class Input {
    public:
        static bool initialize(Engine *instance);
        static bool GetKeyDown();
    private:
        static void handle_key_down(const SDL_Event &event);
        static void handle_key_up(const SDL_Event &event);
        static void handle_new_frame(float deltaTime);
    };
}
