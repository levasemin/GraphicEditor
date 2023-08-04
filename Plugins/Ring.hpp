#pragma once
#include "PluginStandart.hpp"

class Ring : public booba::Picture
{
public:
    Ring(int radius, booba::Color color = booba::Color::BLACK);

    void setRadius(int radius);
    void setColor(booba::Color color);
    const booba::Picture &getPicture();

private:
    booba::Color color_;
    int radius_;

    void updateTexture();
};

Ring::Ring(int radius, booba::Color color):
    radius_(radius),
    color_(color)
{
    updateTexture();
}

void Ring::setRadius(int radius)
{
    radius_ = radius;
    create(radius * 2, radius * 2, booba::Color(0, 0, 0, 0));

    updateTexture();
}

void Ring::setColor(booba::Color color)
{
    color_ = color;
    updateTexture();
}

void Ring::updateTexture()
{
    for (int y = 0; y < radius_ * 2 + 1; y++)
    {
        for (int x = 0; x < radius_ * 2 + 1; x++)
        {
            float value = float(pow(radius_, 2) - (pow(x - radius_, 2) + pow(y - radius_, 2)));

            if (value < 0)
            {
                setPixel(x, y, color_);
            }
        }
    }
}
