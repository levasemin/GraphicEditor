#pragma once

#include "SFML/Graphics.hpp"
#include "Texture.h"

class Font
{

public:

    sf::Font font_;
    
    Font (const sf::Font &font) : font_(font) 
    {}

    static const Font Times_new_roman;

    Font (const char *filename) : font_()
    {
        font_.loadFromFile(filename);
    }

    Texture getTexture(unsigned int characterSize)
    {
        return Texture(font_.getTexture(characterSize));
    }

    bool loadFromFile(const char *filename)
    {
        return font_.loadFromFile(filename);
    }    

    friend class Text;
};