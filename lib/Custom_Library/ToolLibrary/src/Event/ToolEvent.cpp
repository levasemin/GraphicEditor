#include "ToolEvent.hpp"

namespace TOOL_SL
{
    booba::Event convert_event(const SL::Event &event)
    {
        booba::Event booba_event;
        
        switch(event.type_)
        {
            case SL::EventType::NoEvent:
            case SL::EventType::MouseMoved:
            {
                booba_event.type = booba::EventType::MouseMoved;
                booba_event.Oleg.motion.x = (int)event.Oleg_.metion.pos.x_;
                booba_event.Oleg.motion.y = (int)event.Oleg_.metion.pos.y_;

                break;
            }

            case SL::EventType::MousePressed:
            {
                booba_event.type = booba::EventType::MousePressed;
                booba_event.Oleg.mpedata.x = (int)event.Oleg_.mpedata.pos.x_;
                booba_event.Oleg.mpedata.y = (int)event.Oleg_.mpedata.pos.y_;
                
                booba_event.Oleg.mpedata.button = event.Oleg_.mpedata.button == SL::MouseButton::Left ? booba::MouseButton::Left : booba::MouseButton::Right;
                booba_event.Oleg.mpedata.alt    = event.Oleg_.mpedata.alt;
                booba_event.Oleg.mpedata.ctrl   = event.Oleg_.mpedata.ctrl;
                booba_event.Oleg.mpedata.shift  = event.Oleg_.mpedata.shift;

                break;
            }

            case SL::EventType::MouseReleased:
            {
                booba_event.type = booba::EventType::MouseReleased;
                booba_event.Oleg.mpedata.x = (int)event.Oleg_.mredata.pos.x_;
                booba_event.Oleg.mpedata.y = (int)event.Oleg_.mredata.pos.y_;
                
                booba_event.Oleg.mpedata.button = (booba::MouseButton)event.Oleg_.mredata.button;

                break;
            }
            
            case SL::EventType::textEvent:
            {
                booba_event.type = booba::EventType::TextEvent;
                booba_event.Oleg.tedata.letter = event.Oleg_.tedata.letter;
                
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
}