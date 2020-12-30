 #include "common.hh"

namespace engine {
class Texture;
class Engine;

class TextureManager {
    public:
    static std::shared_ptr<Texture> Load(const std::filesystem::path file);

private:
    static TextureManager* create(Engine* engine);
    TextureManager();
    static TextureManager* m_instance;
    Engine* m_engine;
    friend Engine;
};
}; // namespace engine
