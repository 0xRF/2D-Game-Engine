#pragma once

#include "common.hh"

namespace engine {
    class Window;

    typedef void* (*updatefn)(void);

    class Engine {
    public:
        static Engine* initialize();

        Window *get_window() const;

        void run();

        void stop();

        void subscribe_to_update(updatefn func);

    private:
        Window *m_window = nullptr;
        bool m_alive = false;
        std::vector<updatefn> m_update_queue{};

        Engine(){}
        ~Engine();

    };
};