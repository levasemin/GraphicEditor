#pragma once

#include "Library/GraphicLib.h"
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

    SaveWindow(Vector2d shape, Button *save_button, Button *cancel_button, Editor *path_editor): MainWindow(shape, Texture(Color::Grey)),
        path_(""),
        save_button_(save_button),
        cancel_button_(cancel_button),
        path_editor_(path_editor)
    {
        app_ = new Application(this);

        save_button_  ->set_left_click((Command<const Event &> *)  new SimpleCommand<SaveWindow, const Event &>(this, &SaveWindow::save_image));
        cancel_button_->set_left_click((Command<const Event &> *) new SimpleCommand<SaveWindow, const Event &>(this, &SaveWindow::close));
        path_editor_  ->set_editor_command((Command<const std::string &> *) new SimpleCommand<SaveWindow, const std::string &>(this, &SaveWindow::change_path));

        add(path_editor_);
        add(save_button_);
        add(cancel_button_);
    }

    SaveWindow (const SaveWindow &source) : MainWindow(*(const MainWindow *)&source),
        app_(source.app_),
        canvas_(source.canvas_),
        path_(source.path_),
        save_button_(source.save_button_),
        cancel_button_(source.cancel_button_),
        path_editor_(source.path_editor_) 
    {}
    
    SaveWindow &operator= (const SaveWindow &source)
    {
        MainWindow::operator=(source);

        app_           = source.app_;
        canvas_        = source.canvas_;
        path_          = source.path_;
        save_button_   = source.save_button_;
        cancel_button_ = source.cancel_button_;
        path_editor_   = source.path_editor_;
        
        return *this;
    }

    void set_canvas(Canvas *canvas)
    {
        canvas_ = canvas;
    }

    void change_path(const std::string &path)
    {
        path_ = path;
    }

    void save_image(const Event &)
    {
        canvas_->get_image()->saveToFile(path_);
        close(Event());
    }

    void exec(const Event &)
    {
        app_->exec();
    }

    void close(const Event &)
    {
        app_->close();        
    }

    ~SaveWindow() {};
};
