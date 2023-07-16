#pragma once

#include "GraphLib.hpp"

#include "../Options/Color.hpp"
#include "../Additional_Widgets/Canvas.hpp"

#include "../Additional_Widgets/HSVpalette.hpp"
#include <string.h>


class HSVwindow : public SL::MainWindow
{
public:
    SL::Application *app_ = nullptr;

    HSVpalette *hsv_palette_ = nullptr;
    SL::Editor *r_editor_        = nullptr;
    SL::Editor *g_editor_        = nullptr;
    SL::Editor *b_editor_        = nullptr;
    SL::Button *ok_button_       = nullptr;
    SL::Button *cancel_button_   = nullptr;

    CUST_SL::Color color_;
    CUST_SL::Color prev_color_;

    SL::Command<const CUST_SL::Color &> *hsv_window_command_ = nullptr;

    HSVwindow(SL::Vector2d shape, const SL::Texture &texture, HSVpalette *hsv_palette, SL::Editor *r_editor, SL::Editor *g_editor, SL::Editor *b_editor, SL::Button *ok_button, SL::Button *cancel_button);

    HSVwindow(const HSVwindow &source);

    HSVwindow &operator=(const HSVwindow &source);
    void change_color(const CUST_SL::Color &color);

    void set_command(SL::Command<const CUST_SL::Color &> *command);

    void change_r(const SL::Event &string);

    void change_g(const SL::Event &string);

    void change_b(const SL::Event &string);

    void set_color(const CUST_SL::Color &color);

    void exec(const SL::Event &event = SL::Event());

    void close(const SL::Event &event = SL::Event());
};
