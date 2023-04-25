#include "HSVwindow.h"

HSVwindow::HSVwindow(Vector2d shape, const Texture &texture, HSVpalette *hsv_palette, Editor *r_editor, Editor *g_editor, Editor *b_editor, Button *ok_button, Button *cancel_button): MainWindow(shape, texture),
    hsv_palette_(hsv_palette),
    r_editor_(r_editor),
    g_editor_(g_editor),
    b_editor_(b_editor),
    ok_button_(ok_button),
    cancel_button_(cancel_button),
    color_(0.f, 0.f, 0.f)
    {
        hsv_palette_->set_command    ((Command <const Color&> *)  new SimpleCommand<HSVwindow, const Color&>  (this, &HSVwindow::change_color));
        r_editor_->set_editor_command((Command <const Event &> *) new SimpleCommand<HSVwindow, const Event &> (this, &HSVwindow::change_r));
        g_editor_->set_editor_command((Command <const Event &> *) new SimpleCommand<HSVwindow, const Event &> (this, &HSVwindow::change_g));
        b_editor_->set_editor_command((Command <const Event &> *) new SimpleCommand<HSVwindow, const Event &> (this, &HSVwindow::change_b));

        cancel_button_->set_left_click((Command<const Event &> *) new SimpleCommand<HSVwindow, const Event &> (this, &HSVwindow::close));
        ok_button_    ->set_left_click((Command<const Event &> *) new SimpleCommand<HSVwindow, const Event &> (this, &HSVwindow::close));

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

void HSVwindow::set_command(Command<const Color &> *command)
{
    hsv_window_command_ = command;
}

void HSVwindow::set_color(const Color &color)
{
    color_ = color;
    hsv_palette_->set_color(color_);

    if (hsv_window_command_)
    {
        hsv_window_command_->Execute(color_);
    }
}

void HSVwindow::change_r(const Event &event)
{
    std::string string = r_editor_->get_text();
    
    int new_r = string.size() > 0 ? std::stoi(string) : 0;
    new_r = new_r < 255 ? new_r : 255;

    color_.set_r(uint8_t(new_r));
    set_color(color_);
}

void HSVwindow::change_g(const Event &event)
{
    std::string string = g_editor_->get_text();

    int new_g = string.size() > 0 ? std::stoi(string) : 0;
    new_g = new_g < 255 ? new_g : 255;

    color_.set_g(uint8_t(new_g));
    set_color(color_);
}

void HSVwindow::change_b(const Event &event)
{
    std::string string = b_editor_->get_text();

    int new_b = string.size() > 0 ? std::stoi(string) : 0;
    new_b = new_b < 255 ? new_b : 255;

    color_.set_b(uint8_t(new_b));
    set_color(color_);
}

void HSVwindow::exec(const Event &event)
{
    app_ = new Application(this);
    app_->exec();
}

void HSVwindow::close(const Event &event)
{
    if (app_)
    {
        app_->close();
    }
}