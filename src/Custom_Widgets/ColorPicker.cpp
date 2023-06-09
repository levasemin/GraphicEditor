#include "ColorPicker.h"



ColorPicker::ColorPicker(SL::Button *foreground_button, SL::Button *background_button, SL::Button *swap_button, HSVwindow *hsv_window): CompositeObject(SL::Vector2d(0, 0), SL::Vector2d(0, 0)),
    fg_color_(booba::APPCONTEXT->fgColor),
    bg_color_(booba::APPCONTEXT->bgColor),
    foreground_button_(foreground_button),
    background_button_(background_button),
    swap_button_(swap_button),
    hsv_window_(hsv_window)
{
    foreground_button_->set_left_click((SL::Command<const SL::Event &> *) new SL::SimpleCommand<ColorPicker, const SL::Event &>(this, &ColorPicker::open_foreground_hsv_window));
    background_button_->set_left_click((SL::Command<const SL::Event &> *) new SL::SimpleCommand<ColorPicker, const SL::Event &>(this, &ColorPicker::open_background_hsv_window));
    swap_button_->set_left_click((SL::Command<const SL::Event &> *) new SL::SimpleCommand<ColorPicker, const SL::Event &>(this, &ColorPicker::swap_colors));
    hsv_window_->set_command((SL::Command<const CUST_SL::Color &> *) new SL::SimpleCommand<ColorPicker, const CUST_SL::Color&>(this, &ColorPicker::change_color));
    hsv_window_->ok_button_->set_left_click((SL::Command<const SL::Event &> *) new SL::SimpleCommand<ColorPicker, const SL::Event&>(this, &ColorPicker::set_color));
    hsv_window_->cancel_button_->set_left_click((SL::Command<const SL::Event &> *) new SL::SimpleCommand<ColorPicker, const SL::Event &> (this, &ColorPicker::return_color));

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

void ColorPicker::change_color(const CUST_SL::Color &color)
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

void ColorPicker::swap_colors(const SL::Event &)
{
    CUST_SL::Color color = booba::APPCONTEXT->fgColor;
    booba::APPCONTEXT->fgColor = booba::APPCONTEXT->bgColor;
    booba::APPCONTEXT->bgColor = color;

    foreground_button_->set_texture(SL::Texture(CUST_SL::Color(booba::APPCONTEXT->fgColor)));
    background_button_->set_texture(SL::Texture(CUST_SL::Color(booba::APPCONTEXT->bgColor)));
}

void ColorPicker::set_color(const SL::Event &)
{
    if (color_type_ == FOREGROUND_COLOR)
    {
        foreground_button_->set_texture(SL::Texture(fg_color_));
        booba::APPCONTEXT->fgColor = CUST_SL::Color::convert_color_uint(fg_color_);
    }

    else if (color_type_ == BACKGROUND_COLOR)
    {
        background_button_->set_texture(SL::Texture(bg_color_));
        booba::APPCONTEXT->bgColor = CUST_SL::Color::convert_color_uint(bg_color_);
    }

    color_type_ = -1;
    hsv_window_->close();
}

void ColorPicker::return_color(const SL::Event &)
{
    if (color_type_ == FOREGROUND_COLOR)
    {
        fg_color_ = booba::APPCONTEXT->fgColor;
        hsv_window_->set_color(fg_color_);
    }

    else if (color_type_ == BACKGROUND_COLOR)
    {
        bg_color_ = booba::APPCONTEXT->bgColor;
        hsv_window_->set_color(bg_color_);
    }

    color_type_ = -1;
    hsv_window_->close();
}

void ColorPicker::open_foreground_hsv_window(const SL::Event &event)
{
    color_type_ = FOREGROUND_COLOR;
    hsv_window_->set_color(fg_color_);
    hsv_window_->exec(event);
}

void ColorPicker::open_background_hsv_window(const SL::Event &event)
{
    color_type_ = BACKGROUND_COLOR;
    hsv_window_->set_color(bg_color_);
    hsv_window_->exec(event);
}

void ColorPicker::MoveMouseEvent(const SL::Event &event)
{
    CUST_SL::Color fg_color = booba::APPCONTEXT->fgColor;
    CUST_SL::Color bg_color = booba::APPCONTEXT->bgColor;

    if (fg_color_ != fg_color)
    {
        fg_color_ = fg_color;
        foreground_button_->set_texture(SL::Texture(fg_color_));
    }

    if (bg_color != bg_color)
    {
        bg_color_ = bg_color;
        background_button_->set_texture(SL::Texture(bg_color_));
    }
}

void ColorPicker::set_parent(SL::Widget *parent)
{
    CompositeObject::set_parent(parent);   

    parent->add(foreground_button_);
    parent->add(background_button_);
    parent->add(swap_button_);
}