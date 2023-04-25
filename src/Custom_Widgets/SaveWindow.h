#pragma once

#include "../Graphic-Library/GraphLib/GraphLib.h"
#include "Canvas.h"

class SaveWindow : public MainWindow
{

public:
    Application *app_ = nullptr;
    Canvas *canvas_ = nullptr;
    std::string path_;

    Button *save_button_;
    Button *cancel_button_;
    Editor *path_editor_;

    SaveWindow(Vector2d shape, Button *save_button, Button *cancel_button, Editor *path_editor);
    
    SaveWindow (const SaveWindow &source);
    
    SaveWindow &operator= (const SaveWindow &source);

    void set_canvas(Canvas *canvas);

    void change_path(const Event &event);

    void set_path(const std::string &path);
    
    void save_image(const Event &);

    void exec(const Event &);

    void close(const Event &);

    ~SaveWindow();
};
