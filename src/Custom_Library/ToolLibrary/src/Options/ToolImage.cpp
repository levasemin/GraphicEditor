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

    void ToolImage::setPicture(booba::Picture &pic, size_t image_x, size_t image_y, size_t pic_start_x, size_t pic_start_y, size_t pic_end_x, size_t pic_end_y, bool applyAlpha)
    {
        sf::Image image;
        image.create(uint32_t(pic.getW()), uint32_t(pic.getH()), (sf::Uint8*)pic.getData());
        image_->copy(SL::Image(image), SL::Vector2d(image_x, image_y), SL::Vector2d(pic_start_x, pic_start_y), SL::Vector2d(pic_end_x, pic_end_y), applyAlpha);
    }

    void ToolImage::clean(const booba::Color &color) 
    {
        image_->create(SL::Vector2d(getW(), getH()), SL::Color(0, 0, 0, 0));
    }
}