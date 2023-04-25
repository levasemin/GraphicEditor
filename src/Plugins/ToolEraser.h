#pragma once
#define ELPIDIFOR_HIDDEN_LAYER 

#include <deque>

#include "../Graphic-Library/GraphLib/GraphLib.h"
#include "../Tool/Widgets/ToolEditor.h"
#include "../Tool/Widgets/ToolHorizontalScrollBar.h"
#include "optionals.h"
#include "../Tool/Tool.h"
#include "../Tool/ToolCommand.h"
#include "../Tool/ToolManager.h"

#include "Circle.h"
#include "Interpolator.h"

class ToolEraser : public Tool
{
public:
    Interpolator interpolator_;

    bool clicked_ = false;

    ToolEraser() : Tool(),
        interpolator_(Interpolator::CATMULL_ROM),
        points_({}),
        drawing_object_(1.f)
    {
        drawing_object_.set_color(Color::convert_uint_color(Color::convert_color_uint(Color::White)));

        char icon_path[128] = "source/Eraser.png";
        std::memcpy(icon_path_, icon_path, 128);
        booba::addTool(this);
    }

    ToolEraser(const ToolEraser &) = default;
    ToolEraser &operator=(const ToolEraser &) = default;
    
    void set_width_editor(const booba::Event &event)
    {
        std::string string = event.Oleg.textdata.text;
        
        if (string.size() == 0)
        {
            booba::setValueSlider(width_scroll_bar_, 0);
            return ;
        }

        if ('0' > string[string.size() - 1] || string[string.size() - 1] > '9')
        {
            string.resize(string.size() - 1);
            booba::setTextEditor(width_editor_, string.c_str());
            
            return;
        }

        float width = string.size() > 0 ? float(std::stoi(string)) : 0;
        width = width <= 30 ? width : 30;

        Event new_event;
        new_event.type_ = EventType::ScrollbarMoved;
        new_event.Oleg_.smedata.value = width / 30;
        new_event.Oleg_.smedata.id = (uint64_t)&width_scroll_bar_;
        
        booba::setValueSlider(width_scroll_bar_, width / 30);

        drawing_object_.set_radius(int(width / 2) == 0 ? 1 : int(width / 2));
    }

    void set_width(const booba::Event & event)
    {
        int width = int(event.Oleg.smedata.value);
        
        if (width != 0)
        {
            booba::setTextEditor(width_editor_, std::to_string(width).c_str());
        }
        
        drawing_object_.set_radius(width / 2 == 0 ? 1 : width / 2);
    }

    void paint(booba::Image *image)
    {
        drawing_object_.draw_fill(image, points_.back());

        if (points_.size() == 4)
        {
            for (float t = 0; t <= 1.f; t += 0.1f)
            {
                Vector2d new_point = interpolator_(t, points_[0], points_[1], points_[2], points_[3]);
                
                drawing_object_.draw_fill(image, new_point);
            }
        }
    }

    void apply(booba::Image* image, const booba::Event* event) override
    {    
        if (image == nullptr && event == nullptr)
        {
            return;
        }

        switch (event->type)
        {
            case booba::EventType::MousePressed:
            {
                clicked_ = true;

                Vector2d new_point((float)event->Oleg.mbedata.x, (float)event->Oleg.mbedata.y);

                points_.push_back(new_point);
                paint(image);
                points_.pop_back();

                break;
            }

            case booba::EventType::MouseReleased:
            {
                clicked_ = false;
                break;
            }

            case booba::EventType::MouseMoved:
            {
                booba::Image *second_layer = booba::getHiddenLayerID();

                Vector2d new_point((float)event->Oleg.motion.x, (float)event->Oleg.motion.y);

                if (clicked_)
                {
                    if (points_.size() > 0)
                    {
                        if (abs(points_.back().x_ - new_point.x_) > 10 || abs(points_.back().y_ - new_point.y_) > 10)
                        {
                            points_.clear();
                        }
                    }

                    points_.push_back(new_point);
                    
                    if (points_.size() > 4)
                    {
                        points_.pop_front();
                    }

                    paint(image);
                }
                
                ToolManager::getInstance().recovery_second_layer();
                
                float border_width = float(drawing_object_.get_radius() / 3 != 0 ? drawing_object_.get_radius() / 3 : 1); 
                drawing_object_.draw_frame(second_layer, new_point, border_width);

                break;
            }

            case booba::EventType::SliderMoved:
            {
                set_width(*event);

                break;
            }
            case booba::EventType::TextEvent:
            {
                set_width_editor(*event);
                break;
            }

            case booba::EventType::ButtonClicked:
            case booba::EventType::NoEvent:
            case booba::EventType::CanvasMMoved:
            case booba::EventType::CanvasMPressed:
            case booba::EventType::CanvasMReleased:
            
            default:
                break;
        }
    }

    void recovery_second_layer(booba::Image *second_layer, booba::Image *image)
    {
        for (int y = 0; y < int(image->getH()); y++)
        {
            for (int x = 0; x < int(image->getW()); x++)
            {
                second_layer->setPixel(x, y, image->getPixel(x, y));
            }
        }
    }

    const char* getTexture() override
    {
        return icon_path_;
    } 

    void buildSetupWidget() override
    {
        width_editor_     = booba::createEditor(245, 15, 50, 30);
        width_scroll_bar_ = booba::createSlider(20, 20, 200, 20, 0, 30, 0);
    }

private:
    int64_t width_scroll_bar_ = 0;
    int64_t width_editor_     = 0; 
    std::deque<Vector2d> points_;

    Circle drawing_object_;
};