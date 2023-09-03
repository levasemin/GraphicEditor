#include "ToolHorizontalScrollBar.hpp"

namespace TOOL_SL
{
    ToolHorizontalScrollBar::ToolHorizontalScrollBar(SL::HorizontalScrollBar *scroll_bar): 
        scroll_bar_(scroll_bar)
    {
        scroll_bar_->setScrollCommand(static_cast<SL::Command<float> *> (new SL::SimpleCommand<ToolHorizontalScrollBar, float>(this, &ToolHorizontalScrollBar::ToolsetValue)));    
    }

    ToolHorizontalScrollBar::~ToolHorizontalScrollBar()
    {
        delete scroll_bar_->getScrollCommand();
    }


    booba::Vector2d ToolHorizontalScrollBar::getPosition() const
    {
        return booba::Vector2d(scroll_bar_->getPosition().x_, scroll_bar_->getPosition().y_);
    }

    void ToolHorizontalScrollBar::setPosition(booba::Vector2d position)
    {
        scroll_bar_->setPosition(SL::Vector2d(position.x_, position.y_));
    }

    booba::Vector2d ToolHorizontalScrollBar::getShape() const
    {
        return booba::Vector2d(scroll_bar_->getShape().x_, scroll_bar_->getShape().y_);
    }

    void ToolHorizontalScrollBar::setShape(booba::Vector2d shape)
    {
        scroll_bar_->setShape(SL::Vector2d(shape.x_, shape.y_));
    }

    double ToolHorizontalScrollBar::getValue()
    {
        return scroll_bar_->getValue();
    }

    void ToolHorizontalScrollBar::setValue(double value)
    {
        scroll_bar_->setValue(value);
    }

    double ToolHorizontalScrollBar::getMinValue()
    {
        return scroll_bar_->getMinValue();
    }

    void ToolHorizontalScrollBar::setMinValue(double value)
    {
        scroll_bar_->setMinValue(value);
    }

    double ToolHorizontalScrollBar::getMaxValue()
    {
        return scroll_bar_->getMaxValue();
    }

    void ToolHorizontalScrollBar::setMaxValue(double value)
    {
        scroll_bar_->setMaxValue(value);
    }

    void ToolHorizontalScrollBar::setColor(booba::Color color)
    {
        scroll_bar_->setTexture(SL::Texture(SL::Color(color.r, color.g, color.b, color.a)));
    }

    booba::Command<float> *ToolHorizontalScrollBar::getCommand()
    {
        return tool_command_;
    }

    void ToolHorizontalScrollBar::setCommand(booba::Command<float> *command)
    {
        tool_command_ = command;
    }

    void ToolHorizontalScrollBar::ToolsetValue(float value)
    {
        tool_command_->Execute(value);
    }
}