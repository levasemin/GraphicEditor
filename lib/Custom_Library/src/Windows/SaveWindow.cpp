#include "SaveWindow.hpp"

namespace CUST_SL
{

    SaveWindow::SaveWindow(SL::Vector2d shape, SL::Button *save_button, SL::Button *cancel_button, SL::Editor *path_editor): MainWindow(shape, SL::Texture(SL::Color(static_cast<uint8_t>(69),  static_cast<uint8_t>(69),  static_cast<uint8_t>(69),   uint8_t(255)))),
        path_(""),
        save_button_(save_button),
        cancel_button_(cancel_button),
        path_editor_(path_editor)
    {
        app_ = new SL::Application(this);

        save_button_  ->setLeftClick    ((SL::Command<> *) new SL::SimpleCommand<SaveWindow>(this, &SaveWindow::save_image));
        cancel_button_->setLeftClick    ((SL::Command<> *) new SL::SimpleCommand<SaveWindow>(this, &SaveWindow::close));
        path_editor_  ->setEditorCommand((SL::Command<std::string> *) new SL::SimpleCommand<SaveWindow, std::string>(this, &SaveWindow::setPath));

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

    void SaveWindow::setPath(std::string path)
    {
        path_ = path;
    }

    void SaveWindow::save_image()
    {
        canvas_->getImage()->saveToFile(path_);
        close();
    }

    void SaveWindow::exec()
    {
        app_->exec();
    }

    void SaveWindow::close()
    {
        app_->close();        
    }

    SaveWindow::~SaveWindow() {};
}