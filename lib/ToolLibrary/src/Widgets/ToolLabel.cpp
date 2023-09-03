#include "ToolLabel.hpp"
#include "../Event/Event.hpp"

namespace TOOL_SL
{
    ToolLabel::ToolLabel(SL::Label *label) : 
        label_(label)
    {
    }

    booba::Vector2d ToolLabel::getPosition() const
    {
        return booba::Vector2d(label_->getPosition().x_, label_->getPosition().y_);
    }

    void ToolLabel::setPosition(booba::Vector2d position)
    {
        label_->setPosition(SL::Vector2d(position.x_, position.y_));
    }

    booba::Vector2d ToolLabel::getShape() const
    {
        return booba::Vector2d(label_->getShape().x_, label_->getShape().y_);
    }

    void ToolLabel::setShape(booba::Vector2d shape)
    {
        label_->setShape(SL::Vector2d(shape.x_, shape.y_));
    }

    void ToolLabel::setColor(booba::Color color)
    {
        label_->setTexture(SL::Texture(SL::Color(color.r, color.g, color.b, color.a)));
    }

    void ToolLabel::setText(std::string text)
    {
        label_->setText(text);
    }
}