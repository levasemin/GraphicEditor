#pragma once

#include "../Graphic-Library/GraphLib/GraphLib.h"
#include "../Custom_Widgets/Custom_Widgets.h"



class Circle : public Image
{
protected:
    int radius_ = 0;
    Color color_;
     
public:

    Circle(int radius, Color color = Color::Black): Image(SL::Vector2d(float(radius * 2), float(radius * 2))),
        radius_(radius),
        color_(color)
    {
    }
    void set_radius(int radius)
    {
        radius_ = radius;
        setSize(SL::Vector2d(float(radius * 2), float(radius * 2)));
    }

    int get_radius()
    {   
        return radius_;
    }

    void set_color(const Color &color)
    {
        color_ = color;
    }

    void draw_fill(booba::Image *image, SL::Vector2d center)
    {        
        for (int y = 0; y < radius_ * 2; y++)
        {
            for (int x = 0; x < radius_ * 2; x++)
            {
                float value = float(pow(radius_, 2) - (pow(x - radius_, 2) + pow(y - radius_, 2)));
                
                if (SL::doublecmp(value, 0) >= 0)
                {
                    image->setPixel(uint32_t((int)center.x_ + x - radius_), (uint32_t)((int)center.y_ + y - radius_), Color::convert_color_uint(color_));
                }
            }
        }
    }

    void draw_frame(booba::Image *image, SL::Vector2d center, float width)
    {        
        for (int y = 0; y < radius_ * 2 + 1; y++)
        {
            for (int x = 0; x < radius_ * 2 + 1; x++)
            {
                float value = float(pow(radius_, 2) - (pow(x - radius_, 2) + pow(y - radius_, 2)));

                if (SL::doublecmp(abs(value), float(pow(width, 2))) <= 0)
                {
                    image->setPixel(uint32_t((int)center.x_ + x - radius_), (uint32_t)((int)center.y_ + y - radius_), Color::convert_color_uint(color_));
                }
            }
        }
    }
};