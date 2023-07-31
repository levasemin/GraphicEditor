#include "WidgetCreator.hpp"

namespace TOOL_SL
{
    booba::Widget *WidgetCreator::createWidget(booba::WidgetCreator::Type type, int w, int h, int x, int y)
    {
        switch(type)
        {
            case booba::WidgetCreator::Type::LABEL:
            {
                return (booba::Widget *)new ToolLabel(SL::Vector2d(w, h), SL::Vector2d(x, y));
            }
            case booba::WidgetCreator::Type::BUTTON:
            {
                return (booba::Widget *)new ToolButton(SL::Vector2d(w, h), SL::Vector2d(x, y));
            }
            case booba::WidgetCreator::Type::EDITOR:
            {
                return (booba::Widget *)new ToolEditor(SL::Vector2d(w, h), SL::Vector2d(x, y));
            }
            case booba::WidgetCreator::Type::SCROLLBAR:
            {
                return (booba::Widget *)new ToolHorizontalScrollBar(SL::Vector2d(w, h), SL::Vector2d(x, y), 0, 1);
            }

            default:
                return nullptr;
        }
    }
}