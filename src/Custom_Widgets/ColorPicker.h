#pragma once

#include "../Graphic-Library/GraphLib/GraphLib.h"


#include "HSVwindow.h"

enum
{
    FOREGROUND_COLOR,
    BACKGROUND_COLOR
};

using namespace SL;

class ColorPicker : public CompositeObject
{
public:
    int color_type_ = -1;
    Color fg_color_;
    Color bg_color_;

    Button *foreground_button_ = nullptr;
    Button *background_button_ = nullptr;
    Button *swap_button_       = nullptr;
    HSVwindow *hsv_window_     = nullptr;

    ColorPicker(Button *foreground_button, Button *background_button, Button *swap_button, HSVwindow *hsv_window);

    ColorPicker(const ColorPicker &source);

    ColorPicker &operator=(const ColorPicker &source);

    void change_color(const Color &color);

    void swap_colors(const Event &);

    void set_color(const Event &);

    void open_foreground_hsv_window(const Event &event);
    
    void open_background_hsv_window(const Event &event);

    void MoveMouseEvent(const Event &event) override;

    void set_parent(Widget *parent) override;
};