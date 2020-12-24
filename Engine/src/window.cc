#include "../include/window.hh"
#include "../include/log.hh"
#include <SDL.h>
#include <utility>

namespace engine {

    bool Window::initialize() {
        if(SDL_InitSubSystem(SDL_INIT_VIDEO) != 0){
            log("Failed to initialize Window %s", SDL_GetError());
            return false;
        }
        return true;
    }

    Window *Window::create(const std::string &name, unsigned int w, unsigned int h) {

        SDL_Window* window = SDL_CreateWindow(name.c_str(),
                                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_ALLOW_HIGHDPI);

        if(!window)
        {
            log("Failed to create Window\n %s\n", SDL_GetError());
            return nullptr;
        }

        return new Window(name, window);;
    }

    const std::string &Window::get_name(void) const {
        return m_name;
    }

    void Window::set_name(const std::string &name) {
        m_name = name; // Todo add string santiation
    }

    Window::Window(std::string name, SDL_Window *window) : m_name(std::move(name)), m_window(window) {}
};