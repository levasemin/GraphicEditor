#include "WidgetCreator.hpp"

namespace TOOL_SL
{
    WidgetCreator::WidgetCreator(booba::Tool *tool):
        tool_(tool)
    {
        SL::Container *settings_container = new SL::Container(SL::Vector2d(tool->getShape().x_, tool->getShape().y_), SL::Vector2d(0, 0), SL::Texture(SL::Color::Grey));
        ToolManager::getInstance().addSettingsContainer(tool, settings_container);
    }


    booba::Widget *WidgetCreator::createWidget(booba::WidgetCreator::Type type, booba::Vector2d shape, booba::Vector2d position)
    {
        SL::Container *settings_container = ToolManager::getInstance().getSettingsContainer(tool_);
        
        switch(type)
        {
            case booba::WidgetCreator::Type::LABEL:
            {
                auto label = new SL::Label(SL::Vector2d(shape.x_, shape.y_), SL::Vector2d(position.x_, position.y_));
                settings_container->add(label);
                auto tool_label = new TOOL_SL::ToolLabel(label);
                return dynamic_cast<booba::Widget *>(tool_label);
            }
            
            case booba::WidgetCreator::Type::BUTTON:
            {
                auto button = new SL::Button(SL::Vector2d(shape.x_, shape.y_), SL::Vector2d(position.x_, position.y_));
                settings_container->add(button);
                auto tool_button = new TOOL_SL::ToolLabel(button);
                return dynamic_cast<booba::Widget *>(tool_button);
            }
            case booba::WidgetCreator::Type::EDITOR:
            {
                auto editor = new SL::Editor(SL::Vector2d(shape.x_, shape.y_), SL::Vector2d(position.x_, position.y_));
                settings_container->add(editor);
                auto tool_editor = new TOOL_SL::ToolEditor(editor);
                return dynamic_cast<booba::Widget *>(tool_editor);
            }
            case booba::WidgetCreator::Type::SCROLLBAR:
            {
                auto scroll_bar = new SL::HorizontalScrollBar(SL::Vector2d(shape.x_, shape.y_), SL::Vector2d(position.x_, position.y_), 0, 1);
                settings_container->add(scroll_bar);
                auto tool_scroll_bar = new ToolHorizontalScrollBar(scroll_bar);
                return dynamic_cast<booba::Widget *>(tool_scroll_bar);
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