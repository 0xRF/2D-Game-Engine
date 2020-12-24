#include"../include/input.hh"
#include "../include/log.hh"
#include "../include/frame.hh"
#include "../include/engine.hh"
#include <SDL.h>
#include <map>

namespace engine {

    enum KeyState{
        NONE = 0,
        DOWN,
        PRESSED
    };

    std::map<SDL_Keycode, KeyState> m_key_states{};

    void Input::handle_new_frame(float deltaTime){
        for(auto key : m_key_states)
            if(key.second == KeyState::PRESSED)
                m_key_states[key.first] = KeyState::NONE;
    }


    void Input::handle_key_up(const SDL_Event& event) {
        m_key_states[event.key.keysym.sym] = KeyState::PRESSED;
    }

    void Input::handle_key_down(const SDL_Event& event) {
        m_key_states[event.key.keysym.sym] = KeyState::DOWN;
    }

    bool Input::initialize(Engine* instance) {
        if(SDL_InitSubSystem(SDL_INIT_EVENTS) != 0){
            log("Failed to initialize input %s", SDL_GetError());
            return false;
        }
        instance->subscribe_to_update((updatefn)&handle_new_frame);
        instance->subscibe_to_event(SDL_EventType::SDL_KEYUP, (eventfn)&handle_key_up);
        instance->subscibe_to_event(SDL_EventType::SDL_KEYDOWN, (eventfn)&handle_key_down);

        return true;
    }
}