#pragma once
#include "Command.h"
#include "Event.h"
#include "Object.h"
#include "Text.h"

class Label : public Object
{
public:

    bool is_left_clicked_  = false;
    bool is_right_clicked_ = false;
    
    Text text_;
    int alignment_ = 0;

    enum Alignment
    {
        CenterCenter,
        LeftCenter,
        RightCenter,
        LeftUp,
        LeftDown,
        RightUp,
        RightDown
    };

    Label(Vector2d shape, Vector2d center) : Object(shape, center), text_()
    {
        text_.setFont(Font::Times_new_roman);
        text_.setColor(Color::Black);
    };
    
    Label(const Label &source): Object(*(const Object *)&source),
        text_(source.text_),
        alignment_(source.alignment_)
    {}

    Label &operator=(const Label &source)
    {
        Object::operator=(*(const Object *)&source);
        text_ = source.text_;
        alignment_ = source.alignment_;
        return *this;
    }

    void setAlignment(int type)
    {
        alignment_ = type;
    }

    virtual void setString(const std::string &string)
    {
        text_.setString(string.c_str());
        redraw();
    }
    std::string getString()
    {
        return text_.getString();
    }

    void setCharacterSize(int text_size)
    {
        text_.setCharacterSize(text_size);
        set_text(text_);
    }
    
    void set_text(const Text &text)
    {
        text_ = text;
        redraw();
    }

    void setTextColor(const Color &color)
    {
        text_.setColor(color.get_sf_color());
    }

    void redraw()
    {
        render_texture_->clear();
        Sprite sprite(render_texture_->getSize(), texture_);
        render_texture_->draw(sprite);

        Vector2d text_position(0, 0);

        Vector2d text_shape = text_.getGlobalBounds();
        text_shape.y_ = text_shape.y_ > float(text_.getCharacterSize()) ? text_shape.y_ : float(text_.getCharacterSize()) / 10 * 7;

        switch (alignment_)
        {
            case Alignment::CenterCenter:
            {
                text_position.x_ = shape_.x_ / 2 - text_shape.x_ / 2;
                text_position.y_ = shape_.y_ / 2 - text_shape.y_; 
                break;
            }

            case Alignment::LeftCenter:
            {
                text_position.x_ = 0;
                text_position.y_ = shape_.y_ / 2 - text_shape.y_; 
                break;
            }

            case Alignment::LeftDown:
            {
                text_position.x_ = 0;
                text_position.y_ = shape_.y_ - text_shape.y_ * 2; 
                break;
            }
            case Alignment::LeftUp:
            {
                text_position.x_ = 0;
                text_position.y_ = -text_shape.y_ / 2; 
                break;
            }
            case Alignment::RightCenter:
            {
                text_position.x_ = shape_.x_ - text_shape.x_;
                text_position.y_ = shape_.y_ / 2 - text_shape.y_; 
                break;
            }
            case Alignment::RightDown:
            {
                text_position.x_ = shape_.x_ - text_shape.x_;
                text_position.y_ = shape_.y_ - text_shape.y_ * 2; 
                break;
            }
            case Alignment::RightUp:
            {
                text_position.x_ = shape_.x_ - text_shape.x_;
                text_position.y_ = -text_shape.y_ / 2;
            }
            default:
                break;
        }
        
        text_.setPosition(text_position);
        
        render_texture_->draw(text_); 

        render_texture_->display();
    }
};