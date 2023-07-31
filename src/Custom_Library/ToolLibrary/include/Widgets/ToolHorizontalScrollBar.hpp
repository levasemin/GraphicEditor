#pragma once

#include "GraphLib.hpp"
#include "PluginStandart.hpp"

namespace TOOL_SL
{
    class ToolHorizontalScrollBar : public booba::ScrollBar,  private SL::HorizontalScrollBar
    {
    public:
        ToolHorizontalScrollBar(SL::Vector2d shape, SL::Vector2d position, float min_value, float max_value);

        ToolHorizontalScrollBar(const ToolHorizontalScrollBar& source) = default;
        ToolHorizontalScrollBar &operator=(const ToolHorizontalScrollBar& source) = default;
        ~ToolHorizontalScrollBar();

        int getX() override;
        void setX(int x) override;
            
        int getY() override;
        void setY(int y) override;

        int getW() override;
        void setW(int w) override;
            
        int getH() override;
        void setH(int h) override;

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
        booba::Command<float> *tool_command_ = nullptr; 

        void ToolsetValue(float value);
    };
}