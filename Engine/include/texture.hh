#include "common.hh"

namespace engine {

class Texture {

public:
        const std::string get_name();
        const uint32_t get_width();
        const uint32_t get_height();
        const std::pair<uint32_t, uint32_t> get_dimensions();
        void* handle; 
private:
    uint32_t m_width;
    uint32_t m_height;
    std::filesystem::path m_file;
    Texture();
};


} // namespace engine
