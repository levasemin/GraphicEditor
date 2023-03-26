#include "Button.h"

void Button::MoveMouseEvent(const Event &event)
{
    if ((!is_press_button_ || !is_pressed_))
    {
        if (point_belonging(event.Oleg_.motion.pos))
        {
            Color new_color = default_sprite_color_;
        
            new_color.set_a(uint8_t(new_color.get_a() / 3 * 2));

            sprite_.setColor(new_color);
        }

        else if (!is_press_button_ || !is_pressed_) 
        {
            sprite_.setColor(default_sprite_color_);
        }
    }
}


void Button::ClickLeftEvent (const Event &event)
{
    if (point_belonging(Vector2d(event.Oleg_.mbedata.pos)))
    {
        is_left_clicked_ = true;
        is_pressed_ = !is_pressed_;

        if (is_press_button_)
        {
            if (is_pressed_)
            {
                Color new_color = default_sprite_color_;
        
                new_color.set_a(uint8_t(new_color.get_a() / 3 * 2));

                sprite_.setColor(new_color);
            }

            else
            {
                sprite_.setColor(default_sprite_color_);
            }
        }

        if (left_click_command_ != nullptr)
        {
            Event new_event;
            new_event.type_ = EventType::ButtonClicked;
            new_event.Oleg_.bcedata.id = (uint64_t)this;
            left_click_command_->Execute(new_event);
        }
    }
}

void Button::ReleasedLeftEvent (const Event &event)
{
    if (left_release_command_ != nullptr)
    {
        left_release_command_->Execute(event);
    }

    is_left_clicked_ = false;
}

void Button::ClickRightEvent (const Event &event)
{
    if (point_belonging(event.Oleg_.mbedata.pos))
    {
        is_right_clicked_ = true;

        if (right_click_command_ != nullptr)
        {
            Event new_event;
            new_event.type_ = EventType::ButtonClicked;
            new_event.Oleg_.bcedata.id = (uint64_t)this;
            right_click_command_->Execute(new_event);
        }
    }
}
void Button::ReleasedRightEvent (const Event &event)
{
    if (right_release_command_ != nullptr)
    {
        right_release_command_->Execute(event);
    }

    is_right_clicked_ = false;
}