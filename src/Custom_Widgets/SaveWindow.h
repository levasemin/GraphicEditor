#pragma once

#include "GraphLib.h"
#include "Canvas.h"

#include "Image.h"
#include "Color.h"

class SaveWindow : public SL::MainWindow
{
public:
    SL::Application *app_ = nullptr;
    Canvas *canvas_ = nullptr;
    std::string path_;

    SL::Button *save_button_;
    SL::Button *cancel_button_;
    SL::Editor *path_editor_;

    SaveWindow(SL::Vector2d shape, SL::Button *save_button, SL::Button *cancel_button, SL::Editor *path_editor);

    SaveWindow (const SaveWindow &source);

    SaveWindow &operator= (const SaveWindow &source);

    void set_canvas(Canvas *canvas);

    void change_path(const SL::Event &event);

    void set_path(const std::string &path);

    void save_image(const SL::Event &);

    void exec(const SL::Event &);

    void close(const SL::Event &);

    ~SaveWindow();
};
