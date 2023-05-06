#pragma once

#include "../../Graphic-Library/GraphLib/GraphLib.h"
#include "../../Custom_Widgets/Custom_Widgets.h"



class ToolHorizontalScrollBar : public SL::HorizontalScrollBar
{
public:
    int64_t min_value_ = 0;
    int64_t max_value_ = 0;

    SL::Command<const booba::Event &> *tool_scroll_command_ = nullptr;

    ToolHorizontalScrollBar(SL::Vector2d shape, SL::Vector2d position, int64_t min_value, int64_t max_value): 
        SL::HorizontalScrollBar(shape, position, float(min_value),  float(max_value)),
        min_value_(min_value),
        max_value_(max_value)
    {
        scroll_command_ = (SL::Command<const SL::Event &> *) new SL::SimpleCommand<ToolHorizontalScrollBar, const SL::Event &>(this, &ToolHorizontalScrollBar::tool_scroll_bar);
    }

    ToolHorizontalScrollBar(const ToolHorizontalScrollBar& source) : SL::HorizontalScrollBar(*(const SL::HorizontalScrollBar *) &source),
        tool_scroll_command_(source.tool_scroll_command_) 
    {}

    ToolHorizontalScrollBar &operator=(const ToolHorizontalScrollBar& source) 
    {
        SL::HorizontalScrollBar::operator=(*(const SL::HorizontalScrollBar *) &source);
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

    void tool_scroll_bar(const SL::Event &event)
    {
        if (tool_scroll_command_)
        {
            SL::Event new_event;
            new_event.Oleg_.smedata.id = (uint64_t)this;
            new_event.type_ = SL::EventType::ScrollbarMoved;
            new_event.Oleg_.smedata.value = event.Oleg_.smedata.value;
            booba::Event booba_event = convert_event(new_event);
            tool_scroll_command_->Execute(booba_event);
        }
    }

    void set_scroll_command(SL::Command<const booba::Event &> *command)
    {
        tool_scroll_command_ = command;
    }

    ~ToolHorizontalScrollBar() {}
};