#pragma once

#include "GraphLib.hpp"
#include "PluginStandart.hpp"

namespace TOOL_SL
{
    class ToolHorizontalScrollBar : public booba::ScrollBar 
    {
    public:
        ToolHorizontalScrollBar(SL::HorizontalScrollBar *scroll_bar);

        ToolHorizontalScrollBar(const ToolHorizontalScrollBar& source) = default;
        ToolHorizontalScrollBar &operator=(const ToolHorizontalScrollBar& source) = default;
        ~ToolHorizontalScrollBar();

        booba::Vector2d getPosition() const override;
        void setPosition(booba::Vector2d position) override;
        
        booba::Vector2d getShape() const override;
        void setShape(booba::Vector2d shape) override;

        void setColor(booba::Color color) override;
        
        double getValue() override;
        void setValue(double value) override;

        double getMinValue() override;
        void setMinValue(double value) override;

        double getMaxValue() override;
        void setMaxValue(double value) override;
        
        void setCommand(booba::Command<float> *command) override;
        booba::Command<float> *getCommand() override;
        
    private:
        SL::HorizontalScrollBar *scroll_bar_;
        booba::Command<float> *tool_command_ = nullptr; 

        void ToolsetValue(float value);
    };
}