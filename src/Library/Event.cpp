#include "Event.h"

booba::Event convert_event(const Event &event)
{
    booba::Event booba_event;
    
    switch(event.type_)
    {
        case EventType::NoEvent:
        case EventType::MouseMoved:
        {
            booba_event.type = booba::EventType::MouseMoved;
            booba_event.Oleg.motion.x = (int)event.Oleg_.motion.pos.x_;
            booba_event.Oleg.motion.y = (int)event.Oleg_.motion.pos.y_;

            break;
        }

        case EventType::MousePressed:
        {
            booba_event.type = booba::EventType::MousePressed;
            booba_event.Oleg.mbedata.x = (int)event.Oleg_.mbedata.pos.x_;
            booba_event.Oleg.mbedata.y = (int)event.Oleg_.mbedata.pos.y_;
            
            booba_event.Oleg.mbedata.button = event.Oleg_.mbedata.button == MouseButton::Left ? booba::MouseButton::Left : booba::MouseButton::Right;
            booba_event.Oleg.mbedata.alt    = event.Oleg_.mbedata.alt;
            booba_event.Oleg.mbedata.ctrl   = event.Oleg_.mbedata.ctrl;
            booba_event.Oleg.mbedata.shift  = event.Oleg_.mbedata.shift;

            break;
        }

        case EventType::MouseReleased:
        {
            booba_event.type = booba::EventType::MouseReleased;
            booba_event.Oleg.mbedata.x = (int)event.Oleg_.mredata.pos.x_;
            booba_event.Oleg.mbedata.y = (int)event.Oleg_.mredata.pos.y_;
            
            booba_event.Oleg.mbedata.button = (booba::MouseButton)event.Oleg_.mredata.button;

            break;
        }

        case EventType::ButtonClicked:
        {
            booba_event.type = booba::EventType::ButtonClicked;
            booba_event.Oleg.bcedata.id = event.Oleg_.bcedata.id;
            
            break;
        }

        case EventType::ScrollbarMoved:
        {
            booba_event.type = booba::EventType::SliderMoved;
            booba_event.Oleg.smedata.id = event.Oleg_.smedata.id;
            booba_event.Oleg.smedata.value = int(event.Oleg_.smedata.value);

            break;
        }

        case EventType::CanvasMPressed:
        {
            booba_event.type = booba::EventType::CanvasMPressed;
            booba_event.Oleg.cedata.id = event.Oleg_.cedata.id;
            booba_event.Oleg.cedata.x = (uint32_t)event.Oleg_.cedata.pos.x_;
            booba_event.Oleg.cedata.y = (uint32_t)event.Oleg_.cedata.pos.y_;
            
            break;
        }

        case EventType::CanvasMReleased:
        {
            booba_event.type = booba::EventType::CanvasMReleased;
            booba_event.Oleg.cedata.id = event.Oleg_.cedata.id;
            booba_event.Oleg.cedata.x = (uint32_t)event.Oleg_.cedata.pos.x_;
            booba_event.Oleg.cedata.y = (uint32_t)event.Oleg_.cedata.pos.y_;
                        
            break;
        }

        case EventType::CanvasMMoved:
        {
            booba_event.type = booba::EventType::CanvasMMoved;
            booba_event.Oleg.cedata.id = event.Oleg_.cedata.id;
            booba_event.Oleg.cedata.x = (uint32_t)event.Oleg_.cedata.pos.x_;
            booba_event.Oleg.cedata.y = (uint32_t)event.Oleg_.cedata.pos.y_;
            break;
        }

        case EventType::CanvasMleft:
        {
            booba_event.type = booba::EventType::CanvasMLeft;
            booba_event.Oleg.cedata.id = event.Oleg_.cedata.id;
            booba_event.Oleg.cedata.x = (uint32_t)event.Oleg_.cedata.pos.x_;
            booba_event.Oleg.cedata.y = (uint32_t)event.Oleg_.cedata.pos.y_;
            break;
        }

        case EventType::TimerEvent:
        {
            booba_event.type = booba::EventType::TimerEvent;
            booba_event.Oleg.tedata.time = event.Oleg_.tedata.time;
            break;
        }

        case EventType::KeyPressed:
        case EventType::Closed:

        default:
        {
            break;
        }
    }

    return booba_event;
}