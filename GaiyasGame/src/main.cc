#include <engine.hh>
#include <input.hh>
#include <log.hh>
#include <texture_manager.hh>
#include <components/component.hh>

using namespace engine;

static Engine *instance = nullptr;

int main(int argc, char **argv)
{

    instance = Engine::initialize();

//    TextureManager::Lo

    instance->subscribe_to_update((updatefn)[](float deltaTime)->void {
        if (Input::GetKeyDown(KeyCode::A)) instance->stop();

        if (Input::GetKeyUp(KeyCode::F)) instance->stop();


    }); 
    instance->run();

    return 0;
}
