#include "OpenWindow.h"

#include "Canvas.h"

using namespace SL;

OpenWindow::OpenWindow(Vector2d shape, Button *open_button, Button *cancel_button, Editor *path_editor): MainWindow(shape, Texture(Color::Grey)),
    path_(""),
    open_button_(open_button),
    cancel_button_(cancel_button),
    path_editor_(path_editor)
{
    app_ = new Application(this);

    open_button_  ->set_left_click((Command<const Event &> *)  new SimpleCommand<OpenWindow, const Event &>(this, &OpenWindow::open_image));
    cancel_button_->set_left_click((Command<const Event &> *) new SimpleCommand<OpenWindow, const Event &>(this, &OpenWindow::close));
    path_editor_  ->set_editor_command((Command<const Event &> *) new SimpleCommand<OpenWindow, const Event &>(this, &OpenWindow::change_path));

    add(path_editor_);
    add(open_button_);
    add(cancel_button_);
}

OpenWindow::OpenWindow (const OpenWindow &source) : MainWindow(*(const MainWindow *)&source),
    app_(source.app_),
    canvas_(source.canvas_),
    path_(source.path_),
    open_button_(source.open_button_),
    cancel_button_(source.cancel_button_),
    path_editor_(source.path_editor_) 
{}

OpenWindow &OpenWindow::operator= (const OpenWindow &source)
{
    MainWindow::operator=(source);

    app_           = source.app_;
    canvas_        = source.canvas_;
    path_          = source.path_;
    open_button_   = source.open_button_;
    cancel_button_ = source.cancel_button_;
    path_editor_   = source.path_editor_;
    
    return *this;
}

void OpenWindow::set_canvas(Canvas *canvas)
{
    canvas_ = canvas;
}

void OpenWindow::set_path(const std::string &path)
{
    path_ = path;
}

void OpenWindow::change_path(const Event &event)
{
    path_ = path_editor_->get_text();
}

void OpenWindow::open_image(const Event &)
{
    Image image(path_);
    canvas_->set_image(image);
    close(Event());
}

void OpenWindow::exec(const Event &)
{
    app_->exec();
}

void OpenWindow::close(const Event &)
{
    app_->close();
}

OpenWindow::~OpenWindow() {};
