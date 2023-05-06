#include "HSVwindow.h"

HSVwindow::HSVwindow(SL::Vector2d shape, const SL::Texture &texture, HSVpalette *hsv_palette, SL::Editor *r_editor, SL::Editor *g_editor, SL::Editor *b_editor, SL::Button *ok_button, SL::Button *cancel_button): MainWindow(shape, texture),
    hsv_palette_(hsv_palette),
    r_editor_(r_editor),
    g_editor_(g_editor),
    b_editor_(b_editor),
    ok_button_(ok_button),
    cancel_button_(cancel_button),
    color_(),
    prev_color_()
    {
        hsv_palette_->set_command    ((SL::Command <const Color&> *)      new SL::SimpleCommand<HSVwindow, const Color&>  (this, &HSVwindow::change_color));
        r_editor_->set_editor_command((SL::Command <const SL::Event &> *) new SL::SimpleCommand<HSVwindow, const SL::Event &> (this, &HSVwindow::change_r));
        g_editor_->set_editor_command((SL::Command <const SL::Event &> *) new SL::SimpleCommand<HSVwindow, const SL::Event &> (this, &HSVwindow::change_g));
        b_editor_->set_editor_command((SL::Command <const SL::Event &> *) new SL::SimpleCommand<HSVwindow, const SL::Event &> (this, &HSVwindow::change_b));

        add(hsv_palette_);
        add(r_editor_);
        add(g_editor_);
        add(b_editor_);
        add(ok_button_);
        add(cancel_button_);
    };

HSVwindow::HSVwindow(const HSVwindow &source): MainWindow(*(const MainWindow *)&source),
    hsv_palette_(source.hsv_palette_),
    r_editor_(source.r_editor_),
    g_editor_(source.g_editor_),
    b_editor_(source.b_editor_),
    color_(source.color_),
    prev_color_(source.prev_color_),
    hsv_window_command_(source.hsv_window_command_)
{}

HSVwindow &HSVwindow::operator=(const HSVwindow &source)
{
    MainWindow::operator= (*(const MainWindow *)&source);
    hsv_palette_ = source.hsv_palette_;
    r_editor_    = source.r_editor_;
    g_editor_    = source.g_editor_;
    b_editor_    = source.b_editor_;
    
    color_ = source.color_;
    
    hsv_window_command_ = source.hsv_window_command_;

    return *this;
}

void HSVwindow::change_color(const Color &color)
{            
    color_ = color;

    std::string r = std::to_string(int(color_.get_r()));
    std::string g = std::to_string(int(color_.get_g()));
    std::string b = std::to_string(int(color_.get_b()));
    r_editor_->setString(r);
    g_editor_->setString(g);
    b_editor_->setString(b);

    if (hsv_window_command_)
    {
        hsv_window_command_->Execute(color);
    }
}

void HSVwindow::set_command(SL::Command<const Color &> *command)
{
    hsv_window_command_ = command;
}

void HSVwindow::set_color(const Color &color)
{
    color_ = color;
    
    r_editor_->setString(std::to_string(int(color.get_r())));
    g_editor_->setString(std::to_string(int(color.get_g())));
    b_editor_->setString(std::to_string(int(color.get_b())));

    hsv_palette_->set_color(color_);

    if (hsv_window_command_)
    {
        hsv_window_command_->Execute(color_);
    }
}

void HSVwindow::change_r(const SL::Event &event)
{
    std::string string = event.Oleg_.textedata.text;
            
    if (string.size() != 0)
    {
        if ('0' > string[string.size() - 1] || string[string.size() - 1] > '9')
        {
            string.resize(string.size() - 1);
            r_editor_->setString(string.c_str());
        
            return;
        }
    }
    
    int new_r = string.size() > 0 ? std::stoi(string) : 0;
    new_r = new_r < 255 ? new_r : 255;

    color_.set_r(uint8_t(new_r));
    set_color(color_);
}

void HSVwindow::change_g(const SL::Event &event)
{
    std::string string = event.Oleg_.textedata.text;

    if (string.size() != 0)
    {
        if ('0' > string[string.size() - 1] || string[string.size() - 1] > '9')
        {
            string.resize(string.size() - 1);
            g_editor_->setString(string.c_str());
            
            return;
        }
    }

    int new_g = string.size() > 0 ? std::stoi(string) : 0;
    new_g = new_g < 255 ? new_g : 255;

    color_.set_g(uint8_t(new_g));
    set_color(color_);
}

void HSVwindow::change_b(const SL::Event &event)
{
    std::string string = event.Oleg_.textedata.text;

    if (string.size() != 0)
    {
        if ('0' > string[string.size() - 1] || string[string.size() - 1] > '9')
        {
            string.resize(string.size() - 1);
            b_editor_->setString(string.c_str());
            return;
        }
    }

    int new_b = string.size() > 0 ? std::stoi(string) : 0;
    new_b = new_b < 255 ? new_b : 255;

    color_.set_b(uint8_t(new_b));
    set_color(color_);
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