#pragma once

#include <deque>

#include "../Graphic-Library/GraphLib/GraphLib.h"


#include "Circle.h"
#include "Interpolator.h"

extern booba::ApplicationContext* booba::APPCONTEXT;

class ToolEyeDropper : booba::Tool
{
private:
    Color color_;

    SL::Label color_box_label_;
    SL::Label label_r_;
    SL::Label label_g_;
    SL::Label label_b_;

    uint64_t color_box_canvas_ = (uint64_t)nullptr;
    uint64_t canvas_r_         = (uint64_t)nullptr;
    uint64_t canvas_g_         = (uint64_t)nullptr;
    uint64_t canvas_b_         = (uint64_t)nullptr;

    bool clicked_ = false;
    
    char icon_path_[128] = "source/EyeDropper.png";

public:
    ToolEyeDropper():
        color_(uint8_t(0), uint8_t(0), uint8_t(0)),
        color_box_label_(SL::Vector2d(100, 100), SL::Vector2d()),
        label_r_  (SL::Vector2d(50, 30), SL::Vector2d()),
        label_g_  (SL::Vector2d(50, 30), SL::Vector2d()),
        label_b_  (SL::Vector2d(50, 30), SL::Vector2d())
    {
        label_r_.set_texture(SL::Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
        label_g_.set_texture(SL::Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
        label_b_.set_texture(SL::Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
        
        label_r_.setTextColor(Color(uint8_t(190), uint8_t(190), uint8_t(190)));
        label_g_.setTextColor(Color(uint8_t(190), uint8_t(190), uint8_t(190)));
        label_b_.setTextColor(Color(uint8_t(190), uint8_t(190), uint8_t(190)));

        label_r_.setCharacterSize(30);
        label_g_.setCharacterSize(30);
        label_b_.setCharacterSize(30);
        
        booba::addTool(this);
    }

    ToolEyeDropper           (const ToolEyeDropper &) = default;
    ToolEyeDropper &operator=(const ToolEyeDropper &) = default;

    void set_color(const Color &color)
    {
        color_ = color;
        booba::APPCONTEXT->fgColor = Color::convert_color_uint(color);
        
        label_r_.setString(std::to_string(int(color.get_r())));
        label_g_.setString(std::to_string(int(color.get_g())));
        label_b_.setString(std::to_string(int(color.get_b())));
        
        fill_canvas(canvas_r_, label_r_);
        fill_canvas(canvas_g_, label_g_);
        fill_canvas(canvas_b_, label_b_);

        color_box_label_.set_texture(SL::Texture(color));

        fill_canvas(color_box_canvas_, color_box_label_);
        fill_canvas(canvas_r_, label_r_);
        fill_canvas(canvas_g_, label_g_);
        fill_canvas(canvas_b_, label_b_);
    }
    
    void fill_canvas(uint64_t canvas, SL::Label &label)
    {        
        Image image(label.get_render_texture()->getTexture());   

        for (int y = 0; y < int(label.get_shape().y_); y++)
        {
            for (int x = 0; x < int(label.get_shape().x_); x++)
            {
                booba::putPixel(canvas, x, y, image.getPixel(x, y));
            }
        }
    }

    const char* getTexture() override
    {
        return icon_path_;
    } 

    void apply(booba::Image* image, const booba::Event* event) override;

    void buildSetupWidget() override
    {
        color_box_canvas_ = booba::createCanvas(10,  10, 100, 100);
        canvas_r_         = booba::createCanvas(145, 45,  50, 30);
        canvas_g_         = booba::createCanvas(145, 80,  50, 30);
        canvas_b_         = booba::createCanvas(145, 115, 50, 30);
    }

    ~ToolEyeDropper()
    {}
};