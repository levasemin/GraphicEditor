#include "OpenWindow.h"

#include "Canvas.h"



OpenWindow::OpenWindow(SL::Vector2d shape, SL::Button *open_button, SL::Button *cancel_button, SL::Editor *path_editor): MainWindow(shape, SL::Texture(Color::Grey)),
    path_(""),
    open_button_(open_button),
    cancel_button_(cancel_button),
    path_editor_(path_editor)
{
    app_ = new SL::Application(this);

    open_button_  ->set_left_click((SL::Command<const SL::Event &> *)     new SL::SimpleCommand<OpenWindow, const SL::Event &>(this, &OpenWindow::open_image));
    cancel_button_->set_left_click((SL::Command<const SL::Event &> *)     new SL::SimpleCommand<OpenWindow, const SL::Event &>(this, &OpenWindow::close));
    path_editor_  ->set_editor_command((SL::Command<const SL::Event &> *) new SL::SimpleCommand<OpenWindow, const SL::Event &>(this, &OpenWindow::change_path));

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

void OpenWindow::change_path(const SL::Event &event)
{
    path_ = path_editor_->get_text();
}

void OpenWindow::open_image(const SL::Event &)
{
    Image image(path_);
    canvas_->set_image(image);
    close(SL::Event());
}

void OpenWindow::exec(const SL::Event &)
{
    app_->exec();
}

void OpenWindow::close(const SL::Event &)
{
    app_->close();
}

OpenWindow::~OpenWindow() {};
