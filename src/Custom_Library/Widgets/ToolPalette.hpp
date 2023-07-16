#pragma once

#include "GraphLib.hpp"



class ToolPalette : public SL::CompositeObject
{

public:

    SL::Vector2d curr_pos_;

    ToolPalette(SL::Vector2d shape, SL::Vector2d position, const SL::Texture &texture) : SL::CompositeObject(shape, position, texture),
        curr_pos_(0.f, 0.f)
    {

    }

    void add(SL::Widget *widget) override
    {
        if (!SL::doublecmp(curr_pos_.y_, 0.f))
        {
            if (curr_pos_.y_ + widget->get_shape().y_ < shape_.y_)
            {
                widget->set_position(SL::Vector2d(0.f, curr_pos_.y_));
                curr_pos_ += widget->get_shape();
                SL::CompositeObject::add(widget);
            }
        }

        else
        {
            if (curr_pos_.y_ + widget->get_shape().y_ + 10.f < shape_.y_)
            {
                widget->set_position(SL::Vector2d(0.f, curr_pos_.y_ + 10.f));
                curr_pos_ += widget->get_shape();
                SL::CompositeObject::add(widget);
            }
        }
    }
};
