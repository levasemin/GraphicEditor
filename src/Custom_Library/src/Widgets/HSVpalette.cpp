#include "HSVpalette.hpp"

namespace CUST_SL
{
    HSVpalette::HSVpalette(SL::Vector2d shape, SL::Vector2d position) : SL::CompositeObject(shape, position),
        palette_(SL::Vector2d(shape.x_ - 20.f, shape.y_), SL::Vector2d(0, 0)),
        scroll_bar_(SL::Vector2d(20.f, shape.y_), SL::Vector2d(shape.x_ - 20, 0.f), 0.f, 360.f)
    {
        scroll_bar_.setScrollCommand((SL::Command<float> *) new SL::SimpleCommand<HSVfield, float>(&palette_, &HSVfield::change_H));
        scroll_bar_.setScrollButtonShape(SL::Vector2d(20, 4));
        
        add(&scroll_bar_);
        add(&palette_);

        SL::Image rgb_scrollbar_image(scroll_bar_.getShape(), SL::Color(0.f, 0.f, 0.f));

        for (float y = 0; y < rgb_scrollbar_image.getSize().y_; y++)
        {
            for (float x = 0; x < rgb_scrollbar_image.getSize().x_; x++)
            {
                SL::Color color = SL::Color((1.f - y / rgb_scrollbar_image.getSize().y_) * 360.f, 1.f, 1.f);
                rgb_scrollbar_image.setPixel(SL::Vector2d(x, y), color);
            }
        }

        scroll_bar_.setTexture(rgb_scrollbar_image.getTexture());
    }

    HSVpalette::~HSVpalette()
    {
        delete scroll_bar_.getScrollCommand();
    }

    SL::Color HSVpalette::getColor()
    {
        return palette_.getColor();
    }

    void HSVpalette::setColor(const SL::Color &color)
    {
        float value = 360.f - color.get_h();
        scroll_bar_.setValue(value);
        
        palette_.setColor(color);
    }

    SL::Command<const SL::Color&> *HSVpalette::getCommand()
    {
        return palette_.getCommand();
    }

    void HSVpalette::setCommand(SL::Command<const SL::Color&> *command)
    {
        palette_.setCommand(command);
    }

    HSVpalette::HSVfield::HSVfield(SL::Vector2d shape, SL::Vector2d position) : SL::Button(shape, position),
        color_(360.f, 0.f, 0.f),
        old_color_(360.f, 0.f, 0.f),
        image_(SL::Vector2d(shape.x_, shape.y_), SL::Color(360.f, 0.f, 0.f))
    {
        updateTexture();
    }

    void HSVpalette::HSVfield::updateTexture()
    {
        for (float y = 0; y < image_.getSize().y_; y++)
        {
            for (float x = 0; x < image_.getSize().x_; x++)
            {
                image_.setPixel(SL::Vector2d(x, y), SL::Color(color_.get_h(), x / image_.getSize().x_, 1.f - y / image_.getSize().y_));
            }
        }
        
        setTexture(image_.getTexture());
    }

    void HSVpalette::HSVfield::updateCross()
    {        
        for (int y = 0; y < int(image_.getSize().y_); y++)
        {
            int x = int(old_color_.get_s() * image_.getSize().x_);
            SL::Color color(color_.get_h(), x / image_.getSize().x_, 1.f - y / image_.getSize().y_);
            image_.setPixel(SL::Vector2d(int(old_color_.get_s() * image_.getSize().x_), y), color);
            image_.setPixel(SL::Vector2d(int(color_.get_s() * image_.getSize().x_), y), SL::Color::White);
        }

        for (int x = 0; x < int(image_.getSize().x_ - 1); x++)
        {
            int y = int((1 - old_color_.get_v()) * image_.getSize().y_ - 1);
            SL::Color color(color_.get_h(), x / image_.getSize().x_, 1.f - y / image_.getSize().y_);
            image_.setPixel(SL::Vector2d(x, int((1 - old_color_.get_v()) * image_.getSize().y_ - 1)), color);
            image_.setPixel(SL::Vector2d(x, int((1 - color_.get_v()) * image_.getSize().y_ - 1)), SL::Color::White);
        }

        setTexture(image_.getTexture());
    }

    void HSVpalette::HSVfield::setColor(const SL::Color &color)
    {
        if (color.get_h() != color_.get_h())
        {
            color_ = color;
            updateTexture();
        }
        else 
        {
            color_ = color;
            updateCross();
        }

        if (palette_command_)
        {
            palette_command_->Execute(color_);
        }
    }

    SL::Color HSVpalette::HSVfield::getColor()
    {
        return color_;
    }   

    void HSVpalette::HSVfield::change_H(float value)
    {
        SL::Color color = color_;

        color.set_h((360.f - value));
        setColor(color);
    }

    void HSVpalette::HSVfield::moveMouseEvent(const SL::Event &event)
    {
        if (clicked_)
        {
            if (pointBelong(event.Oleg_.metion.pos))
            {
                old_color_ = color_;

                color_.set_s((event.Oleg_.metion.pos.x_ - getField().first.x_) / image_.getSize().x_);
                color_.set_v(1.f - (event.Oleg_.metion.pos.y_ - getField().first.y_) / image_.getSize().y_);

                setColor(color_);
            }
        }
    }    

    void HSVpalette::HSVfield::clickLeftEvent(const SL::Event &event)
    {
        if (pointBelong(event.Oleg_.mpedata.pos))
        {
            clicked_ = true;

            old_color_ = color_;

            color_.set_s((event.Oleg_.mpedata.pos.x_ - getField().first.x_) / getShape().x_);
            color_.set_v(1.f - (event.Oleg_.mpedata.pos.y_ - getField().first.y_) / getShape().y_);
            
            setColor(color_);
        }

        else
        {
            clicked_ = false;
        }
    }

    void HSVpalette::HSVfield::releaseLeftEvent(const SL::Event &event)
    {
        clicked_ = false;
    }

    void HSVpalette::HSVfield::setCommand(SL::Command<const SL::Color &> *command)
    {
        palette_command_ = command;
    }

    SL::Command<const SL::Color &> *HSVpalette::HSVfield::getCommand()
    {
        return palette_command_;
    }
}