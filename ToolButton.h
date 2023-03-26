#pragma once
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "Library/Button.h"
#include "Library/SimpleCommand.h"
#include "Library/Vector2d.h"
#include "tools.h"
#include "optionals.h"

class ToolButton : public Button
{
public:
    
    ToolButton(Vector2d shape, Vector2d center, const Texture &texture = Texture(Color::White)) : Button(shape, center, texture)
    {
        left_click_command_    = (Command<const Event &> *) new SimpleCommand<ToolButton, const Event &>(this, &ToolButton::ToolClickLeftEvent);
        left_release_command_  = (Command<const Event &> *) new SimpleCommand<ToolButton, const Event &>(this, &ToolButton::ToolReleasedLeftEvent);
        right_click_command_   = (Command<const Event &> *) new SimpleCommand<ToolButton, const Event &>(this, &ToolButton::ToolClickRightEvent);
        right_release_command_ = (Command<const Event &> *) new SimpleCommand<ToolButton, const Event &>(this, &ToolButton::ToolReleasedRightEvent);
    }
    
    ToolButton(const ToolButton &source) : Button(*(const Button *)&source),
        tool_left_click_command_   (source.tool_left_click_command_),
        tool_left_release_command_ (source.tool_left_release_command_),
        tool_right_click_command_  (source.tool_right_click_command_),
        tool_right_release_command_(source.tool_right_release_command_)
    {}
    
    ToolButton &operator= (const ToolButton &source)
    {
        Button::operator=(*(const Button *)&source);

        left_click_command_    = source.left_click_command_;
        left_release_command_  = source.left_release_command_;
        right_click_command_   = source.right_click_command_;
        right_release_command_ = source.right_release_command_;

        return *this;
    }

    void set_left_click       (Command<const booba::Event &> *command)
    {
        tool_left_click_command_ = command;
    }

    void set_release_left_click  (Command<const booba::Event &> *command)
    {
        tool_left_release_command_ = command;
    }

    void set_right_click      (Command<const booba::Event &> *command)
    {
        tool_right_click_command_ = command;
    }

    void set_release_right_click  (Command<const booba::Event &> *command)
    {
        tool_right_release_command_ = command;
    }
    
    void ToolClickLeftEvent     (const Event &event);
    void ToolReleasedLeftEvent  (const Event &event);

    void ToolClickRightEvent    (const Event &event);
    void ToolReleasedRightEvent (const Event &event);
    
protected:
    Command<const booba::Event &> *tool_left_click_command_    = nullptr;
    Command<const booba::Event &> *tool_left_release_command_  = nullptr;

    Command<const booba::Event &> *tool_right_click_command_   = nullptr;
    Command<const booba::Event &> *tool_right_release_command_ = nullptr;
};