#pragma once

#include <memory>
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wswitch-enum"

#pragma once

#include <filesystem>
#include <dlfcn.h>
#include <vector>

#include "../Graphic-Library/GraphLib/GraphLib.h"


#include "Surface.h"
#include "../Tool/ToolManager.h"
#include "../Tool/ToolPalette.h"

#include "Image.h"
#include "Color.h"


class Canvas : public SL::CompositeObject
{
    Canvas() : SL::CompositeObject(SL::Vector2d(0, 0), SL::Vector2d(0, 0)), tool_manager_(ToolManager::getInstance()) {}
    Canvas (const Canvas &source) = delete;

    Canvas &operator= (const Canvas &source) = delete;

public:
    Surface *surface_        = nullptr;    
    Surface *second_surface_ = nullptr;

    ToolManager &tool_manager_;

    bool is_left_clicked_ = false;
    bool is_right_clicked_ = false;

    float zoom_ = 1;


    static Canvas *getInstance()
    {
        static Canvas canvas;
        return &canvas;
    }

    static Canvas *Create(SL::Vector2d shape, SL::Vector2d position, ToolPalette *tool_palette = nullptr, SL::Container * setting_palette = nullptr);

    void MoveMouseEvent (const SL::Event &event) override;

    void ClickLeftEvent(const SL::Event &event) override;

    void ClickRightEvent(const SL::Event &event) override;
    
    void ReleasedLeftEvent (const SL::Event &event) override;

    void ReleasedRightEvent (const SL::Event &event) override;

    void PressKeyEvent(const SL::Event &event) override;

    void set_zoom(float value);

    void set_image(const std::string &path_image);

    void set_image(const Image &new_image);

    Image *get_image();
    
    void add_tool(Tool *new_tool);

    Surface *get_surface();
};