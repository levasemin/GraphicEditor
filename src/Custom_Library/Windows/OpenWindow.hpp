#pragma once

#include "GraphLib.hpp"

#include "../Options/Color.hpp"

#include "../Additional_Widgets/Canvas.hpp"

class OpenWindow : public SL::MainWindow
{
public:
    SL::Application *app_ = nullptr;
    Canvas *canvas_ = nullptr;
    std::string path_;

    SL::Button *open_button_;
    SL::Button *cancel_button_;
    SL::Editor *path_editor_;

    OpenWindow(SL::Vector2d shape, SL::Button *open_button, SL::Button *cancel_button, SL::Editor *path_editor);

    OpenWindow (const OpenWindow &source);

    OpenWindow &operator= (const OpenWindow &source);

    void set_canvas(Canvas *canvas);

    void set_path(const std::string &path);

    void change_path(const SL::Event &event);

    void open_image(const SL::Event &);

    void exec(const SL::Event &);

    void close(const SL::Event &);

    ~OpenWindow();
};
