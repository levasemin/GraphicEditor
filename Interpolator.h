#pragma once

#include <iostream>
#include <vector>
#include <math.h>

#include "Library/GraphicLib.h"

class Interpolator
{
public:
    int type_ = 0;

    Interpolator(int type):
        type_(type)
    {

    }
    
    static const int CATMULL_ROM = 0;

    Vector2d operator()(float t, Vector2d point_0, Vector2d point_1, Vector2d point_2, Vector2d point_3);
};