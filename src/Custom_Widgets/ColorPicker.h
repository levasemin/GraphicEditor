#pragma once

#include "../Graphic-Library/GraphLib/GraphLib.h"

#include "Image.h"
#include "Color.h"

#include "HSVwindow.h"



enum
{
    FOREGROUND_COLOR,
    BACKGROUND_COLOR
};



class ColorPicker : public SL::CompositeObject
{
public:
    int color_type_ = -1;
    Color fg_color_;
    Color bg_color_;

    SL::Button *foreground_button_ = nullptr;
    SL::Button *background_button_ = nullptr;
    SL::Button *swap_button_       = nullptr;
    HSVwindow *hsv_window_     = nullptr;

    ColorPicker(SL::Button *foreground_button, SL::Button *background_button, SL::Button *swap_button, HSVwindow *hsv_window);

    ColorPicker(const ColorPicker &source);

    ColorPicker &operator=(const ColorPicker &source);

    void change_color(const Color &color);

    void swap_colors(const SL::Event &);

    void set_color(const SL::Event &);

    void return_color(const SL::Event &);
    
    void open_foreground_hsv_window(const SL::Event &event);
    
    void open_background_hsv_window(const SL::Event &event);

    void MoveMouseEvent(const SL::Event &event) override;

    void set_parent(SL::Widget *parent) override;
};