#include "../include/resource_manager.hh"
#include <fstream>
#include <sstream>

std::filesystem::path ResourceManager::m_resources_file;

std::vector<std::filesystem::path> ResourceManager::files;

void ResourceManager::SetResouceFile(std::filesystem::path resource_directory) {
  m_resources_file = resource_directory;

  std::ifstream ifs(resource_directory);

  std::string jsonstr((std::istreambuf_iterator<char>(ifs)),
                      std::istreambuf_iterator<char>());

  //auto j = json::parse(jsonstr);
}
