#include <engine.hh>

int main(int argc, char** argv){

    engine::Engine* instance = engine::Engine::initialize();

    instance->run();

    return 0;
}
