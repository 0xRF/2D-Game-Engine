#pragma once

#include "../include/common.hh"
#include "../include/resource.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ResourceManager {
public:
  static void SetResouceFile(std::filesystem::path resource_directory);

  template <typename T> static std::vector<Resource<T>> GetAllResoucesOfType();

  template <typename T>
  static std::vector<Resource<T>> GetResouceByName(std::string resource) {}

private:
  static std::vector<std::filesystem::path> files;
  static std::filesystem::path m_resources_file;
};
