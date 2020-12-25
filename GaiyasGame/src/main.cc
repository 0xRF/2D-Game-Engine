#include <engine.hh>
#include <input.hh>

using namespace engine;

static Engine* instance = nullptr;



int main(int argc, char** argv){

    instance = Engine::initialize();

    instance->subscribe_to_update((updatefn)[] (float deltaTime) -> void {
        if(Input::GetKeyDown(KeyCode::A))
            instance->stop();
    });

    instance->run();

    return 0;
}
