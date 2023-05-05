#include "ColorPicker.h"

using namespace SL;

ColorPicker::ColorPicker(Button *foreground_button, Button *background_button, Button *swap_button, HSVwindow *hsv_window): CompositeObject(Vector2d(0, 0), Vector2d(0, 0)),
    fg_color_(Color::convert_uint_color(booba::APPCONTEXT->fgColor)),
    bg_color_(Color::convert_uint_color(booba::APPCONTEXT->bgColor)),
    foreground_button_(foreground_button),
    background_button_(background_button),
    swap_button_(swap_button),
    hsv_window_(hsv_window)
{
    foreground_button_->set_left_click((Command<const Event &> *) new SimpleCommand<ColorPicker, const Event &>(this, &ColorPicker::open_foreground_hsv_window));
    background_button_->set_left_click((Command<const Event &> *) new SimpleCommand<ColorPicker, const Event &>(this, &ColorPicker::open_background_hsv_window));
    swap_button_->set_left_click((Command<const Event &> *) new SimpleCommand<ColorPicker, const Event &>(this, &ColorPicker::swap_colors));
    hsv_window_->set_command((Command<const Color &> *) new SimpleCommand<ColorPicker, const Color&>(this, &ColorPicker::change_color));
    hsv_window_->ok_button_->set_left_click((Command<const Event &> *) new SimpleCommand<ColorPicker, const Event&>(this, &ColorPicker::set_color));
    hsv_window_->cancel_button_->set_left_click((Command<const Event &> *) new SimpleCommand<ColorPicker, const Event &> (this, &ColorPicker::return_color));

}

ColorPicker::ColorPicker(const ColorPicker &source) : CompositeObject(*(const CompositeObject *) &source),
    fg_color_(source.fg_color_),
    bg_color_(source.bg_color_),
    foreground_button_(source.foreground_button_),
    background_button_(source.background_button_),
    swap_button_(source.swap_button_),
    hsv_window_(source.hsv_window_)
{}

ColorPicker &ColorPicker::operator=(const ColorPicker &source)
{
    CompositeObject::operator=(*(const CompositeObject *) &source);

    fg_color_          = source.fg_color_;
    bg_color_          = source.bg_color_;
    foreground_button_ = source.foreground_button_;
    background_button_ = source.background_button_;
    swap_button_       = source.swap_button_;
    hsv_window_        = source.hsv_window_;

    return *this;
}

void ColorPicker::change_color(const Color &color)
{
    if (color_type_ == FOREGROUND_COLOR)
    {
        fg_color_ = color;
    }

    else
    {
        bg_color_ = color;
    }
}

void ColorPicker::swap_colors(const Event &)
{
    uint32_t color = booba::APPCONTEXT->fgColor;
    booba::APPCONTEXT->fgColor = booba::APPCONTEXT->bgColor;
    booba::APPCONTEXT->bgColor = color;

    foreground_button_->set_texture(Texture(Color::convert_uint_color(booba::APPCONTEXT->fgColor)));
    background_button_->set_texture(Texture(Color::convert_uint_color(booba::APPCONTEXT->bgColor)));
}

void ColorPicker::set_color(const Event &)
{
    if (color_type_ == FOREGROUND_COLOR)
    {
        foreground_button_->set_texture(Texture(fg_color_));
        booba::APPCONTEXT->fgColor = Color::convert_color_uint(fg_color_);
    }

    else if (color_type_ == BACKGROUND_COLOR)
    {
        background_button_->set_texture(Texture(bg_color_));
        booba::APPCONTEXT->bgColor = Color::convert_color_uint(bg_color_);
    }

    color_type_ = -1;
    hsv_window_->close();
}

void ColorPicker::return_color(const Event &)
{
    if (color_type_ == FOREGROUND_COLOR)
    {
        fg_color_ = Color::convert_uint_color(booba::APPCONTEXT->fgColor);
        hsv_window_->set_color(fg_color_);
    }

    else if (color_type_ == BACKGROUND_COLOR)
    {
        bg_color_ = Color::convert_uint_color(booba::APPCONTEXT->bgColor);
        hsv_window_->set_color(bg_color_);
    }

    color_type_ = -1;
    hsv_window_->close();
}

void ColorPicker::open_foreground_hsv_window(const Event &event)
{
    color_type_ = FOREGROUND_COLOR;
    hsv_window_->set_color(fg_color_);
    hsv_window_->exec(event);
}

void ColorPicker::open_background_hsv_window(const Event &event)
{
    color_type_ = BACKGROUND_COLOR;
    hsv_window_->set_color(bg_color_);
    hsv_window_->exec(event);
}

void ColorPicker::MoveMouseEvent(const Event &event)
{
    Color fg_color = Color::convert_uint_color(booba::APPCONTEXT->fgColor);
    Color bg_color = Color::convert_uint_color(booba::APPCONTEXT->bgColor);

    if (fg_color_ != fg_color)
    {
        fg_color_ = fg_color;
        foreground_button_->set_texture(Texture(fg_color_));
    }

    if (bg_color != bg_color)
    {
        bg_color_ = bg_color;
        background_button_->set_texture(Texture(bg_color_));
    }
}

void ColorPicker::set_parent(Widget *parent)
{
    CompositeObject::set_parent(parent);   

    parent->add(foreground_button_);
    parent->add(background_button_);
    parent->add(swap_button_);
}