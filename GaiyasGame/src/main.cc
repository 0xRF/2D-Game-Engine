#include <engine.hh>
#include <input.hh>
int main(int argc, char** argv){

    engine::Engine* instance = engine::Engine::initialize();

    instance->run();

    instance->subscribe_to_update((engine::updatefn)[] (float deltaTime) -> void {

        engine::Input::


    });

    return 0;
}
