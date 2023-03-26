#pragma once

#include "Texture.h"
#include "CompositeObject.h"
#include "Command.h"
#include "Button.h"
#include "SimpleCommand.h"
#include "Command.h"
#include "Container.h"

class ComboBox : public Button
{
    bool is_showed_ = false;
    Container item_box_;

public:

    ComboBox(Vector2d shape, Vector2d center, const Texture &texture = Texture(Color::Blue)) : Button(shape, center, texture),
        item_box_(Vector2d(shape.x_ * 2, shape.y_ * 10), center + shape / 2 + Vector2d(0, shape.y_ * 5))
    {
    }

    void ClickLeftEvent(const Event &event) override
    {
        if (point_belonging(event.Oleg_.mbedata.pos))
        {
            if (is_showed_)
            {
                parent_->remove(&item_box_);
            }

            else
            {
                parent_->add(&item_box_);
            }

            is_showed_ = !is_showed_;
        }

        else if (is_showed_)
        {
            if (!item_box_.point_belonging(event.Oleg_.mbedata.pos) && !point_belonging(event.Oleg_.mbedata.pos))
            {
                parent_->remove(&item_box_);
                is_showed_ = false;
            }
        }
    }

    void add(Widget *widget) override
    {
        item_box_.add(widget);
    }
    
    Vector2d get_box_shape()
    {
        return item_box_.get_shape();
    }

    void set_box_shape(const Vector2d &shape)
    {
        item_box_.set_shape(shape);
        item_box_.set_center(center_ + shape_ / 2 + Vector2d(0, shape.y_ / 2));
    }
    
    void set_box_texture(const Texture &texture)
    {
        item_box_.set_texture(texture);
    }
};