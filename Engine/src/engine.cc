#include "../include/engine.hh"
#include "../include/window.hh"
#include "../include/input.hh"
#include "../include/log.hh"
#include "../include/frame.hh"
#include <SDL.h>

namespace engine {

    Engine* Engine::initialize() {

        Engine* instance = new Engine;

        if (SDL_Init(0) != 0) {
            log("Failed to init sdl");
            delete instance;
            return nullptr;
        }

        if (!Window::initialize()) {
            log("Failed to init Window");
            delete instance;
            return nullptr;
        }
        instance->m_window = Window::create("Test", 1280, 720);

        if (!Input::initialize(instance)) {
            log("Failed to init input");
            delete instance;
            return nullptr;
        }
        return instance;
    }

     Window *Engine::get_window() const{
        return m_window;
    }

    void Engine::run() {
        m_alive = true;
        Frame frame = Frame();

        while(m_alive) {

            SDL_Event event;
            while (SDL_PollEvent(&event))
                for(auto fn : m_event_queue)
                    if(event.type == fn.first)
                        fn.second(event);

            Uint32 t1 = SDL_GetTicks();

            for (auto fn : m_update_queue)
                fn(frame.deltaTime);

            Uint32 t2 = SDL_GetTicks();

            frame.deltaTime = (float)(t2 - t1)/1000;
        }
    }

    void Engine::stop() {
        if(!m_alive)
            log("Already shutting down");
        m_alive = false;
    }

    void Engine::subscribe_to_update(const updatefn func) {
        m_update_queue.push_back(func);
    }

    Engine::~Engine() {
        delete m_window;
    }

    void Engine::subscibe_to_event(uint32_t type, eventfn func) {
        m_event_queue.emplace_back(type, func);
    }
};
