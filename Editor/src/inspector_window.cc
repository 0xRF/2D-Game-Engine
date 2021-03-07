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

static const entt::entity *current_item = nullptr;

namespace {
void InspectorWindow::scene_load(entt::registry &registry) {

  auto factory = entt::meta<Position>()
                     .type()
                     .prop("Component"_hs)
                     .prop("ComponentName"_hs, "Position");
  //.data(&Position::x>("x"_hs);
  //.data(&Position::y>("y"_hs);
};

void InspectorWindow::InspectEntity(const Scene& scene) {
  auto &ee = scene.m_registry.get<Tag>(*current_item);
  ImGui::LabelText("", "%s\n", ee.name.c_str());

  ImGui::InputText("Name:", &ee.name);

  registry.visit(*current_item, [&](const auto component) -> void {
    const entt::meta_type type = entt::resolve_type(component);

    if (type.is_class() && type.prop("Component"_hs)) {
    }
  });
}

void InspectorWindow::update(float dt, entt::registry &registry){};
void InspectorWindow::update_end(float dt, entt::registry &registry){};
void InspectorWindow::on_render(entt::registry &registry) {

  ImGui::SetNextWindowPos({0, 0}, ImGuiCond_Always);
  ImGui::SetNextWindowSizeConstraints(
      {(float)engine::Window::GetWidth() / 5,
       (float)engine::Window::GetHeight()},
      {(float)engine::Window::GetWidth(), (float)engine::Window::GetHeight()});

  if (ImGui::Begin("Inspector")) {
    if (ImGui::Button("Add Entity")) {
      auto entity = registry.create();
      size_t size = registry.size();

      ee.entity_name = std::string("Entity: ") + std::to_string(size);
      registry.emplace<EditorEntity>(entity, ee);
      ImGui::End();
      return;
    }
    ImGui::SameLine();
    if (ImGui::Button("Remove Entity")) {
      registry.destroy(*current_item);
      current_item = nullptr;
      ImGui::End();
      return;
    }

    auto view = registry.view<EditorEntity>();
    for (auto &entity : view) {
      EditorEntity &eent = registry.get<EditorEntity>(entity);
      bool selected = (current_item != nullptr && entity == *current_item);
      if (ImGui::Selectable(eent.entity_name.c_str(), selected)) {
        current_item = &entity;
      }
    }
  }

  if (current_item == nullptr) {
    ImGui::End();
    return;
  }
  if (ImGui::CollapsingHeader("Selected Entity")) {
    InspectEntity(registry);
  }
  ImGui::End();
};
void InspectorWindow::scene_end(entt::registry &registry){};
void InspectorWindow::shutdown(const Scene &scene){};

} // namespace
