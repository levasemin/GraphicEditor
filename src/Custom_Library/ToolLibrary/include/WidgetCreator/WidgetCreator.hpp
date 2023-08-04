#pragma once
#include "PluginStandart.hpp"
#include "../Widgets/ToolLabel.hpp"
#include "../Widgets/ToolButton.hpp"
#include "../Widgets/ToolEditor.hpp"
#include "../Widgets/ToolHorizontalScrollBar.hpp"
#include "../ToolManager/ToolManager.hpp"

namespace TOOL_SL
{
    class WidgetCreator : booba::WidgetCreator
    {
    public:
        WidgetCreator(booba::GUID guid);

        booba::Widget *createWidget(booba::WidgetCreator::Type type, int w, int h, int x, int y);
    
    private:
        booba::GUID guid_;
    };
} 