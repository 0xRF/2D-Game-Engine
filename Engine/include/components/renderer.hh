#include "../common.hh"
#include "../texture.hh"

struct Renderer
{
    std::shared_ptr<engine::Texture> texture;
    Rect* mapping;

    Renderer(std::shared_ptr<engine::Texture> _texture) : texture(_texture), mapping(NULL){ 
    }

};
