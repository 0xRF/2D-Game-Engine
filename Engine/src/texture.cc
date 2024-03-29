#include "../include/texture.hh"
#include "../include/log.hh"
#include <SDL.h>
#include <SDL_image.h>
namespace engine {

const std::string Texture::get_name()
{
    return m_file.filename().string();
}

const uint32_t Texture::get_width()
{
    return m_width;
}
const uint32_t Texture::get_height()
{
    return m_height;
}
const std::pair<uint32_t, uint32_t> Texture::get_dimensions()
{
    return std::pair<uint32_t, uint32_t>{m_width, m_height};
}

Texture::Texture(const std::filesystem::path file, void* _handle) : m_width(0), m_height(0), m_file(file), m_handle(_handle)
{
    SDL_QueryTexture((SDL_Texture*)_handle, nullptr, nullptr, (int*)&m_width, (int*)&m_height);
}
} // namespace engine
