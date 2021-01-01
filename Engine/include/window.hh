#pragma once

#include "common.hh"

struct SDL_Window;

namespace engine
{
    namespace internal{
        class GraphicsSystem;
    }


    class Window {
    public:
        static Window *create(const std::string &name, unsigned int width, unsigned int height);
        static bool initialize();

        const std::string &get_name(void) const;
        void set_name(const std::string &name);

        uint32_t get_width();
        uint32_t get_height();

    private:

        Window(std::string name, SDL_Window *window);
        friend internal::GraphicsSystem;

        std::string m_name;
        SDL_Window* m_window;
    };
}
