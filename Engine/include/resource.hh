#pragma once

#include "./texture_manager.hh"
#include <filesystem>
#include <jsoncons/json.hpp>

struct SimpleResource {
  std::string m_path;
  std::string m_type;

  SimpleResource(const std::string &path, std::string type)
      : m_path(path), m_type(type) {}

  SimpleResource() {}
  SimpleResource(const SimpleResource &res)
      : m_path(res.m_path), m_type(res.m_type) {}
};

JSONCONS_ALL_MEMBER_TRAITS(SimpleResource, m_path, m_type);

template <typename T> struct Resource : public SimpleResource {

  Resource(std::string path)
      : m_instance(nullptr),
        SimpleResource(path, std::string(typeid(T).name())) {}

  Resource(SimpleResource res) : m_instance(nullptr), SimpleResource(res) {}
  // template < typename = typename std::enable_if< std::is_same>::type >
  template <std::enable_if<std::is_same<T, engine::Texture>::value>>
  std::shared_ptr<T> Get() {
    if (m_instance == nullptr)
      m_instance = engine::TextureManager::Load(m_path);
    return m_instance;
  }

  std::shared_ptr<T> Get() { return nullptr; }

private:
  std::shared_ptr<T> m_instance;
};
