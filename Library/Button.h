#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "Command.h"
#include "Event.h"
#include "Object.h"
#include "Text.h"

class Button : public Object
{
public:

    bool is_left_clicked_  = false;
    bool is_right_clicked_ = false;
    bool is_pressed_       = false;

    bool is_press_button_ = false;

    Color default_sprite_color_;
    Text text_;
    
    Button(Vector2d shape, Vector2d center, const Texture &texture = Texture(Color::White)) : Object(shape, center, texture), 
        default_sprite_color_(sprite_.getColor()),
        text_()
    {
        text_.setFont(Font::Times_new_roman);
    };

    Button(const Button& source) : Object(*(const Object *)&source),
        default_sprite_color_(source.default_sprite_color_),
        text_(source.text_),
        left_click_command_         (source.left_click_command_),
        left_release_command_ (source.left_release_command_),
        right_click_command_        (source.right_click_command_),
        right_release_command_(source.right_release_command_)
    {}
    
    Button &operator=(const Button &source)
    {
        Object::operator=(*(const Object *)&source);

        default_sprite_color_ = source.default_sprite_color_;        
        text_ = source.text_;
        left_click_command_          = source.left_click_command_;
        left_release_command_  = source.left_release_command_;
        right_click_command_         = source.right_click_command_;
        right_release_command_ = source.right_release_command_;

        return *this;
    }

    void setTextColor(const Color &color)
    {
        text_.setColor(color);
        set_text(text_);
    }

    void setCharacterSize(int text_size)
    {
        text_.setCharacterSize(text_size);
        set_text(text_);
    }

    void set_pressed(bool is_press_button)
    {
        is_press_button_ = is_press_button;
    }

    void set_left_click           (Command<const Event &> *command)
    {
        left_click_command_ = command;
    }
    void set_release_left_click   (Command<const Event &> *command)
    {
        left_release_command_ = command;
    }
    void set_right_click          (Command<const Event &> *command)
    {
        right_click_command_ = command;
    }
    void set_release_right_click  (Command<const Event &> *command)
    {
        right_release_command_ = command;
    }
    
    
    Command<const Event &> * get_left_click       ()
    {
        return left_click_command_;
    }
    Command<const Event &> * get_release_left_click  ()
    {
        return left_release_command_;
    }
    Command<const Event &> * get_right_click      ()
    {
        return right_click_command_;
    }
    Command<const Event &> * set_release_right_click  ()
    {
        return right_release_command_;
    }

    void set_click_color(const Color &color)
    {
           
    }

    void set_texture(const Texture &texture) override
    {
        Object::set_texture(texture);
        default_sprite_color_ = sprite_.getColor();
    }
    
    void setString(const std::string &text)
    {
        text_.setString(text);
        set_text(text_);
    }

    void set_text(const Text &text)
    {
        text_ = text;
        sprite_.setTexture(texture_);
        render_texture_->draw(sprite_);

        Vector2d text_position(0, 0);
        text_position.x_ = shape_.x_ / 2 - text_.getGlobalBounds().x_ / 2;
        text_position.y_ = shape_.y_ / 2 - text_.getGlobalBounds().y_; 
        text_.setPosition(text_position);

        render_texture_->draw(text_); 
    }

    void ClickLeftEvent     (const Event &event) override;
    void ReleasedLeftEvent  (const Event &event) override;

    void ClickRightEvent    (const Event &event) override;
    void ReleasedRightEvent (const Event &event) override;
    
    void MoveMouseEvent     (const Event &event) override;

    void print(const Event &event)
    {
        printf("CLICKED!!\n");
    }

protected:
    Command<const Event &> *left_click_command_          = nullptr;
    Command<const Event &> *left_release_command_  = nullptr;

    Command<const Event &> *right_click_command_         = nullptr;
    Command<const Event &> *right_release_command_ = nullptr;
};

