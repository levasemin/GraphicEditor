#include "ToolEyeDropper.h"

void ToolEyeDropper::apply(booba::Image* image, const booba::Event* event)
{
    switch (event->type)
    {
        case booba::EventType::MousePressed:
        {
            clicked_ = true;
            Color color = Color::convert_uint_color(image->getPixel(event->Oleg.mbedata.x, event->Oleg.mbedata.y));
            
            set_color(color);

            break;
        }

        case booba::EventType::MouseMoved:
        {
            if (clicked_)
            {
                Color color = Color::convert_uint_color(image->getPixel(event->Oleg.mbedata.x, event->Oleg.mbedata.y));
            
                set_color(color);
            }

            break;
        }

        case booba::EventType::MouseReleased:
        {
            clicked_ = false;
            break;
        }

        case booba::EventType::CanvasMReleased:
        case booba::EventType::NoEvent:
        case booba::EventType::CanvasMMoved:
        case booba::EventType::CanvasMPressed:
        case booba::EventType::ButtonClicked:
        case booba::EventType::SliderMoved:
        case booba::EventType::CanvasMLeft:
        case booba::EventType::TimerEvent:
    default:
        break;
    }
}

booba::GUID booba::getGUID()
{
    booba::GUID myToolsGUID = {"EYEDROPER-TOOL"};
    
    return myToolsGUID;
}

void booba::init_module()
{
    new ToolEyeDropper;
}