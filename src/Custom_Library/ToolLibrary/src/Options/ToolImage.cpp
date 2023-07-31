#include "ToolImage.hpp"

namespace TOOL_SL
{    
    Image::Image () : booba::Image(), SL::Image() {}

    Image::~Image() {};

    Image::Image(const std::string &path): booba::Image(), SL::Image()
    {
        loadFromFile(path);
    }


    Image::Image (const SL::Vector2d &shape, const SL::Color &color): 
        booba::Image(), SL::Image(shape, color) 
    {}

    Image::Image (const SL::Image &image) : booba::Image(), SL::Image(image) {}

    size_t Image::getH() 
    {
        return size_t(getSize().y_);
    }

    size_t Image::getW() 
    {
        return size_t(getSize().x_);
    }

    booba::Color Image::getPixel(size_t x, size_t y) 
    {
        SL::Color color = getPixel(SL::Vector2d(uint32_t(x), uint32_t(y)));
        return booba::Color(color.get_r(), color.get_b(), color.get_b(), color.get_a());
    }

    SL::Color Image::getPixel(SL::Vector2d pos) const
    {
        return getPixel(pos);
    }

    void Image::setPixel(size_t x, size_t y, booba::Color color) 
    {
        image_changed = true;
        setPixel(SL::Vector2d(x, y), SL::Color(color.r, color.g, color.b, color.a));
    }

    booba::Picture Image::getPicture(size_t x, size_t y, size_t w, size_t h) 
    {
        return booba::Picture(x, y, w, h, this);
    }

    void Image::setPicture(booba::Picture &&pic) 
    {
        sf::Image image;
        image.create(uint32_t(pic.getW()), uint32_t(pic.getH()), (sf::Uint8*)pic.getData());
        SL::RenderTexture render_texture(SL::Vector2d(getSize().x_, getSize().y_));
        SL::Sprite main_sprite(SL::Vector2d(getSize().x_, getSize().y_), getTexture());

        SL::Texture texture;
        texture.texture_.loadFromImage(image);

        SL::Sprite pic_sprite(SL::Vector2d(pic.getW(), pic.getH()), texture);
        pic_sprite.setPosition(SL::Vector2d(pic.getX(), pic.getY()));

        render_texture.clear(SL::Color(0, 0, 0, 0));
        render_texture.draw(main_sprite);
        render_texture.draw(pic_sprite);
        render_texture.display();

        *this = render_texture.getTexture().copyToImage();
    }

    void Image::clean(const booba::Color &color) 
    {
        create(SL::Vector2d(getW(), getH()), SL::Color(0, 0, 0, 0));
    }

    // void create(SL::Vector2d shape, const SL::Color &color = SL::Color(0, 0, 0, 255))
    // {
    //     image_.create(uint32_t(shape.x_), uint32_t(shape.y_), color.get_sf_color());
    // }
    
}