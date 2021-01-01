#include "common.hh"

namespace engine {
class TextureManager;

class Texture {

public:
    const std::string get_name();
    const uint32_t get_width();
    const uint32_t get_height();
    const std::pair<uint32_t, uint32_t> get_dimensions();
    void *m_handle;

private:
    int32_t m_width;
    int32_t m_height;
    std::filesystem::path m_file;
    Texture(const std::filesystem::path file, void* handle);

    friend TextureManager;
};

} // namespace engine
