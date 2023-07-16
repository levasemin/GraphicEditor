#include "Event.hpp"

booba::Event convert_event(const SL::Event &event)
{
    booba::Event booba_event;
    
    switch(event.type_)
    {
        case SL::EventType::NoEvent:
        case SL::EventType::MouseMoved:
        {
            booba_event.type = booba::EventType::MouseMoved;
            booba_event.Oleg.motion.x = (int)event.Oleg_.motion.pos.x_;
            booba_event.Oleg.motion.y = (int)event.Oleg_.motion.pos.y_;

            break;
        }

        case SL::EventType::MousePressed:
        {
            booba_event.type = booba::EventType::MousePressed;
            booba_event.Oleg.mbedata.x = (int)event.Oleg_.mbedata.pos.x_;
            booba_event.Oleg.mbedata.y = (int)event.Oleg_.mbedata.pos.y_;
            
            booba_event.Oleg.mbedata.button = event.Oleg_.mbedata.button == SL::MouseButton::Left ? booba::MouseButton::Left : booba::MouseButton::Right;
            booba_event.Oleg.mbedata.alt    = event.Oleg_.mbedata.alt;
            booba_event.Oleg.mbedata.ctrl   = event.Oleg_.mbedata.ctrl;
            booba_event.Oleg.mbedata.shift  = event.Oleg_.mbedata.shift;

            break;
        }

        case SL::EventType::MouseReleased:
        {
            booba_event.type = booba::EventType::MouseReleased;
            booba_event.Oleg.mbedata.x = (int)event.Oleg_.mredata.pos.x_;
            booba_event.Oleg.mbedata.y = (int)event.Oleg_.mredata.pos.y_;
            
            booba_event.Oleg.mbedata.button = (booba::MouseButton)event.Oleg_.mredata.button;

            break;
        }

        case SL::EventType::ButtonClicked:
        {
            booba_event.type = booba::EventType::ButtonClicked;
            booba_event.Oleg.bcedata.id = event.Oleg_.bcedata.id;
            
            break;
        }

        case SL::EventType::ScrollbarMoved:
        {
            booba_event.type = booba::EventType::SliderMoved;
            booba_event.Oleg.smedata.id = event.Oleg_.smedata.id;
            booba_event.Oleg.smedata.value = int(event.Oleg_.smedata.value);

            break;
        }
        
        case SL::EventType::TextEvent:
        {
            booba_event.type = booba::EventType::TextEvent;
            booba_event.Oleg.textdata.id = event.Oleg_.textedata.id;
            booba_event.Oleg.textdata.text = event.Oleg_.textedata.text;
            
            break;
        }

        case SL::EventType::CanvasMPressed:
        {
            booba_event.type = booba::EventType::CanvasMPressed;
            booba_event.Oleg.cedata.id = event.Oleg_.cedata.id;
            booba_event.Oleg.cedata.x = (uint32_t)event.Oleg_.cedata.pos.x_;
            booba_event.Oleg.cedata.y = (uint32_t)event.Oleg_.cedata.pos.y_;
            
            break;
        }

        case SL::EventType::CanvasMReleased:
        {
            booba_event.type = booba::EventType::CanvasMReleased;
            booba_event.Oleg.cedata.id = event.Oleg_.cedata.id;
            booba_event.Oleg.cedata.x = (uint32_t)event.Oleg_.cedata.pos.x_;
            booba_event.Oleg.cedata.y = (uint32_t)event.Oleg_.cedata.pos.y_;
                        
            break;
        }

        case SL::EventType::CanvasMMoved:
        {
            booba_event.type = booba::EventType::CanvasMMoved;
            booba_event.Oleg.cedata.id = event.Oleg_.cedata.id;
            booba_event.Oleg.cedata.x = (uint32_t)event.Oleg_.cedata.pos.x_;
            booba_event.Oleg.cedata.y = (uint32_t)event.Oleg_.cedata.pos.y_;
            break;
        }

        case SL::EventType::TimerEvent:
        {
            booba_event.type = booba::EventType::TimerEvent;
            booba_event.Oleg.tedata.time = event.Oleg_.tedata.time;
            break;
        }

        case SL::EventType::KeyPressed:
        case SL::EventType::Closed:

        default:
        {
            break;
        }
    }

    return booba_event;
}