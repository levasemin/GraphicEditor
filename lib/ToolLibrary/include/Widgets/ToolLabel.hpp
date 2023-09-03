#pragma once
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "GraphLib.hpp"
#include "PluginStandart.hpp"

namespace TOOL_SL
{
    class ToolLabel : public booba::Label
    {
    public:
        ToolLabel(SL::Label *label);

        ToolLabel(const ToolLabel &source) = default;
        ToolLabel &operator= (const ToolLabel &source) = default;
        ~ToolLabel() = default;

        booba::Vector2d getPosition() const override;
        void setPosition(booba::Vector2d position) override;
        
        booba::Vector2d getShape() const override;
        void setShape(booba::Vector2d shape) override;

        void setColor(booba::Color color) override;
            
        void setText(std::string text) override;
    
    private:
        SL::Label *label_;
    };
}