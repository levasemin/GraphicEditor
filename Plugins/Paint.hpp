#pragma once
#define ELPIDIFOR_HIDDEN_LAYER 

#include <deque>

#include "PluginStandart.hpp"
#include "Interpolator.hpp"
#include "Circle.hpp"
#include "Ring.hpp"

class ToolPaint : public booba::Tool
{
public:

    ToolPaint();

    ToolPaint(const ToolPaint &) = default;
    ToolPaint &operator=(const ToolPaint &) = default;
    ~ToolPaint() = default;
    
    void apply(booba::Image* image, const booba::Event* event) override;

    const char* getTexture() override;

    std::pair<int, int> getShape() override;

private:
    std::string icon_path_ = "Paint.png";

    booba::WidgetCreator *widget_creator_ = nullptr;
    booba::ScrollBar *width_scroll_bar_ = nullptr;
    booba::Editor *width_editor_ = nullptr; 

    std::deque<std::pair<int, int>> points_;

    Circle drawing_object_;
    Ring drawing_object_frame_;
    
    Interpolator interpolator_;

    bool clicked_ = false;

    void set_width(float width);

    void set_width(std::string string);

    void paint(booba::Image *image);

    void recovery_second_layer(booba::Image *second_layer, booba::Image *image);
};