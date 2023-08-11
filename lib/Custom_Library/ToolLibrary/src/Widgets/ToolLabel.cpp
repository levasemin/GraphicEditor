#include "ToolLabel.hpp"
#include "../Event/Event.hpp"

namespace TOOL_SL
{
    ToolLabel::ToolLabel(SL::Vector2d shape, SL::Vector2d position) : 
        SL::Label(shape, position)
    {
    }

    int ToolLabel::getX()
    {
        return SL::Label::getPosition().x_;
    }

    void ToolLabel::setX(int x)
    {
        SL::Label::setPosition(SL::Vector2d(static_cast<float>(x), SL::Label::getPosition().y_));
    }

    int ToolLabel::getY()
    {
        return SL::Label::getPosition().y_;
    }

    void ToolLabel::setY(int y)
    {
        SL::Label::setPosition(SL::Vector2d(SL::Label::getPosition().x_, static_cast<float>(y)));
    }

    int ToolLabel::getW()
    {
        return SL::Label::getShape().x_;
    }

    void ToolLabel::setW(int w)
    {
        SL::Label::setShape(SL::Vector2d(static_cast<float>(w), SL::Label::getShape().y_));
    }

    int ToolLabel::getH()
    {
        return SL::Label::getShape().y_;
    }

    void ToolLabel::setH(int h)
    {
        SL::Label::setShape(SL::Vector2d(SL::Label::getShape().x_, static_cast<float>(h)));
    }

    void ToolLabel::setColor(booba::Color color)
    {
        SL::Label::setTexture(SL::Texture(SL::Color(color.r, color.g, color.b, color.a)));
    }

    void ToolLabel::setText(std::string text)
    {
        SL::Label::setText(text);
    }
}