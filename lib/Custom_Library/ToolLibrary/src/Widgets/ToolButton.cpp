#include "ToolButton.hpp"
#include "../Event/Event.hpp"

namespace TOOL_SL
{
    ToolButton::ToolButton(SL::Vector2d shape, SL::Vector2d position) : 
        SL::Button(shape, position)
    {
        SL::Button::setLeftClick        (dynamic_cast<SL::Command<> *>(new SL::SimpleCommand<ToolButton>(this, &ToolButton::clickLeftEvent)));
        SL::Button::setReleaseLeftClick (dynamic_cast<SL::Command<> *>(new SL::SimpleCommand<ToolButton>(this, &ToolButton::releaseLeftEvent)));
        SL::Button::setRightClick       (dynamic_cast<SL::Command<> *>(new SL::SimpleCommand<ToolButton>(this, &ToolButton::clickRightEvent)));
        SL::Button::setReleaseRightClick(dynamic_cast<SL::Command<> *>(new SL::SimpleCommand<ToolButton>(this, &ToolButton::releaseRightEvent)));
    }


    ToolButton::~ToolButton()
    {
        delete tool_left_click_command_;
        delete tool_left_release_command_;
        delete tool_right_click_command_;
        delete tool_right_release_command_;
    }

    int ToolButton::getX()
    {
        return SL::Button::getPosition().x_;
    }

    void ToolButton::setX(int x)
    {
        SL::Button::setPosition(SL::Vector2d(static_cast<float>(x), SL::Button::getPosition().y_));
    }

    int ToolButton::getY()
    {
        return SL::Button::getPosition().y_;
    }

    void ToolButton::setY(int y)
    {
        SL::Button::setPosition(SL::Vector2d(SL::Button::getPosition().x_, static_cast<float>(y)));
    }

    int ToolButton::getW()
    {
        return SL::Button::getShape().x_;
    }

    void ToolButton::setW(int w)
    {
        SL::Button::setShape(SL::Vector2d(static_cast<float>(w), SL::Button::getShape().y_));
    }

    int ToolButton::getH()
    {
        return SL::Button::getShape().y_;
    }

    void ToolButton::setH(int h)
    {
        SL::Button::setShape(SL::Vector2d(SL::Button::getShape().x_, static_cast<float>(h)));
    }

    void ToolButton::setColor(booba::Color color)
    {
        SL::Button::setTexture(SL::Texture(SL::Color(color.r, color.g, color.b, color.a)));
    }

    void ToolButton::setText(std::string text)
    {
        SL::Button::setText(text);
    }

    void ToolButton::setLeftClick (booba::Command<> *command)
    {
        tool_left_click_command_ = command;
    }

    void ToolButton::setReleaseLeftClick (booba::Command<> *command)
    {
        tool_left_release_command_ = command;
    }

    void ToolButton::setRightClick (booba::Command<> *command)
    {
        tool_right_click_command_ = command;
    }

    void ToolButton::setReleaseRightClick (booba::Command<> *command)
    {
        tool_right_release_command_ = command;
    }

    booba::Command<> *ToolButton::getLeftClick()
    {
        return tool_left_click_command_;
    }

    void ToolButton::clickLeftEvent ()
    {
        if (tool_left_click_command_ != nullptr)
        {
            tool_left_click_command_->Execute();
        }
    }

    booba::Command<> *ToolButton::getReleaseLeftClick()
    {
        return tool_left_release_command_;
    }

    void ToolButton::releaseLeftEvent ()
    {
        if (tool_left_release_command_ != nullptr)
        {
            tool_left_release_command_->Execute();
        }
    }

    booba::Command<> *ToolButton::getRightClick()
    {
        return tool_right_click_command_;
    }

    void ToolButton::clickRightEvent ()
    {
        if (tool_right_click_command_ != nullptr)
        {
            tool_right_click_command_->Execute();
        }
    }

    booba::Command<> *ToolButton::getReleaseRightClick()
    {
        return tool_right_release_command_;
    }

    void ToolButton::releaseRightEvent ()
    {
        if (tool_right_release_command_ != nullptr)
        {
            tool_right_release_command_->Execute();
        }
    }
}