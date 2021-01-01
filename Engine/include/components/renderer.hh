#include "../common.hh"
#include "../texture.hh"
#include "../log.hh"

struct Renderer {
    std::shared_ptr<engine::Texture> texture;
    Rect *mapping;
    float width;
    float height;

    Renderer(std::shared_ptr<engine::Texture> _texture)
        : texture(_texture), mapping(NULL)
    {
        width = _texture->get_width();
        height = _texture->get_height();
    }

    inline void scale(float scale)
    {
        width = width * scale;
        height = height * scale;
        engine::logl("scaled");
    }
};
