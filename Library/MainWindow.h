#pragma once

#include "Texture.h"
#include "Vector2d.h"
#include "CompositeObject.h"
#include "Widget.h"

class MainWindow : public CompositeObject
{
public:
    int style_;
    enum Style
    {
        Close      = sf::Style::Close,
        Default    = sf::Style::Default,
        Fullscreen = sf::Style::Fullscreen,
        None       = sf::Style::None,
        Resize     =  sf::Style::Resize,
        Titlebar   = sf::Style::Titlebar,
    };

    MainWindow(Vector2d shape, Texture texture, int style = sf::Style::Default):
        CompositeObject(shape, Vector2d(shape.x_ / 2, shape.y_ / 2), texture),
        style_(style)
    {
    }
};