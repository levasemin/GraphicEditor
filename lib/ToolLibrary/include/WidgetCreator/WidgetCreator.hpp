#pragma once
#include "PluginStandart.hpp"
#include "../Widgets/ToolLabel.hpp"
#include "../Widgets/ToolButton.hpp"
#include "../Widgets/ToolEditor.hpp"
#include "../Widgets/ToolHorizontalScrollBar.hpp"
#include "../ToolManager/ToolManager.hpp"

namespace TOOL_SL
{
    class WidgetCreator : public booba::WidgetCreator
    {
    public:
        WidgetCreator(booba::Tool *tool);

        booba::Widget *createWidget(booba::WidgetCreator::Type type, booba::Vector2d shape, booba::Vector2d position);
    
    private:
        booba::Tool * tool_;
    };
} 