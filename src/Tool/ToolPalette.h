#pragma once 

#include "../Graphic-Library/GraphLib/GraphLib.h"


class ToolPalette : public CompositeObject
{

public:

    Vector2d curr_pos_;

    ToolPalette(Vector2d shape, Vector2d position, const Texture &texture) : CompositeObject(shape, position, texture),
        curr_pos_(0.f, 0.f)
    {
        
    }

    void add(Widget *widget) override
    {
        if (!doublecmp(curr_pos_.y_, 0))
        {
            if (curr_pos_.y_ + widget->get_shape().y_ < shape_.y_)
            {
                widget->set_position(Vector2d(0, curr_pos_.y_));
                curr_pos_ += widget->get_shape();
                CompositeObject::add(widget);
            }
        }

        else
        {
            if (curr_pos_.y_ + widget->get_shape().y_ + 10 < shape_.y_)
            {
                widget->set_position(Vector2d(0, curr_pos_.y_ + 10));
                curr_pos_ += widget->get_shape();
                CompositeObject::add(widget);
            }
        }
    }
};