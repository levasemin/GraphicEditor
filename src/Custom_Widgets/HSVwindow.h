#pragma once

#include "../Graphic-Library/GraphLib/GraphLib.h"

#include "HSVpalette.h"
#include <string.h>

using namespace SL;

class HSVwindow : public MainWindow
{
public:
    Application *app_ = nullptr;

    HSVpalette *hsv_palette_ = nullptr;
    Editor *r_editor_        = nullptr;
    Editor *g_editor_        = nullptr;
    Editor *b_editor_        = nullptr;
    Button *ok_button_       = nullptr;
    Button *cancel_button_   = nullptr;

    Color color_;
    Color prev_color_;
    
    Command<const Color &> *hsv_window_command_ = nullptr; 

    HSVwindow(Vector2d shape, const Texture &texture, HSVpalette *hsv_palette, Editor *r_editor, Editor *g_editor, Editor *b_editor, Button *ok_button, Button *cancel_button);

    HSVwindow(const HSVwindow &source);
    
    HSVwindow &operator=(const HSVwindow &source);
    void change_color(const Color &color);
    
    void set_command(Command<const Color &> *command);
    
    void change_r(const Event &string);

    void change_g(const Event &string);

    void change_b(const Event &string);

    void set_color(const Color &color);

    void exec(const Event &event = Event());

    void close(const Event &event = Event());
};