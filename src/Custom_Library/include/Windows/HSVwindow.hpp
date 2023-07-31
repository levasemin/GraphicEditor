#pragma once

#include "GraphLib.hpp"

#include "../Widgets/Canvas.hpp"

#include "../Widgets/HSVpalette.hpp"
#include <string.h>

namespace CUST_SL
{
    class HSVwindow : public SL::MainWindow
    {
    public:
        HSVwindow(SL::Vector2d shape, const SL::Texture &texture, HSVpalette *hsv_palette, SL::Editor *r_editor, SL::Editor *g_editor, SL::Editor *b_editor, SL::Button *ok_button, SL::Button *cancel_button);

        HSVwindow(const HSVwindow &source) = default;
        HSVwindow &operator=(const HSVwindow &source) = default;
        ~HSVwindow();

        SL::Command<const SL::Color &> *getCommand();
        void setCommand(SL::Command<const SL::Color &> *command);
        
        void setColor(const SL::Color &color);

        void exec(const SL::Event &event = SL::Event());

        void close(const SL::Event &event = SL::Event());
        
        friend class ColorPicker;
        
    private:
        SL::Application *app_ = nullptr;

        HSVpalette *hsv_palette_   = nullptr;
        SL::Editor *r_editor_      = nullptr;
        SL::Editor *g_editor_      = nullptr;
        SL::Editor *b_editor_      = nullptr;
        SL::Button *ok_button_     = nullptr;
        SL::Button *cancel_button_ = nullptr;

        SL::Color color_;
        SL::Color prev_color_;

        SL::Command<const SL::Color &> *hsv_window_command_ = nullptr;

        void change_r(std::string string);

        void change_g(std::string string);

        void change_b(std::string string);

        void change_color(const SL::Color &color);
    };
}