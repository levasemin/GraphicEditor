#pragma once

#include "GraphLib.hpp"
#include "ToolLibrary.hpp"

#include "../Windows/HSVwindow.hpp"

namespace CUST_SL
{
    class ColorPicker : public SL::CompositeObject
    {
    public:
        enum class Type
        {
            FOREGROUND_COLOR,
            BACKGROUND_COLOR,
            NO_COLOR
        };

        ColorPicker(SL::Vector2d shape, SL::Vector2d position, const SL::Texture &texture = SL::Texture(SL::Color::White));

        ColorPicker(const ColorPicker &source) = default;
        ColorPicker &operator=(const ColorPicker &source) = default;
        ~ColorPicker();

        void setColor();
        void setHSVwindow(HSVwindow *hsv_window);

        void open_foreground_hsv_window();

        void open_background_hsv_window();

    protected:
        void moveMouseEvent(const SL::Event &event) override;
    
    private:
        Type color_type_ = Type::NO_COLOR;
        SL::Color fg_color_;
        SL::Color bg_color_;

        SL::Button foreground_button_;
        SL::Button background_button_;
        SL::Button swap_button_;
        HSVwindow *hsv_window_         = nullptr;

        void change_color(const SL::Color &color);

        void swap_colors();

        void return_color();
    };
}