#pragma once

#include "../../Graphic-Library/GraphLib/GraphLib.h"

using namespace SL;

class ToolHorizontalScrollBar : public HorizontalScrollBar
{
public:
    int64_t min_value_ = 0;
    int64_t max_value_ = 0;

    Command<const booba::Event &> *tool_scroll_command_ = nullptr;

    ToolHorizontalScrollBar(Vector2d shape, Vector2d position, int64_t min_value, int64_t max_value): 
        HorizontalScrollBar(shape, position, float(min_value),  float(max_value)),
        min_value_(min_value),
        max_value_(max_value)
    {
        scroll_command_ = (Command<const Event &> *) new SimpleCommand<ToolHorizontalScrollBar, const Event &>(this, &ToolHorizontalScrollBar::tool_scroll_bar);
    }

    ToolHorizontalScrollBar(const ToolHorizontalScrollBar& source) : HorizontalScrollBar(*(const HorizontalScrollBar *) &source),
        tool_scroll_command_(source.tool_scroll_command_) 
    {}

    ToolHorizontalScrollBar &operator=(const ToolHorizontalScrollBar& source) 
    {
        HorizontalScrollBar::operator=(*(const HorizontalScrollBar *) &source);
        tool_scroll_command_ = source.tool_scroll_command_;

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

    void tool_scroll_bar(const Event &event)
    {
        if (tool_scroll_command_)
        {
            Event new_event;
            new_event.Oleg_.smedata.id = (uint64_t)this;
            new_event.type_ = EventType::ScrollbarMoved;
            new_event.Oleg_.smedata.value = event.Oleg_.smedata.value;
            booba::Event booba_event = convert_event(new_event);
            tool_scroll_command_->Execute(booba_event);
        }
    }

    void set_scroll_command(Command<const booba::Event &> *command)
    {
        tool_scroll_command_ = command;
    }

    ~ToolHorizontalScrollBar() {}
};