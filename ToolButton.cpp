#include "ToolButton.h"

void ToolButton::ToolClickLeftEvent (const Event &event)
{
    if (tool_left_click_command_ != nullptr)
    {
        Event new_event;
        new_event.type_ = EventType::ButtonClicked;
        new_event.Oleg_.bcedata.id = (uint64_t)this;
        tool_left_click_command_->Execute(convert_event(new_event));
    }
}

void ToolButton::ToolReleasedLeftEvent (const Event &event)
{
    if (tool_left_release_command_ != nullptr)
    {
        Event new_event;
        new_event.type_ = EventType::MouseReleased;
        new_event.Oleg_.mredata.button = MouseButton::Left;
        tool_left_release_command_->Execute(convert_event(new_event));
    }
}

void ToolButton::ToolClickRightEvent (const Event &event)
{
    if (tool_right_click_command_ != nullptr)
    {
        Event new_event;
        new_event.type_ = EventType::ButtonClicked;
        new_event.Oleg_.bcedata.id = (uint64_t)this;
        tool_right_click_command_->Execute(convert_event(new_event));
    }
}

void ToolButton::ToolReleasedRightEvent (const Event &event)
{
    if (right_release_command_ != nullptr)
    {
        Event new_event;
        new_event.type_ = EventType::MouseReleased;
        new_event.Oleg_.mredata.button = MouseButton::Right;
        tool_right_release_command_->Execute(convert_event(new_event));
    }
}