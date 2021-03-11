#pragma once

#include "log.hh"
#include "scene.hh"
#include <entt/entt.hpp>

namespace engine {

class Entity {
public:
  template <typename T, typename... Args> T &add(Args &&...args) {
    DEBUG_ASSERT(has<T>());
    return m_scene->m_registry.emplace<T>(m_handle,
                                          std::forward<Args>(args)...);
  }

  template <typename T> bool has() {
    DEBUG_ASSERT(m_scene != nullptr);
    return m_scene->m_registry.has<T>(m_handle);
  }

  void destroy() {
    m_scene->get_entity_list().remove(m_handle);
    m_handle = entt::null;
  }

  template <typename T> T &get() {
    DEBUG_ASSERT(has<T>());
    return m_scene->m_registry.get<T>(m_handle);
  }

  template <typename T> T &remove() {
    DEBUG_ASSERT(has<T>());
    return m_scene->m_registry.remove<T>(m_handle);
  }
  operator bool() const { return m_handle != entt::null; }
  operator entt::entity() const { return m_handle; }
  bool operator==(const Entity &other) { return m_handle == other.m_handle; }

  Entity(entt::entity id, Scene *scene) : m_scene(scene), m_handle(id) {}

  Entity(Scene *scene) : m_scene(scene) {
    m_handle = m_scene->m_registry.create();
  }

private:
  Scene *m_scene;
  entt::entity m_handle{entt::null};
  Entity() = delete;
  friend Scene;
};
} // namespace engine
