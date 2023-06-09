// #pragma once
#define ELPIDIFOR_HIDDEN_LAYER 

#include "ToolManager.h"
#include "ToolButton.h"
#include "ToolEditor.h"
#include "ToolCanvas.h"
#include "ToolHorizontalScrollBar.h"
#include "ToolPalette.h"
#include "ToolCommand.h"
#include "stdint.h"
#include "GraphLib.h"
#include "Custom_Widgets.h"

booba::GUID booba::getGUID()
{
    booba::GUID myToolsGUID = {"LE-TOOLS"};
    
    return myToolsGUID;
}

uint64_t booba::createButton   (size_t x, size_t y, size_t w, size_t h, const char* text)
{   
    ToolManager &tool_manager = ToolManager::getInstance();

    ToolButton *tool_button = new ToolButton(SL::Vector2d((float)w, (float)h), SL::Vector2d(float(x), float(y)), CUST_SL::Color::BUTTON_LIGHT);
    tool_button->setString(text);
    tool_button->setTextColor(CUST_SL::Color::TEXT);
    tool_button->set_left_click((SL::Command<const booba::Event &> *) new ToolCommand<booba::Tool>(tool_manager.init_tool_, &Tool::apply));
    
    tool_manager.setting_palettes_.back()->add(tool_button);

    return (int64_t)tool_button;
}

uint64_t booba::createEditor(size_t x, size_t y, size_t w, size_t h)
{
    ToolManager &tool_manager = ToolManager::getInstance();

    ToolEditor *tool_editor = new ToolEditor(SL::Vector2d((float)w, (float)h), SL::Vector2d(float(x), float(y)), CUST_SL::Color::EDITOR);
    tool_editor->setTextColor(CUST_SL::Color::TEXT);
    tool_editor->set_editor_command((SL::Command<const booba::Event &> *) new ToolCommand<booba::Tool>(tool_manager.init_tool_, &Tool::apply));
    
    tool_manager.setting_palettes_.back()->add(tool_editor);

    return (int64_t)tool_editor;
}

uint64_t booba::createLabel    (size_t x, size_t y, size_t w, size_t h, const char* text)
{
    ToolManager &tool_manager = ToolManager::getInstance();

    SL::Label *label = new SL::Label(SL::Vector2d(float(w), float(h)), SL::Vector2d(float(x), float(y)), CUST_SL::Color(uint8_t(48),  uint8_t(48),  uint8_t(48)));
    label->setTextColor(CUST_SL::Color::TEXT);
    label->setString(text);

    tool_manager.setting_palettes_.back()->add(label);

    return (int64_t)label;
}   

uint64_t booba::createSlider(size_t x, size_t y, size_t w, size_t h, int64_t minValue, int64_t maxValue, int64_t startValue)
{
    ToolManager &tool_manager = ToolManager::getInstance();

    ToolHorizontalScrollBar *scroll_bar = new ToolHorizontalScrollBar(SL::Vector2d(float(w), float(h)), SL::Vector2d(float(x), float(y)), minValue, maxValue);

    scroll_bar->set_scroll_command((SL::Command <const booba::Event &> *) new ToolCommand<booba::Tool>(tool_manager.init_tool_, &Tool::apply));

    tool_manager.setting_palettes_.back()->add(scroll_bar);

    return (int64_t)scroll_bar;     
}

uint64_t booba::createCanvas(size_t x, size_t y, size_t w, size_t h)
{
    ToolManager &tool_manager = ToolManager::getInstance();
    
    SL::Image image = SL::Image(SL::Vector2d(float(w), float(h)));
    ToolCanvas(SL::Vector2d(float(w), float(h)), SL::Vector2d(float(x), float(y)), image);
    ToolCanvas *tool_canvas = new ToolCanvas(SL::Vector2d(float(w), float(h)), SL::Vector2d(float(x), float(y)), image);
    tool_canvas->set_command((SL::Command<const booba::Event &> *) new ToolCommand<booba::Tool>(tool_manager.init_tool_, &Tool::apply));
    tool_manager.setting_palettes_.back()->add(tool_canvas);

    return (int64_t)tool_canvas;
}

void booba::setValueSlider(uint64_t slider, int64_t value)
{
    ((ToolHorizontalScrollBar*)slider)->scroll_bar(float(value));
}

void booba::setTextEditor(uint64_t editorId, const char *text)
{
    ((ToolEditor *)editorId)->setString(text);
}

char *booba::getTextEditor(uint64_t editorId)
{
    std::string *text = new std::string(((ToolEditor *)editorId)->getString());
    return (char *)text->c_str();
}

void booba::setTextLabel(uint64_t labelId, const char *text)
{
    ((SL::Label *)labelId)->setString(text);
    SL::Application::get_current()->show(nullptr);
}

char *booba::getTextLabel(uint64_t labelId)
{
    std::string *text = new std::string(((SL::Label *)labelId)->getString());
    return (char *)text->c_str();
}

void booba::putPixel (uint64_t canvas, size_t x, size_t y, booba::Color color)
{
    if (canvas) 
    {
        ToolCanvas *tool_canvas = (ToolCanvas *)canvas;
        tool_canvas->image_.setPixel(x, y, color);
    }
}


void booba::putSprite(uint64_t canvas, size_t x, size_t y, size_t w, size_t h, const char* texture)
{
    if (canvas)
    {
        ToolCanvas *tool_canvas = (ToolCanvas *)canvas;
        tool_canvas->image_.loadFromFile(texture);
    }
}

void booba::cleanCanvas(uint64_t canvasId, booba::Color color)
{

}


void booba::addTool(booba::Tool* tool)
{
    ToolManager &tool_manager = ToolManager::getInstance();
    tool_manager.add(tool);  
}

void booba::addFilter(booba::Tool* tool)
{

}

void* booba::getLibSymbol(GUID guid, const char* name) 
{
    void* handler = nullptr;

    if ((handler = ToolManager::getInstance().get_guid_handler(guid)) == nullptr) {
        return nullptr;
    }

    return dlsym(handler, name);
}


bool booba::setToolBarSize(size_t w, size_t h)
{
    return true;
}