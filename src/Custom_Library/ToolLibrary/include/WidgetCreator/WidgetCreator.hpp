#pragma once
#include "PluginStandart.hpp"
#include "../Widgets/ToolLabel.hpp"
#include "../Widgets/ToolButton.hpp"
#include "../Widgets/ToolEditor.hpp"
#include "../Widgets/ToolHorizontalScrollBar.hpp"

namespace TOOL_SL
{
    class WidgetCreator : booba::WidgetCreator
    {
    public:
        booba::Widget *createWidget(booba::WidgetCreator::Type type, int w, int h, int x, int y);
    };
}