#pragma once

#include "common.hh"

union SDL_Event;
namespace engine {
    class Window;
    struct Frame;

    typedef void (*updatefn)(float deltaTime);
    typedef void (*eventfn)(const SDL_Event& event);

    class Engine {
    public:
        static Engine* initialize();

        Window *get_window() const;

        void run();

        void stop();

        void subscribe_to_update(updatefn func);
        void subscibe_to_event(uint32_t type, eventfn func);

    private:
        Window *m_window = nullptr;
        bool m_alive = false;
        std::vector<updatefn> m_update_queue{};
        std::vector<std::pair<uint32_t, eventfn>> m_event_queue{};

        Engine(){}
        ~Engine();

    };
};