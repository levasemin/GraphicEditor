#pragma once

#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Widget.h"
#include "Event.h"

class EventManager
{

public: 
    void distribute_event(Widget *window, const Event &event_);

private:
    bool is_left_button_clicked_ = false;
    bool is_right_button_clicked_ = false;
};