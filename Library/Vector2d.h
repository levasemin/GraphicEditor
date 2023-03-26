#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Vector2d
{
public:
    float x_, y_;

    Vector2d(float x = 0, float y = 0): 
        x_(x),
        y_(y)
        {};
    
    Vector2d(sf::Vector2u sf_vector):
        x_((float)sf_vector.x),
        y_((float)sf_vector.y)
    {}

    Vector2d(sf::Vector2f sf_vector):
        x_(sf_vector.x),
        y_(sf_vector.y)
    {}

    sf::Vector2u to_sf_vector() const;
    void set_value(float x, float y);
    void print_value () const;

    friend Vector2d operator + (const Vector2d &first, const Vector2d &second);
    friend Vector2d operator - (const Vector2d &first, const Vector2d &second);
    friend Vector2d operator * (const Vector2d &first, float num);
    friend Vector2d operator * (float num, const Vector2d &first);
    friend Vector2d operator / (const Vector2d &first, float num);
    Vector2d &operator -= (const Vector2d &that);
    Vector2d &operator += (const Vector2d &that);
    Vector2d &operator *= (float num);
    Vector2d &operator /= (float num);
};