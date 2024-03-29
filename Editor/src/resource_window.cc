#include "../include/resource_window.hh"
#include "log.hh"
#include <imgui.h>
#include <imfilebrowser.h>
#include <resource_manager.hh>
#include <vector.hh>
#include <window.hh>

ImGui::FileBrowser fileDialog;
static const char *current_item = NULL;
std::vector<std::string> types;

using namespace engine;

void ResourceWindow::update(float dt, Scene &scene){};
void ResourceWindow::update_end(float dt, Scene &scene){};
void ResourceWindow::on_render(Scene &scene) {

  ImGui::Begin("Tree");
  {
    if (ImGui::BeginCombo("Add Resource Of Type", current_item,
                          ImGuiComboFlags_NoArrowButton)) {
      for (int n = 0; n < types.size(); n++) {
        bool is_selected = (types[n].compare(std::string(current_item)) == 0);
        if (ImGui::Selectable(types[n].c_str(), is_selected))
          current_item = types[n].c_str();
        if (is_selected)
          ImGui::SetItemDefaultFocus();
      }
      ImGui::EndCombo();
    }

    if (ImGui::Button("Add"))
      fileDialog.Open();

    if (ImGui::Button("Update JSON")) {
      ResourceManager::DebugPrintResourceFile();
      ResourceManager::SaveResourceFile();
    }

    fileDialog.Display();
  }
  ImGui::End();

  if (fileDialog.HasSelected() && fileDialog.IsOpened()) {
    ResourceManager::AddResource(
        SimpleResource(fileDialog.GetSelected(), std::string(current_item)));
    fileDialog.Close();
    fileDialog.ClearSelected();
  }
};
void ResourceWindow::scene_end(Scene& scene){};
void ResourceWindow::scene_load(Scene& scene) {
  types = ResourceManager::GetResouceTypes();
  current_item = types[0].c_str();
};
void ResourceWindow::shutdown(Scene& scene){};
