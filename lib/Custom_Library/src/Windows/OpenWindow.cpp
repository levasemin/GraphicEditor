#include "OpenWindow.hpp"

namespace CUST_SL
{
    OpenWindow::OpenWindow(SL::Vector2d shape, SL::Button *open_button, SL::Button *cancel_button, SL::Editor *path_editor): MainWindow(shape, SL::Texture(SL::Color((uint8_t)69,  (uint8_t)69,  (uint8_t)69,   uint8_t(255)))),
        path_(""),
        open_button_(open_button),
        cancel_button_(cancel_button),
        path_editor_(path_editor)
    {
        app_ = new SL::Application(this);

        open_button_  ->setLeftClick((SL::Command<> *)     new SL::SimpleCommand<OpenWindow>(this, &OpenWindow::open_image));
        cancel_button_->setLeftClick((SL::Command<> *)     new SL::SimpleCommand<OpenWindow>(this, &OpenWindow::close));
        path_editor_  ->setEditorCommand((SL::Command<std::string> *) new SL::SimpleCommand<OpenWindow, std::string>(this, &OpenWindow::setPath));

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

    void OpenWindow::setPath(std::string path)
    {
        path_ = path;
    }

    void OpenWindow::open_image()
    {
        SL::Image image(path_);
        canvas_->setImage(image);
        close();
    }

    void OpenWindow::exec()
    {
        app_->exec();
    }

    void OpenWindow::close()
    {
        app_->close();
    }

    OpenWindow::~OpenWindow() {}
}