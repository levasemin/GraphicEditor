#pragma once
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "GraphLib.h"
#include "Custom_Widgets.h"

class ToolButton : public SL::Button
{
public:

    ToolButton(SL::Vector2d shape, SL::Vector2d position, const SL::Texture &texture = SL::Texture(CUST_SL::Color::White)) : SL::Button(shape, position, texture)
    {
        left_click_command_    = (SL::Command<const SL::Event &> *) new SL::SimpleCommand<ToolButton, const SL::Event &>(this, &ToolButton::ToolClickLeftEvent);
        left_release_command_  = (SL::Command<const SL::Event &> *) new SL::SimpleCommand<ToolButton, const SL::Event &>(this, &ToolButton::ToolReleasedLeftEvent);
        right_click_command_   = (SL::Command<const SL::Event &> *) new SL::SimpleCommand<ToolButton, const SL::Event &>(this, &ToolButton::ToolClickRightEvent);
        right_release_command_ = (SL::Command<const SL::Event &> *) new SL::SimpleCommand<ToolButton, const SL::Event &>(this, &ToolButton::ToolReleasedRightEvent);
    }

    ToolButton(const ToolButton &source) : SL::Button(*(const SL::Button *)&source),
        tool_left_click_command_   (source.tool_left_click_command_),
        tool_left_release_command_ (source.tool_left_release_command_),
        tool_right_click_command_  (source.tool_right_click_command_),
        tool_right_release_command_(source.tool_right_release_command_)
    {}

    ToolButton &operator= (const ToolButton &source)
    {
        SL::Button::operator=(*(const SL::Button *)&source);

        left_click_command_    = source.left_click_command_;
        left_release_command_  = source.left_release_command_;
        right_click_command_   = source.right_click_command_;
        right_release_command_ = source.right_release_command_;

        return *this;
    }

    void set_left_click       (SL::Command<const booba::Event &> *command)
    {
        tool_left_click_command_ = command;
    }

    void set_release_left_click  (SL::Command<const booba::Event &> *command)
    {
        tool_left_release_command_ = command;
    }

    void set_right_click      (SL::Command<const booba::Event &> *command)
    {
        tool_right_click_command_ = command;
    }

    void set_release_right_click  (SL::Command<const booba::Event &> *command)
    {
        tool_right_release_command_ = command;
    }

    void ToolClickLeftEvent     (const SL::Event &event);
    void ToolReleasedLeftEvent  (const SL::Event &event);

    void ToolClickRightEvent    (const SL::Event &event);
    void ToolReleasedRightEvent (const SL::Event &event);

protected:
    SL::Command<const booba::Event &> *tool_left_click_command_    = nullptr;
    SL::Command<const booba::Event &> *tool_left_release_command_  = nullptr;

    SL::Command<const booba::Event &> *tool_right_click_command_   = nullptr;
    SL::Command<const booba::Event &> *tool_right_release_command_ = nullptr;
};
