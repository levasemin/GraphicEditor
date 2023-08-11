#include "ToolHorizontalScrollBar.hpp"

namespace TOOL_SL
{
    ToolHorizontalScrollBar::ToolHorizontalScrollBar(SL::Vector2d shape, SL::Vector2d position, float min_value, float max_value): 
        SL::HorizontalScrollBar(shape, position, min_value, max_value)
    {
        SL::HorizontalScrollBar::setScrollCommand(static_cast<SL::Command<float> *> (new SL::SimpleCommand<ToolHorizontalScrollBar, float>(this, &ToolHorizontalScrollBar::ToolsetValue)));    
    }

    ToolHorizontalScrollBar::~ToolHorizontalScrollBar()
    {
        delete SL::HorizontalScrollBar::getScrollCommand();
    }


    int ToolHorizontalScrollBar::getX()
    {
        return SL::HorizontalScrollBar::getPosition().x_;
    }

    void ToolHorizontalScrollBar::setX(int x)
    {
        SL::HorizontalScrollBar::setPosition(SL::Vector2d(static_cast<float>(x), SL::HorizontalScrollBar::getPosition().y_));
    }

    int ToolHorizontalScrollBar::getY()
    {
        return SL::HorizontalScrollBar::getPosition().y_;
    }

    void ToolHorizontalScrollBar::setY(int y)
    {
        SL::HorizontalScrollBar::setPosition(SL::Vector2d(SL::HorizontalScrollBar::getPosition().x_, static_cast<float>(y)));
    }

    int ToolHorizontalScrollBar::getW()
    {
        return SL::HorizontalScrollBar::getShape().x_;
    }

    void ToolHorizontalScrollBar::setW(int w)
    {
        SL::HorizontalScrollBar::setShape(SL::Vector2d(static_cast<float>(w), SL::HorizontalScrollBar::getShape().y_));
    }

    int ToolHorizontalScrollBar::getH()
    {
        return SL::HorizontalScrollBar::getShape().y_;
    }

    void ToolHorizontalScrollBar::setH(int h)
    {
        SL::HorizontalScrollBar::setShape(SL::Vector2d(SL::HorizontalScrollBar::getShape().x_, static_cast<float>(h)));
    }

    double ToolHorizontalScrollBar::getValue()
    {
        return SL::HorizontalScrollBar::getValue();
    }

    void ToolHorizontalScrollBar::setValue(double value)
    {
        SL::HorizontalScrollBar::setValue(value);
    }

    double ToolHorizontalScrollBar::getMinValue()
    {
        return SL::HorizontalScrollBar::getMinValue();
    }

    void ToolHorizontalScrollBar::setMinValue(double value)
    {
        SL::HorizontalScrollBar::setMinValue(value);
    }

    double ToolHorizontalScrollBar::getMaxValue()
    {
        return SL::HorizontalScrollBar::getMaxValue();
    }

    void ToolHorizontalScrollBar::setMaxValue(double value)
    {
        SL::HorizontalScrollBar::setMaxValue(value);
    }

    void ToolHorizontalScrollBar::setColor(booba::Color color)
    {
        SL::HorizontalScrollBar::setTexture(SL::Texture(SL::Color(color.r, color.g, color.b, color.a)));
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