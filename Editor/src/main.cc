#include "vector.hh"
#include <components/box_collider.hh>
#include <components/component.hh>
#include <components/position.hh>
#include <components/renderer.hh>
#include <components/rigidbody.hh>
#include <components/rotatable.hh>
#include <engine.hh>
#include <graphics.hh>
#include <imgui.h>
#include <input.hh>
#include <log.hh>
#include <math.hh>
#include <texture_manager.hh>
#include <window.hh>

#include <resource.hh>
#include <resource_manager.hh>

using namespace engine;

static Engine *instance = nullptr;

int main(int argc, char **argv) {

  instance = Engine::initialize();

  ResourceManager::SetResouceFile("res");

  instance->subscribe_to_start((startfn)[](entt::registry & registry)->void{});
  instance->subscribe_to_update(
      [&](entt::registry &registry, float dt) -> void {
        if (Input::GetKeyDown(KeyCode::ESCAPE))
          instance->stop();
      });

  std::vector<Resource<int>> meme;
  std::string json_str;

  instance->subscribe_to_render([&]() -> void {
    ImVec2 a;
    ImGui::SetNextWindowPos({0, 0}, ImGuiCond_Always);
    ImGui::SetNextWindowSizeConstraints(
        {(float)Window::GetWidth() / 5, (float)Window::GetHeight()},
        {(float)Window::GetWidth(), (float)Window::GetHeight()});
    ImGui::Begin("Tree");
    {
      if (ImGui::Button("Add")) {
        meme.push_back(Resource<int>((int)(rand() * 32), "MEME"));
      }
      if (ImGui::Button("Update JSON")) {
        for (auto itm : meme) {
          json j = itm._json();

        }
      }
      std::string s = jObj.dump();
      ImGui::Text("%s", s.c_str());
    }
    ImGui::End();
  });
  instance->run();

  return 0;
}
