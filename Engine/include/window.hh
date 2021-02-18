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

        const static std::string &GetName(void);
        static void SetName(const std::string &name);

        static uint32_t GetWidth();
        static uint32_t GetHeight();

    private:
        static Window* m_instance;

        Window(std::string name, SDL_Window *window);
        friend internal::GraphicsSystem;

        std::string m_name;
        SDL_Window* m_window;
    };
}
