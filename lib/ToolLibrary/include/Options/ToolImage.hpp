#pragma once

#include "GraphLib.hpp"
#include "PluginStandart.hpp"
#include "Color.hpp"
#include "ToolManager.hpp"

namespace TOOL_SL
{
    class ToolImage : public booba::Image
    {
    public:        
        bool image_changed_ = false;

        ToolImage (SL::Image *image);
        ToolImage(const ToolImage &source) = default;
        ToolImage &operator=(const ToolImage &source) = default;
        ~ToolImage() {};

        booba::Vector2d getSize() const override;

        booba::Color getPixel(booba::Vector2d position) const override;

        void setPixel(booba::Vector2d position, booba::Color color) override;

        virtual booba::Picture getPicture(booba::Vector2d position, booba::Vector2d shape) const override;

        void setPicture(booba::Picture &pic, booba::Vector2d image_pos, booba::Vector2d pic_start, booba::Vector2d pic_end, bool applyAlpha) override;

        void replaceWithPicture(booba::Picture &pic) override;

        void clean(const booba::Color &color = booba::Color::WHITE) override;
    
    private:
        SL::Image *image_;
    };
}