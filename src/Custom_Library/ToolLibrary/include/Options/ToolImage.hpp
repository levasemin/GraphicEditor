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
        ToolImage (SL::Image *image);
        ToolImage(const ToolImage &source) = default;
        ToolImage &operator=(const ToolImage &source) = default;
        ~ToolImage() {};

        size_t getH() override;

        size_t getW() override;

        booba::Color getPixel(size_t x, size_t y) override;

        void setPixel(size_t x, size_t y, booba::Color color) override;

        booba::Picture getPicture(size_t x, size_t y, size_t w, size_t h) override;

        void setPicture(booba::Picture &pic, size_t image_x, size_t image_y, size_t pic_start_x, size_t pic_start_y, size_t pic_end_x, size_t pic_end_y, bool applyAlpha) override;

        void clean(const booba::Color &color = booba::Color::WHITE) override;
    
    private:
        SL::Image *image_;
        bool image_changed = false;
    };
}