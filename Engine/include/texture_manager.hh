#pragma once

#include "common.hh"

namespace engine {
class Texture;
class Engine;

class TextureManager {
    public:
    static bool Initialize();
    static std::shared_ptr<Texture> Load(const std::filesystem::path file);
    TextureManager() = delete;
    TextureManager(const TextureManager&) = delete;

private:
    static TextureManager* m_instance;
    Engine* m_engine;
    friend Engine;
};
}; // namespace engine
