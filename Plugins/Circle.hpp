#pragma once
#include "PluginStandart.hpp"


class Circle : public booba::Picture
{
public:

    Circle(int radius, booba::Color color = booba::Color::BLACK);

    void setRadius(int radius);

    void setColor(const booba::Color &color);

private:
    int radius_ = 0;
    booba::Color color_;

    void updateTexture();
};


Circle::Circle(int radius, booba::Color color): Picture(),
    radius_(radius),
    color_(color)
{
    // updateTexture();
}

void Circle::setRadius(int radius)
{
    radius_ = radius_;

    create(radius_ * 2, radius_ * 2, color_);

    updateTexture();
}

void Circle::setColor(const booba::Color &color)
{
    color_ = color;

    updateTexture();
}

void Circle::updateTexture()
{
    for (int y = 0; y < radius_ * 2; y++)
    {
        for (int x = 0; x < radius_ * 2; x++)
        {
            float value = float(pow(radius_, 2) - (pow(x - radius_, 2) + pow(y - radius_, 2)));
            
            if (value > 0)
            {
                setPixel(x, y, color_);
            }
        }
    }
}