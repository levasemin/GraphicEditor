#pragma once 

#include "Library/CompositeObject.h"

class ToolPalette : public CompositeObject
{

public:

    Vector2d curr_pos_;

    ToolPalette(Vector2d shape, Vector2d center, const Texture &texture) : CompositeObject(shape, center, texture),
        curr_pos_(0.f, 0.f)
    {
        
    }

    void add(Widget *widget) override
    {
        if (!doublecmp(curr_pos_.y_, 0))
        {
            if (curr_pos_.y_ + widget->get_shape().y_ < shape_.y_)
            {
                widget->set_center(Vector2d(widget->get_shape().x_ / 2, curr_pos_.y_ + widget->get_shape().y_));
                curr_pos_ += widget->get_shape();
                CompositeObject::add(widget);
            }
        }

        else
        {
            if (curr_pos_.y_ + widget->get_shape().y_ + 10 < shape_.y_)
            {
                widget->set_center(Vector2d(widget->get_shape().x_ / 2, curr_pos_.y_ + widget->get_shape().y_ + 10));
                curr_pos_ += widget->get_shape();
                CompositeObject::add(widget);
            }
        }
    }
};