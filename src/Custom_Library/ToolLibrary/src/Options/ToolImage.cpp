#include "ToolImage.hpp"

namespace TOOL_SL
{
    ToolImage::ToolImage (SL::Image *image):
        image_(image)
    {}

    size_t ToolImage::getH() 
    {
        return size_t(image_->getSize().y_);
    }

    size_t ToolImage::getW() 
    {
        return size_t(image_->getSize().x_);
    }

    booba::Color ToolImage::getPixel(size_t x, size_t y) 
    {
        SL::Color color = image_->getPixel(SL::Vector2d(uint32_t(x), uint32_t(y)));
        return booba::Color(color.get_r(), color.get_b(), color.get_b(), color.get_a());
    }

    void ToolImage::setPixel(size_t x, size_t y, booba::Color color) 
    {
        image_changed = true;
        image_->setPixel(SL::Vector2d(x, y), SL::Color(color.r, color.g, color.b, color.a));
    }

    booba::Picture ToolImage::getPicture(size_t x, size_t y, size_t w, size_t h) 
    {
        booba::Picture pic;
        pic.create(w, h, x, y, this);
        return pic;
    }

    void ToolImage::setPicture(booba::Picture &&pic, size_t x, size_t y) 
    {
        sf::Image image;
        image.create(uint32_t(pic.getW()), uint32_t(pic.getH()), (sf::Uint8*)pic.getData());
        SL::RenderTexture render_texture(SL::Vector2d(image_->getSize().x_, image_->getSize().y_));
        SL::Sprite main_sprite(SL::Vector2d(image_->getSize().x_, image_->getSize().y_), image_->getTexture());

        SL::Texture texture;
        texture.texture_.loadFromImage(image);

        SL::Sprite pic_sprite(SL::Vector2d(pic.getW(), pic.getH()), texture);
        pic_sprite.setPosition(SL::Vector2d(x, y));

        render_texture.clear(SL::Color(0, 0, 0, 0));
        render_texture.draw(main_sprite);
        render_texture.draw(pic_sprite);
        render_texture.display();

        *image_ = render_texture.getTexture().copyToImage();
    }

    void ToolImage::clean(const booba::Color &color) 
    {
        image_->create(SL::Vector2d(getW(), getH()), SL::Color(0, 0, 0, 0));
    }

    booba::Image *ToolImage::getHiddenLayer()
    {
        return nullptr;
    }
    
}