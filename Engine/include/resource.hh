#pragma once

#include <json/json.h>

#include <filesystem>

template <typename T> struct Resource {
  std::filesystem::path m_path;
  T Get() { return m_contents; }

  Resource(T content, std::filesystem::path path)
      : m_contents(content), m_path(path) {}

private:
  T m_contents;
};
