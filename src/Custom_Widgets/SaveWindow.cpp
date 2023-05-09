#include "SaveWindow.h"



SaveWindow::SaveWindow(SL::Vector2d shape, SL::Button *save_button, SL::Button *cancel_button, SL::Editor *path_editor): MainWindow(shape, SL::Texture(CUST_SL::Color::Grey)),
    path_(""),
    save_button_(save_button),
    cancel_button_(cancel_button),
    path_editor_(path_editor)
{
    app_ = new SL::Application(this);

    save_button_  ->set_left_click((SL::Command<const SL::Event &> *)     new SL::SimpleCommand<SaveWindow, const SL::Event &>(this, &SaveWindow::save_image));
    cancel_button_->set_left_click((SL::Command<const SL::Event &> *)     new SL::SimpleCommand<SaveWindow, const SL::Event &>(this, &SaveWindow::close));
    path_editor_  ->set_editor_command((SL::Command<const SL::Event &> *) new SL::SimpleCommand<SaveWindow, const SL::Event &>(this, &SaveWindow::change_path));

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

void SaveWindow::change_path(const SL::Event &event)
{
    path_ = path_editor_->get_text();
}

void SaveWindow::set_path(const std::string &path)
{
    path_ = path;
}

void SaveWindow::save_image(const SL::Event &)
{
    canvas_->get_image()->saveToFile(path_);
    close(SL::Event());
}

void SaveWindow::exec(const SL::Event &)
{
    app_->exec();
}

void SaveWindow::close(const SL::Event &)
{
    app_->close();        
}

SaveWindow::~SaveWindow() {};
