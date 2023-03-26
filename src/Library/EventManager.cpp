#include "EventManager.h"

void EventManager::distribute_event(Widget *window, const Event &event)
{
    switch (event.type_)
    {   
        case EventType::MousePressed:
        {
            if (event.Oleg_.mbedata.button == MouseButton::Left)
            {
                is_left_button_clicked_ = true; 
                window->ClickLeftEvent(event);
            }

            else if (event.Oleg_.mbedata.button == MouseButton::Right)
            {         
                is_right_button_clicked_ = true;
                window->ClickRightEvent(event);
            }

            break;
        }

        case EventType::KeyPressed:
        {
            window->PressKeyEvent(event);

            break;
        }

        case EventType::ScrollbarMoved:
        {            
            window->ScrollEvent(event);
            
            break;
        }
        
        case EventType::MouseMoved:
        {            
            window->MoveMouseEvent(event);

            break;
        }
        
        case EventType::MouseReleased:
        {
            if (event.Oleg_.mredata.button == MouseButton::Left)
            {
                is_left_button_clicked_ = false;
                window->ReleasedLeftEvent(event);
            }

            else if (event.Oleg_.mredata.button == MouseButton::Right)
            {
                is_right_button_clicked_ = false;
                window->ReleasedRightEvent(event);            
            }

            break;
        }

        case EventType::NoEvent:
        case EventType::ButtonClicked:
        case EventType::CanvasMPressed:
        case EventType::CanvasMReleased:
        case EventType::CanvasMMoved:
        case EventType::CanvasMleft:
        case EventType::TimerEvent:
        case EventType::Closed:
        default:
        {
            break;
        }
    }
}