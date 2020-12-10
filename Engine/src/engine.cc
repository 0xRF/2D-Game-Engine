#include "../include/engine.hh"
#include "../include/window.hh"
#include "../include/input.hh"
#include "../include/log.hh"
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

        if (!input::initialize(instance)) {
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
        while(m_alive) {

            for (auto fn : m_update_queue)
                fn();

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
};
