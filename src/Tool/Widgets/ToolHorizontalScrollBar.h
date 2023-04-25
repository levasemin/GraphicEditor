#pragma once

#include "../../Graphic-Library/GraphLib/GraphLib.h"


class ToolHorizontalScrollBar : public HorizontalScrollBar
{
public:
    int64_t min_value_ = 0;
    int64_t max_value_ = 0;

    Command<const booba::Event &> *scroll_command_ = nullptr;
    ToolHorizontalScrollBar(Vector2d shape, Vector2d position, int64_t min_value, int64_t max_value): 
        HorizontalScrollBar(shape, position),
        min_value_(min_value),
        max_value_(max_value)
    {

    }

    ToolHorizontalScrollBar(const ToolHorizontalScrollBar& source) : HorizontalScrollBar(*(const HorizontalScrollBar *) &source),
        scroll_command_(source.scroll_command_) 
    {}

    ToolHorizontalScrollBar &operator=(const ToolHorizontalScrollBar& source) 
    {
        HorizontalScrollBar::operator=(*(const HorizontalScrollBar *) &source);
        scroll_command_ = source.scroll_command_;

        return *this;
    }
    
    void set_min(int64_t min_value)
    {
        min_value_ = min_value;
    }

    void set_max(int64_t max_value)
    {
        max_value_ = max_value;
    }

    void scroll_bar(float value) override
    {
        Event new_event;
        new_event.type_ = EventType::ScrollbarMoved;
        new_event.Oleg_.smedata.id    = uint64_t(this);
        new_event.Oleg_.smedata.value = value < 0 ? 0 : value;
        new_event.Oleg_.smedata.value = value > 1 ? 1 : value;
        
        Vector2d offset = Vector2d(scroll_field_shape.x_, 0);
        offset *= value;

        offset.x_ = offset.x_ >= 0 ? offset.x_ : 0;
        offset.y_ = offset.y_ >= 0 ? offset.y_ : 0;
        
        Vector2d max_offset = Vector2d(shape_.x_ - left_button_.get_shape().x_ * 2 - scroll_button_.get_shape().x_, 0);
        offset.x_ = offset.x_ <= max_offset.x_ ? offset.x_ : max_offset.x_;
        offset.y_ = offset.y_ <= max_offset.y_ ? offset.y_ : max_offset.y_;
        
        set_local_offset(offset);

        if (scroll_command_)
        {
            new_event.Oleg_.smedata.value = float(max_value_ - min_value_) * new_event.Oleg_.smedata.value + float(min_value_);
            booba::Event booba_event = convert_event(new_event);
            scroll_command_->Execute(booba_event);
        }
    }

    void set_scroll_command(Command<const booba::Event &> *command)
    {
        scroll_command_ = command;
    }

    ~ToolHorizontalScrollBar() {}
};