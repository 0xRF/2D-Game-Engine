#include "../include/inspector_window.hh"
#include "../include/components/tag.hh"
#include "entt/core/fwd.hpp"
#include <entt/core/type_info.hpp>
#include <entt/core/type_traits.hpp>
#include <entt/entity/registry.hpp>
#include <entt/entt.hpp>
#include <functional>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <window.hh>

#include <components/position.hh>
#include <components/transform.hh>
#include <entt/core/hashed_string.hpp>

#include "../include/entity.hh"
#include "../include/scene.hh"
using namespace engine;

static Entity *selected_entity = nullptr;

namespace engine {
void InspectorWindow::scene_load(Scene &scene) {

  auto factory = entt::meta<Position>()
                     .type()
                     .prop("Component"_hs)
                     .prop("ComponentName"_hs, "Position");
  //.data(&Position::x>("x"_hs);
  //.data(&Position::y>("y"_hs);
};

void InspectorWindow::InspectEntity(Scene &scene) {
  Tag &tag = selected_entity->get<Tag>();
  ImGui::LabelText("", "%s\n", tag.name.c_str());

  ImGui::InputText("Name:", &tag.name);

  scene.get_entity_list().visit(
      *selected_entity, [&](const auto component) -> void {
        const entt::meta_type type = entt::resolve_type(component);
      });
}

void InspectorWindow::update(float dt, Scene &scene){};
void InspectorWindow::update_end(float dt, Scene &scene) {}
void InspectorWindow::on_render(Scene &scene) {

  ImGui::SetNextWindowPos({0, 0}, ImGuiCond_Always);
  ImGui::SetNextWindowSizeConstraints(
      {(float)engine::Window::GetWidth() / 5,
       (float)engine::Window::GetHeight()},
      {(float)engine::Window::GetWidth(), (float)engine::Window::GetHeight()});

  if (ImGui::Begin("Inspector")) {
    if (ImGui::Button("Add Entity")) {
      auto entity = scene.create_entity();
      size_t size = scene.get_entity_list().size();
      entity.add<Tag>(std::string("Entity: ") + std::to_string(size));
      ImGui::End();
      return;
    }
    ImGui::SameLine();
    if (ImGui::Button("Remove Entity")) {
      selected_entity->destroy();
      selected_entity = nullptr;
      ImGui::End();
      return;
    }

    auto view = scene.get_entity_list().view<Tag>();
    for (auto &entity_id : view) {
      Entity entity(entity_id, &scene);
      Tag &tag = entity.get<Tag>();
      bool selected =
          (selected_entity != nullptr && entity == *selected_entity);
      if (ImGui::Selectable(tag, selected)) {
        selected_entity = &entity;
      }
    }
  }

  if (selected_entity == nullptr) {
    ImGui::End();
    return;
  }
  if (ImGui::CollapsingHeader("Selected Entity")) {
    InspectEntity(scene);
  }
  ImGui::End();
};
void InspectorWindow::scene_end(Scene &scene){};
void InspectorWindow::shutdown(Scene &scene){};

} // namespace engine
