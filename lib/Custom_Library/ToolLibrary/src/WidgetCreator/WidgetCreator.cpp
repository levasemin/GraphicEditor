#include "WidgetCreator.hpp"

namespace TOOL_SL
{
    WidgetCreator::WidgetCreator(booba::Tool *tool):
        tool_(tool)
    {
        SL::Container *settings_container = new SL::Container(SL::Vector2d(tool->getShape().first, tool->getShape().second), SL::Vector2d(0, 0), SL::Texture(SL::Color::Grey));
        ToolManager::getInstance().addSettingsContainer(tool, settings_container);
    }


    booba::Widget *WidgetCreator::createWidget(booba::WidgetCreator::Type type, int w, int h, int x, int y)
    {
        SL::Container *settings_container = ToolManager::getInstance().getSettingsContainer(tool_);
        
        switch(type)
        {
            case booba::WidgetCreator::Type::LABEL:
            {
                auto label = new ToolLabel(SL::Vector2d(w, h), SL::Vector2d(x, y));
                settings_container->add(label);
                return (booba::Widget *)label;
            }
            
            case booba::WidgetCreator::Type::BUTTON:
            {
                auto button = new ToolButton(SL::Vector2d(w, h), SL::Vector2d(x, y));
                settings_container->add(button);
                return (booba::Widget *)button;
            }
            case booba::WidgetCreator::Type::EDITOR:
            {
                auto editor = new ToolEditor(SL::Vector2d(w, h), SL::Vector2d(x, y));
                settings_container->add(editor);
                return (booba::Widget *)editor;
            }
            case booba::WidgetCreator::Type::SCROLLBAR:
            {
                auto scrollbar = new ToolHorizontalScrollBar(SL::Vector2d(w, h), SL::Vector2d(x, y), 0, 1);
                settings_container->add(scrollbar);
                return (booba::Widget *)scrollbar;
            }

            default:
                return nullptr;
        }
    }   
}

extern "C" booba::WidgetCreator* getWidgetCreator(booba::Tool *tool)
{
    return dynamic_cast<booba::WidgetCreator *>(new TOOL_SL::WidgetCreator(tool));
}