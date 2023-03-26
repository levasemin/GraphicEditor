#pragma once

#include "Vector2d.h"
#include "Color.h"
#include <SFML/Graphics.hpp>

class Texture
{
    
public:
    sf::Texture texture_;    
    
    Texture (): 
        texture_()
        {}
    
    Texture (const Texture &) = default;
    Texture& operator= (const Texture &) = default; 
    
    ~Texture(){}
    
    Texture(const char *path):
        texture_()
    {
        loadFromFile(path);
    };
    
    Texture (const Color &color):
        texture_()
    {
        sf::Image image;
        image.create(100, 100, color.get_sf_color());
        texture_.loadFromImage(image);
    }

    Texture (const sf::Texture &texture):
        texture_(texture)
    {
    }
    
    bool loadFromFile(const char *path)
    {
        return texture_.loadFromFile(path);
    }

    Vector2d getSize() const
    {
        return Vector2d(texture_.getSize());
    }    

private:
    friend class Sprite;
};