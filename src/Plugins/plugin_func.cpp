// #pragma once
#define ELPIDIFOR_HIDDEN_LAYER 

#include "../Tool/ToolManager.h"
#include "../Tool/Widgets/ToolButton.h"
#include "../Tool/Widgets/ToolEditor.h"
#include "../Tool/Widgets/ToolCanvas.h"
#include "../Tool/Widgets/ToolHorizontalScrollBar.h"
#include "../Tool/ToolPalette.h"
#include "../Custom_Widgets/Canvas.h"
#include "stdint.h"
#include "../Graphic-Library/GraphLib/GraphLib.h"

#include "optionals.h"

booba::GUID booba::getGUID()
{
    booba::GUID myToolsGUID = {"LE-TOOLS"};
    
    return myToolsGUID;
}

uint64_t booba::createButton   (size_t x, size_t y, size_t w, size_t h, const char* text)
{   
    ToolManager &tool_manager = ToolManager::getInstance();

    ToolButton *tool_button = new ToolButton(Vector2d((float)w, (float)h), Vector2d(float(x), float(y)), Texture(tool_manager.init_tool_->getTexture()));

    tool_button->set_left_click((Command<const booba::Event &> *) new ToolCommand<booba::Tool>(tool_manager.init_tool_, &Tool::apply));
    
    tool_manager.setting_palettes_.back()->add(tool_button);

    return (int64_t)tool_button;
}

uint64_t booba::createEditor(size_t x, size_t y, size_t w, size_t h)
{
    ToolManager &tool_manager = ToolManager::getInstance();

    ToolEditor *tool_editor = new ToolEditor(Vector2d((float)w, (float)h), Vector2d(float(x), float(y)));

    tool_editor->set_editor_command((Command<const booba::Event &> *) new ToolCommand<booba::Tool>(tool_manager.init_tool_, &Tool::apply));
    
    tool_manager.setting_palettes_.back()->add(tool_editor);

    return (int64_t)tool_editor;
}

uint64_t booba::createLabel    (size_t x, size_t y, size_t w, size_t h, const char* text)
{
    ToolManager &tool_manager = ToolManager::getInstance();

    Label *label = new Label(Vector2d(float(w), float(h)), Vector2d(float(x), float(y)));
    label->setString(text);

    tool_manager.setting_palettes_.back()->add(label);

    return (int64_t)label;
}   

uint64_t booba::createSlider(size_t x, size_t y, size_t w, size_t h, int64_t minValue, int64_t maxValue, int64_t startValue)
{
    ToolManager &tool_manager = ToolManager::getInstance();

    ToolHorizontalScrollBar *scroll_bar = new ToolHorizontalScrollBar(Vector2d(float(w), float(h)), Vector2d(float(x), float(y)), minValue, maxValue);

    scroll_bar->set_scroll_command((Command <const booba::Event &> *) new ToolCommand<booba::Tool>(tool_manager.init_tool_, &Tool::apply));

    tool_manager.setting_palettes_.back()->add(scroll_bar);

    return (int64_t)scroll_bar;     
}

uint64_t booba::createCanvas(size_t x, size_t y, size_t w, size_t h)
{
    ToolManager &tool_manager = ToolManager::getInstance();
    
    SL::Image image = SL::Image(Vector2d(float(w), float(h)));
    ToolCanvas(Vector2d(float(w), float(h)), Vector2d(float(x), float(y)), image);
    ToolCanvas *tool_canvas = new ToolCanvas(Vector2d(float(w), float(h)), Vector2d(float(x), float(y)), image);
    tool_canvas->set_command((Command <const booba::Event &> *) new ToolCommand<booba::Tool>(tool_manager.init_tool_, &Tool::apply));
    tool_manager.setting_palettes_.back()->add(tool_canvas);

    return (int64_t)tool_canvas;
}

void booba::setValueSlider(uint64_t slider, int64_t value)
{
    ((ToolHorizontalScrollBar*)slider)->scroll_bar(value);
}

void booba::setTextEditor(uint64_t editorId, const char *text)
{
    ((ToolEditor *)editorId)->setString(text);
}

void booba::putPixel (uint64_t canvas, size_t x, size_t y, uint32_t color)
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

void booba::cleanCanvas(uint64_t canvasId, uint32_t color)
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

booba::Image *booba::getHiddenLayerID()
{
    return ToolManager::getInstance().get_second_layer()->get_image();
}