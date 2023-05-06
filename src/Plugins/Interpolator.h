#pragma once

#include <iostream>
#include <vector>
#include <math.h>

#include "../Graphic-Library/GraphLib/GraphLib.h"



class Interpolator
{
public:
    int type_ = 0;

    Interpolator(int type):
        type_(type)
    {
    }
    
    static const int CATMULL_ROM = 0;

    virtual SL::Vector2d operator()(float t, SL::Vector2d point_0, SL::Vector2d point_1, SL::Vector2d point_2, SL::Vector2d point_3);
};