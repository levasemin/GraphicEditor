#include "ToolButton.h"
#include "../../Custom_Widgets/Event.h"


void ToolButton::ToolClickLeftEvent (const SL::Event &event)
{
    if (tool_left_click_command_ != nullptr)
    {
        SL::Event new_event;
        new_event.type_ = SL::EventType::ButtonClicked;
        new_event.Oleg_.bcedata.id = (uint64_t)this;
        tool_left_click_command_->Execute(convert_event(new_event));
    }
}

void ToolButton::ToolReleasedLeftEvent (const SL::Event &event)
{
    if (tool_left_release_command_ != nullptr)
    {
        SL::Event new_event;
        new_event.type_ = SL::EventType::MouseReleased;
        new_event.Oleg_.mredata.button = SL::MouseButton::Left;
        tool_left_release_command_->Execute(convert_event(new_event));
    }
}

void ToolButton::ToolClickRightEvent (const SL::Event &event)
{
    if (tool_right_click_command_ != nullptr)
    {
        SL::Event new_event;
        new_event.type_ = SL::EventType::ButtonClicked;
        new_event.Oleg_.bcedata.id = (uint64_t)this;
        tool_right_click_command_->Execute(convert_event(new_event));
    }
}

void ToolButton::ToolReleasedRightEvent (const SL::Event &event)
{
    if (right_release_command_ != nullptr)
    {
        SL::Event new_event;
        new_event.type_ = SL::EventType::MouseReleased;
        new_event.Oleg_.mredata.button = SL::MouseButton::Right;
        tool_right_release_command_->Execute(convert_event(new_event));
    }
}