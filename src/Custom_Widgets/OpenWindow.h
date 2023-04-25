#pragma once

#include "../Graphic-Library/GraphLib/GraphLib.h"


#include "Canvas.h"

class OpenWindow : public MainWindow
{

public:
    Application *app_ = nullptr;
    Canvas *canvas_ = nullptr;
    std::string path_;

    Button *open_button_;
    Button *cancel_button_;
    Editor *path_editor_;

    OpenWindow(Vector2d shape, Button *open_button, Button *cancel_button, Editor *path_editor);

    OpenWindow (const OpenWindow &source);
    
    OpenWindow &operator= (const OpenWindow &source);

    void set_canvas(Canvas *canvas);

    void set_path(const std::string &path);

    void change_path(const Event &event);

    void open_image(const Event &);

    void exec(const Event &);

    void close(const Event &);

    ~OpenWindow();
};
