#pragma once

#include <filesystem>

template <typename T> struct Resource {
  std::filesystem::path m_path;
  T m_contents;

  Resource(T content, std::filesystem::path path)
      : m_contents(content), m_path(path) {}

};
