#include "../include/resource_manager.hh"
#include "../include/log.hh"
#include "../include/texture.hh"
#include <fstream>
#include <ostream>
#include <sstream>

std::filesystem::path ResourceManager::m_resources_file;

std::vector<SimpleResource> ResourceManager::m_resource_list{};
std::vector<std::string> ResourceManager::m_type_list{ typeid(engine::Texture).name()};

void ResourceManager::SetResouceFile(std::filesystem::path resource_directory) {
  m_resources_file = resource_directory;

  if (!std::filesystem::exists(resource_directory)){
    engine::logl("File does not exist");
    return;
  }

  std::ostringstream ss;
  std::ifstream ifs(resource_directory, std::ios::in | std::ios::binary);
  ss << ifs.rdbuf();
  ifs.close();

  std::string jsonstr(ss.str());

  auto resources = jsoncons::json::parse(jsonstr);

  for (auto res : resources.array_range()) {
    SimpleResource resource = res.as<SimpleResource>();
    if (!std::filesystem::exists(resource.m_path)) {
      engine::logl("Could not load file:\n %s", resource.m_path.c_str());
      continue;
    }
    m_resource_list.push_back(resource);
  }


  ///TODO FIX
  /*
  for (auto res : GetAllResoucesOfType<int>()) {
    engine::logl("A %s %s\n", res.m_type.c_str(), res.m_path.c_str());
  }
  */
}

std::vector<std::string> ResourceManager::GetResouceTypes() {
  return m_type_list;
}

void ResourceManager::AddResource(SimpleResource resource) {

  for (auto res : m_resource_list)
    if (res.m_path == resource.m_path)
      return;

  m_resource_list.push_back(resource);
}

void ResourceManager::RemoveResource(std::filesystem::path path) {}
void ResourceManager::SaveResourceFile() {

  std::ofstream resource_file(m_resources_file, std::ios::trunc);
  if (!resource_file.is_open())
    return;

  jsoncons::json j(jsoncons::json_array_arg);
  for (auto itm : m_resource_list)
    j.push_back((SimpleResource)itm);
  std::string s;
  j.dump_pretty(s);
  resource_file << s;
  resource_file.close();
}

void ResourceManager::DebugPrintResourceFile() {
  engine::logl("There are %d reosurce items", m_resource_list.size());
  jsoncons::json j(jsoncons::json_array_arg);
  for (auto itm : m_resource_list)
    j.push_back(itm);
  std::string s;
  j.dump_pretty(s);
  engine::logl("Resources: %s", s.c_str());
}
