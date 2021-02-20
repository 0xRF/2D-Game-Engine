#pragma once

#include <filesystem>
#include <jsoncons/json.hpp>

template <typename T> struct Resource {
  std::filesystem::path m_path;
  T m_contents;

  Resource(T content, std::filesystem::path path)
      : m_contents(content), m_path(path) {}

  json _json() {
    return json({
            std::string(typeid(T).name()), {
                        {"content", m_contents}, 
                        {"path", m_path.string().c_str()}
                    }
            });
  }
};


