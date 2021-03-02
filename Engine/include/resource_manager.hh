#pragma once

#include "../include/common.hh"
#include "../include/resource.hh"
#include <algorithm>

class ResourceManager {
public:
  static void SetResouceFile(std::filesystem::path resource_directory);

  template <typename T> static std::vector<Resource<T>> GetAllResoucesOfType() {
    std::vector<Resource<T>> values{};
    std::string target_type = std::string(typeid(T).name());
    for (SimpleResource res : m_resource_list) {
      if (res.m_type.compare(target_type) != 0)
        //              values.push_back(*reinterpret_cast<Resource<T>*>(&res));
        values.push_back(static_cast<Resource<T>>(res));
    }

    return values;
  }

  template <typename T> static void AddResourceType() {
    if (std::find(m_type_list.begin(), m_type_list.end(),
                  std::string(typeid(T).name())) != m_type_list.end())
      m_type_list.push_back(std::string(typeid(T).name()));
  }

  static std::vector<std::string> GetResouceTypes();

  template <typename T> static void AddResource(T resource) {
    AddResource((SimpleResource)resource);
  }
  static void AddResource(SimpleResource resource);
  static void RemoveResource(std::filesystem::path path);
  static void SaveResourceFile();
  static void DebugPrintResourceFile();

  template <typename T>
  static std::vector<Resource<T>>
  GetResouceByName(const std::string &resource) {}

private:
  static std::vector<SimpleResource> m_resource_list;
  static std::vector<std::string> m_type_list;
  static std::filesystem::path m_resources_file;
};
