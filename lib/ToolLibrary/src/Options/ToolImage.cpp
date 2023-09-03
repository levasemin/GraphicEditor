#include "ToolImage.hpp"

namespace TOOL_SL
{
    ToolImage::ToolImage (SL::Image *image):
        image_(image)
    {}

    booba::Vector2d ToolImage::getSize() const 
    {
        return booba::Vector2d(image_->getSize().x_, image_->getSize().y_);
    }

    booba::Color ToolImage::getPixel(booba::Vector2d position) const 
    {
        SL::Color color = image_->getPixel(SL::Vector2d(static_cast<uint32_t>(position.x_), static_cast<uint32_t>(position.y_)));
        return booba::Color(color.get_r(), color.get_b(), color.get_b(), color.get_a());
    }

    void ToolImage::setPixel(booba::Vector2d position, booba::Color color) 
    {
        image_changed_ = true;
        
        image_->setPixel(SL::Vector2d(position.x_, position.y_), SL::Color(color.r, color.g, color.b, color.a));
    }

    booba::Picture ToolImage::getPicture(booba::Vector2d position, booba::Vector2d shape) const
    {
        booba::Picture pic;
        pic.create(shape, position, this);
        return pic;
    }

    void ToolImage::setPicture(booba::Picture &pic, booba::Vector2d image_pos, booba::Vector2d pic_start, booba::Vector2d pic_end, bool applyAlpha)
    {
        image_changed_ = true;

        SL::Image image;
        image.create(SL::Vector2d(pic.getSize().x_, pic.getSize().y_), reinterpret_cast<const uint8_t*>(pic.getData()));
        image_->copy(SL::Image(image), SL::Vector2d(image_pos.x_, image_pos.y_), SL::Vector2d(pic_start.x_, pic_start.y_), SL::Vector2d(pic_end.x_, pic_end.y_), applyAlpha);
    }

    void ToolImage::replaceWithPicture(booba::Picture &pic)
    {
        image_changed_ = true;

        image_->create(SL::Vector2d(pic.getSize().x_, pic.getSize().y_), reinterpret_cast<const uint8_t*>(pic.getData()));
    }

    void ToolImage::clean(const booba::Color &color) 
    {
        image_changed_ = true;

        image_->create(SL::Vector2d(getSize().x_, getSize().y_), SL::Color(0, 0, 0, 0));
    }
}