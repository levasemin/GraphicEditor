#include "ToolButton.hpp"
#include "../Event/Event.hpp"

namespace TOOL_SL
{
    ToolButton::ToolButton(SL::Button *button) : 
        button_(button)
    {
        button_->setLeftClick        (dynamic_cast<SL::Command<> *>(new SL::SimpleCommand<ToolButton>(this, &ToolButton::clickLeftEvent)));
        button_->setReleaseLeftClick (dynamic_cast<SL::Command<> *>(new SL::SimpleCommand<ToolButton>(this, &ToolButton::releaseLeftEvent)));
        button_->setRightClick       (dynamic_cast<SL::Command<> *>(new SL::SimpleCommand<ToolButton>(this, &ToolButton::clickRightEvent)));
        button_->setReleaseRightClick(dynamic_cast<SL::Command<> *>(new SL::SimpleCommand<ToolButton>(this, &ToolButton::releaseRightEvent)));
    }


    ToolButton::~ToolButton()
    {
        delete tool_left_click_command_;
        delete tool_left_release_command_;
        delete tool_right_click_command_;
        delete tool_right_release_command_;
    }

    booba::Vector2d ToolButton::getPosition() const
    {
        return booba::Vector2d(button_->getPosition().x_, button_->getPosition().y_);
    }

    void ToolButton::setPosition(booba::Vector2d position)
    {
        button_->setPosition(SL::Vector2d(position.x_, position.y_));
    }

    booba::Vector2d ToolButton::getShape() const
    {
        return booba::Vector2d(button_->getShape().x_, button_->getShape().y_);
    }

    void ToolButton::setShape(booba::Vector2d shape)
    {
        button_->setShape(SL::Vector2d(shape.x_, shape.y_));
    }


    void ToolButton::setColor(booba::Color color)
    {
        button_->setTexture(SL::Texture(SL::Color(color.r, color.g, color.b, color.a)));
    }

    void ToolButton::setText(std::string text)
    {
        button_->setText(text);
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