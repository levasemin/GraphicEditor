#include "WidgetCreator.hpp"

namespace TOOL_SL
{
    WidgetCreator::WidgetCreator(booba::GUID guid):
        guid_(guid)
    {}


    booba::Widget *WidgetCreator::createWidget(booba::WidgetCreator::Type type, int w, int h, int x, int y)
    {
        SL::Container *settings_container = ToolManager::getInstance().getSettingsContainer(guid_);
        
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
                return (booba::Widget *)button;
            }
            case booba::WidgetCreator::Type::EDITOR:
            {
                auto editor = new ToolEditor(SL::Vector2d(w, h), SL::Vector2d(x, y));
                return (booba::Widget *)editor;
            }
            case booba::WidgetCreator::Type::SCROLLBAR:
            {
                auto scrollbar = new ToolHorizontalScrollBar(SL::Vector2d(w, h), SL::Vector2d(x, y), 0, 1);
                return (booba::Widget *)scrollbar;
            }

            default:
                return nullptr;
        }
    }   
}

extern "C" void* getWidgetCreator(booba::GUID guid)
{
    std::cout << "WidgetCreator is created\n";
    return new TOOL_SL::WidgetCreator(guid);
}