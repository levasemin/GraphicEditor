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


using namespace SL;

class Canvas : public CompositeObject
{
public:
    Surface *surface_ = nullptr;    
    Surface *second_surface_ = nullptr;

    ToolManager &tool_manager_;

    bool is_left_clicked_ = false;
    bool is_right_clicked_ = false;

    float zoom_ = 1;

    Canvas(Vector2d shape, Vector2d position, ToolPalette *tool_palette = nullptr, Container * setting_palette = nullptr);
    
    Canvas (const Canvas &source);

    Canvas &operator= (const Canvas &source);

    void MoveMouseEvent (const Event &event) override;

    void ClickLeftEvent(const Event &event) override;

    void ClickRightEvent(const Event &event) override;
    
    void ReleasedLeftEvent (const Event &event) override;

    void ReleasedRightEvent (const Event &event) override;

    void PressKeyEvent(const Event &event) override;

    void set_zoom(float value);

    void set_image(const std::string &path_image);

    void set_image(const Image &new_image);

    Image *get_image();
    
    void add_tool(Tool *new_tool);
};