#pragma once
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "GraphLib.hpp"
#include "PluginStandart.hpp"

namespace TOOL_SL
{
    class ToolLabel : public SL::Label, protected booba::Label
    {
    public:
        ToolLabel(SL::Vector2d shape, SL::Vector2d position);

        ToolLabel(const ToolLabel &source) = default;
        ToolLabel &operator= (const ToolLabel &source) = default;
        ~ToolLabel() = default;

        int getX() override;
        void setX(int x) override;
        
        int getY() override;
        void setY(int y) override;

        int getW() override;
        void setW(int w) override;
        
        int getH() override;
        void setH(int h) override;
        
        void setColor(booba::Color color) override;
            
        void setText(std::string text) override;
    };
}