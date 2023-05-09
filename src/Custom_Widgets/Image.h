#pragma once

#include "../Graphic-Library/GraphLib/GraphLib.h"
#include "../Tool/tools.h"

#include "Color.h"

class Image : public booba::Image, public SL::Image
{
public:    
    Image () : SL::Image() {}
    
    virtual ~Image() {};

    Image(const std::string &path): SL::Image()
    {
        loadFromFile(path);
    }

    Image(const SL::Texture &texture): SL::Image()
    {
        image_ = texture.texture_.copyToImage();
    }

    Image (const SL::Vector2d &shape, const CUST_SL::Color &color = CUST_SL::Color(uint8_t(0), uint8_t(0), uint8_t(0))): SL::Image(shape, color)
    {}

    Image (const SL::Image &image) : SL::Image(image) {}

    size_t getH() override
    {
        return size_t(getSize().y_);
    }

    size_t getW() override
    {
        return size_t(getSize().x_);
    }
    
    booba::Color getPixel(size_t x, size_t y) override
    {
        CUST_SL::Color color(image_.getPixel(uint32_t(x), uint32_t(y)));
        return color;
    }

    CUST_SL::Color getPixel(SL::Vector2d pos) const
    {
        return CUST_SL::Color(image_.getPixel(uint32_t(pos.x_), uint32_t(pos.y_)));
    }
    
    void setPixel(size_t x, size_t y, booba::Color color) override
    {        
        image_changed = true;
        setPixel(SL::Vector2d(float(x), float(y)), color);
    }   

    void setPixel(SL::Vector2d pos, const CUST_SL::Color &color)
    {
        image_.setPixel(uint32_t(pos.x_), uint32_t(pos.y_), color.get_sf_color());
    }

    booba::Picture getPicture(size_t x, size_t y, size_t w, size_t h) override
    {
        return booba::Picture(x, y, w, h, this);
    }

    void setPicture(booba::Picture &&pic) override
    {
        sf::Image image;
        image.create(uint32_t(pic.getW()), uint32_t(pic.getH()), (sf::Uint8*)pic.getData());
        SL::RenderTexture render_texture(SL::Vector2d(image_.getSize().x, image_.getSize().y));
        SL::Sprite main_sprite(SL::Vector2d(image_.getSize().x, image_.getSize().y), getTexture());
        
        SL::Texture texture;
        texture.texture_.loadFromImage(image);

        SL::Sprite pic_sprite(SL::Vector2d(pic.getW(), pic.getH()), texture);
        pic_sprite.setPosition(SL::Vector2d(pic.getX(), pic.getY()));
        
        render_texture.clear(CUST_SL::Color(0, 0, 0, 0));
        render_texture.draw(main_sprite);
        render_texture.draw(pic_sprite);
        render_texture.display();
        
        image_ = render_texture.render_texture_.getTexture().copyToImage();
        image_.saveToFile("KIIIIt.png");
    }

    void create(SL::Vector2d shape, const CUST_SL::Color &color = CUST_SL::Color(0, 0, 0, 255))
    {
        image_.create(uint32_t(shape.x_), uint32_t(shape.y_), color.get_sf_color());
    }

    booba::Image *getHiddenLayer() override;
};