#include "SaveWindow.h"

using namespace SL;

SaveWindow::SaveWindow(Vector2d shape, Button *save_button, Button *cancel_button, Editor *path_editor): MainWindow(shape, Texture(Color::Grey)),
    path_(""),
    save_button_(save_button),
    cancel_button_(cancel_button),
    path_editor_(path_editor)
{
    app_ = new Application(this);

    save_button_  ->set_left_click((Command<const Event &> *)  new SimpleCommand<SaveWindow, const Event &>(this, &SaveWindow::save_image));
    cancel_button_->set_left_click((Command<const Event &> *) new SimpleCommand<SaveWindow, const Event &>(this, &SaveWindow::close));
    path_editor_  ->set_editor_command((Command<const Event &> *) new SimpleCommand<SaveWindow, const Event &>(this, &SaveWindow::change_path));

    add(path_editor_);
    add(save_button_);
    add(cancel_button_);
}

SaveWindow::SaveWindow (const SaveWindow &source) : MainWindow(*(const MainWindow *)&source),
    app_(source.app_),
    canvas_(source.canvas_),
    path_(source.path_),
    save_button_(source.save_button_),
    cancel_button_(source.cancel_button_),
    path_editor_(source.path_editor_) 
{}

SaveWindow &SaveWindow::operator= (const SaveWindow &source)
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

void SaveWindow::set_canvas(Canvas *canvas)
{
    canvas_ = canvas;
}

void SaveWindow::change_path(const Event &event)
{
    path_ = path_editor_->get_text();
}

void SaveWindow::set_path(const std::string &path)
{
    path_ = path;
}

void SaveWindow::save_image(const Event &)
{
    canvas_->get_image()->saveToFile(path_);
    close(Event());
}

void SaveWindow::exec(const Event &)
{
    app_->exec();
}

void SaveWindow::close(const Event &)
{
    app_->close();        
}

SaveWindow::~SaveWindow() {};
