#include "ColorPicker.hpp"

namespace CUST_SL
{
    ColorPicker::ColorPicker(SL::Vector2d shape, SL::Vector2d position, const SL::Texture &texture): 
        CompositeObject(shape, position, texture),
        fg_color_(booba::APPCONTEXT->fgColor.r, booba::APPCONTEXT->fgColor.g, booba::APPCONTEXT->fgColor.b, booba::APPCONTEXT->fgColor.a),
        bg_color_(booba::APPCONTEXT->bgColor.r, booba::APPCONTEXT->bgColor.g, booba::APPCONTEXT->bgColor.b, booba::APPCONTEXT->bgColor.a),
        foreground_button_(shape / 2, SL::Vector2d(0, 0), SL::Texture(SL::Color(booba::APPCONTEXT->fgColor.r, booba::APPCONTEXT->fgColor.g, booba::APPCONTEXT->fgColor.b, booba::APPCONTEXT->fgColor.a))),
        background_button_(shape / 2, shape / 2, SL::Texture(SL::Color(booba::APPCONTEXT->bgColor.r, booba::APPCONTEXT->bgColor.g, booba::APPCONTEXT->bgColor.b, booba::APPCONTEXT->bgColor.a))),
        swap_button_(shape / 5, SL::Vector2d(shape.x_ / 2, shape.y_ * 3 / 10))
    {
        SL::TextureManager &texture_manager = SL::TextureManager::getInstance();

        swap_button_.setTexture(texture_manager[SL::TextureManager::Icon::Swap]);

        add(&foreground_button_);
        add(&background_button_);
        add(&swap_button_);

        foreground_button_.setLeftClick((SL::Command<> *) new SL::SimpleCommand<ColorPicker>(this, &ColorPicker::open_foreground_hsv_window));
        background_button_.setLeftClick((SL::Command<> *) new SL::SimpleCommand<ColorPicker>(this, &ColorPicker::open_background_hsv_window));
        swap_button_.setLeftClick((SL::Command<> *) new SL::SimpleCommand<ColorPicker>(this, &ColorPicker::swap_colors));
    }

    ColorPicker::~ColorPicker()
    {
        delete foreground_button_.getLeftClick();
        delete background_button_.getLeftClick();
        delete swap_button_.getLeftClick();
        
        if (hsv_window_)
        {
            delete hsv_window_->getCommand();
            delete hsv_window_->ok_button_->getLeftClick();
            delete hsv_window_->cancel_button_->getLeftClick();
        }
    }

    void ColorPicker::change_color(const SL::Color &color)
    {
        if (color_type_ == Type::FOREGROUND_COLOR)
        {
            fg_color_ = color;
        }

        else
        {
            bg_color_ = color;
        }
    }

    void ColorPicker::swap_colors()
    {
        booba::Color color = booba::APPCONTEXT->fgColor;
        booba::APPCONTEXT->fgColor = booba::APPCONTEXT->bgColor;
        booba::APPCONTEXT->bgColor = color;

        foreground_button_.setTexture(SL::Texture(SL::Color(booba::APPCONTEXT->fgColor.r, 
                                                             booba::APPCONTEXT->fgColor.g, 
                                                             booba::APPCONTEXT->fgColor.b, 
                                                             booba::APPCONTEXT->fgColor.a)));

        background_button_.setTexture(SL::Texture(SL::Color(booba::APPCONTEXT->bgColor.r, 
                                                             booba::APPCONTEXT->bgColor.g, 
                                                             booba::APPCONTEXT->bgColor.b, 
                                                             booba::APPCONTEXT->bgColor.a)));
    }

    void ColorPicker::setColor()
    {
        if (color_type_ == Type::FOREGROUND_COLOR)
        {
            foreground_button_.setTexture(SL::Texture(fg_color_));
            booba::APPCONTEXT->fgColor = SL::Color::convert_color_uint(fg_color_);
        }

        else if (color_type_ == Type::BACKGROUND_COLOR)
        {
            background_button_.setTexture(SL::Texture(bg_color_));
            booba::APPCONTEXT->bgColor = SL::Color::convert_color_uint(bg_color_);
        }

        color_type_ = Type::NO_COLOR;

        if (hsv_window_)
        {
            hsv_window_->close();
        }
    }

    void ColorPicker::setHSVwindow(HSVwindow *hsv_window)
    {
        hsv_window_ = hsv_window;
        hsv_window_->setCommand((SL::Command<const SL::Color &> *) new SL::SimpleCommand<ColorPicker, const SL::Color&>(this, &ColorPicker::change_color));
        hsv_window_->ok_button_->setLeftClick((SL::Command<> *) new SL::SimpleCommand<ColorPicker>(this, &ColorPicker::setColor));
        hsv_window_->cancel_button_->setLeftClick((SL::Command<> *) new SL::SimpleCommand<ColorPicker> (this, &ColorPicker::return_color));
    }
    
    void ColorPicker::return_color()
    {
        if (color_type_ == Type::FOREGROUND_COLOR)
        {
            fg_color_ = SL::Color(booba::APPCONTEXT->fgColor.r, 
                                  booba::APPCONTEXT->fgColor.g, 
                                  booba::APPCONTEXT->fgColor.b, 
                                  booba::APPCONTEXT->fgColor.a);
            if (hsv_window_)
            {
                hsv_window_->setColor(fg_color_);
            }
        }

        else if (color_type_ == Type::BACKGROUND_COLOR)
        {
            bg_color_ = SL::Color(booba::APPCONTEXT->bgColor.r, 
                                  booba::APPCONTEXT->bgColor.g, 
                                  booba::APPCONTEXT->bgColor.b, 
                                  booba::APPCONTEXT->bgColor.a);
            if (hsv_window_)
            {                   
                hsv_window_->setColor(bg_color_);
            }
        }

        color_type_ = Type::NO_COLOR;

        if (hsv_window_)
        {
            hsv_window_->close();
        }
    }

    void ColorPicker::open_foreground_hsv_window()
    {
        color_type_ = Type::FOREGROUND_COLOR;
        
        if (hsv_window_)
        {
            hsv_window_->setColor(fg_color_);
            hsv_window_->exec();
        }
    }

    void ColorPicker::open_background_hsv_window()
    {
        color_type_ = Type::BACKGROUND_COLOR;
        
        if (hsv_window_)
        {
            hsv_window_->setColor(bg_color_);
            hsv_window_->exec();
        }
    }

    void ColorPicker::moveMouseEvent(const SL::Event &event)
    {
        SL::Color fg_color(booba::APPCONTEXT->fgColor.r, booba::APPCONTEXT->fgColor.g, booba::APPCONTEXT->fgColor.b, booba::APPCONTEXT->fgColor.a);
        SL::Color bg_color(booba::APPCONTEXT->bgColor.r, booba::APPCONTEXT->bgColor.g, booba::APPCONTEXT->bgColor.b, booba::APPCONTEXT->bgColor.a);

        if (fg_color_ != fg_color)
        {
            fg_color_ = fg_color;
            foreground_button_.setTexture(SL::Texture(fg_color_));
        }

        if (bg_color != bg_color)
        {
            bg_color_ = bg_color;
            background_button_.setTexture(SL::Texture(bg_color_));
        }
    }
}