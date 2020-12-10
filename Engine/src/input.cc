#include "../include/input.hh"
#include "../include/log.hh"
#include "../include/engine.hh"

#include <SDL.h>
namespace engine {

    void handle_input() {

        SDL_Event event;
        while (SDL_PollEvent(&event)){
            
        }


    }


    bool input::initialize(Engine* instance) {
        if(SDL_InitSubSystem(SDL_INIT_EVENTS) != 0){
            log("Failed to initialize input %s", SDL_GetError());
            return false;
        }
        instance->subscribe_to_update((updatefn)&handle_input);
        return true;
    }
}