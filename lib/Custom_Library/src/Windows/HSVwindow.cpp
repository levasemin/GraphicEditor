#include "HSVwindow.hpp"

namespace CUST_SL
{

    HSVwindow::HSVwindow(SL::Vector2d shape, const SL::Texture &texture, HSVpalette *hsv_palette, 
                                                                         SL::Editor *r_editor, 
                                                                         SL::Editor *g_editor,
                                                                         SL::Editor *b_editor,
                                                                         SL::Button *ok_button, 
                                                                         SL::Button *cancel_button): 
        MainWindow(shape, texture),
        hsv_palette_(hsv_palette),
        r_editor_(r_editor),
        g_editor_(g_editor),
        b_editor_(b_editor),
        ok_button_(ok_button),
        cancel_button_(cancel_button),
        color_(),
        prev_color_()
        {
            hsv_palette_->setCommand        (static_cast<SL::Command <const SL::Color&> *>(new SL::SimpleCommand<HSVwindow, const SL::Color&>  (this, &HSVwindow::change_color)));
            r_editor_->setEditorCommand     (static_cast<SL::Command <std::string> *>     (new SL::SimpleCommand<HSVwindow, std::string> (this, &HSVwindow::change_r)));
            g_editor_->setEditorCommand     (static_cast<SL::Command <std::string> *>     (new SL::SimpleCommand<HSVwindow, std::string> (this, &HSVwindow::change_g)));
            b_editor_->setEditorCommand     (static_cast<SL::Command <std::string> *>     (new SL::SimpleCommand<HSVwindow, std::string> (this, &HSVwindow::change_b)));

            add(hsv_palette_);
            add(r_editor_);
            add(g_editor_);
            add(b_editor_);
            add(ok_button_);
            add(cancel_button_);
        };

    HSVwindow::~HSVwindow()
    {
        delete hsv_palette_->getCommand();
        delete r_editor_->getEditorCommand();
        delete g_editor_->getEditorCommand();
        delete b_editor_->getEditorCommand();
    }

    void HSVwindow::change_color(const SL::Color &color)
    {            
        color_ = color;

        std::string r = std::to_string(static_cast<int>(color_.get_r()));
        std::string g = std::to_string(static_cast<int>(color_.get_g()));
        std::string b = std::to_string(static_cast<int>(color_.get_b()));
        
        r_editor_->setText(r);
        g_editor_->setText(g);
        b_editor_->setText(b);

        if (hsv_window_command_)
        {
            hsv_window_command_->Execute(color);
        }
    }

    SL::Command<const SL::Color &> *HSVwindow::getCommand()
    {
        return hsv_window_command_;
    }

    void HSVwindow::setCommand(SL::Command<const SL::Color &> *command)
    {
        hsv_window_command_ = command;
    }

    void HSVwindow::setColor(const SL::Color &color)
    {
        color_ = color;
        
        r_editor_->setText(std::to_string(static_cast<int>(color.get_r())));
        g_editor_->setText(std::to_string(static_cast<int>(color.get_g())));
        b_editor_->setText(std::to_string(static_cast<int>(color.get_b())));

        hsv_palette_->setColor(color_);

        if (hsv_window_command_)
        {
            hsv_window_command_->Execute(color_);
        }
    }

    void HSVwindow::change_r(std::string string)
    {            
        if (string.size() != 0)
        {
            if ('0' > string[string.size() - 1] || string[string.size() - 1] > '9')
            {
                string.resize(string.size() - 1);
                r_editor_->setText(string.c_str());
            
                return;
            }
        }
        
        int new_r = string.size() > 0 ? std::stoi(string) : 0;
        new_r = new_r < 255 ? new_r : 255;

        color_.set_r(static_cast<uint8_t>(new_r));
        setColor(color_);
    }

    void HSVwindow::change_g(std::string string)
    {
        if (string.size() != 0)
        {
            if ('0' > string[string.size() - 1] || string[string.size() - 1] > '9')
            {
                string.resize(string.size() - 1);
                g_editor_->setText(string.c_str());
                
                return;
            }
        }

        int new_g = string.size() > 0 ? std::stoi(string) : 0;
        new_g = new_g < 255 ? new_g : 255;

        color_.set_g(static_cast<uint8_t>(new_g));
        setColor(color_);
    }

    void HSVwindow::change_b(std::string string)
    {
        if (string.size() != 0)
        {
            if ('0' > string[string.size() - 1] || string[string.size() - 1] > '9')
            {
                string.resize(string.size() - 1);
                b_editor_->setText(string.c_str());
                return;
            }
        }

        int new_b = string.size() > 0 ? std::stoi(string) : 0;
        new_b = new_b < 255 ? new_b : 255;

        color_.set_b(static_cast<uint8_t>(new_b));
        setColor(color_);
    }

    void HSVwindow::exec(const SL::Event &event)
    {
        app_ = new SL::Application(this);
        app_->exec();
    }

    void HSVwindow::close(const SL::Event &event)
    {
        if (app_)
        {
            app_->close();
        }
    }
}