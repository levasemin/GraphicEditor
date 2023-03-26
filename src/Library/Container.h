#pragma once

#include "Texture.h"
#include "Window.h"
#include "Widget.h"
#include "Vector2d.h"

class Container : public CompositeObject
{
public:

    Container(Vector2d shape, Vector2d center): 
        CompositeObject(shape, center)
        {}
};