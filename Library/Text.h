#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#pragma once

#include <SFML/Graphics.hpp>
#include "Color.h"
#include "Font.h"
#include <string>

class Text
{
public:
    sf::Text text_;

    Text ():
        text_()
    {}
    
    Text (const Font &font): 
        text_()
    {
        setFont(font);
    };

    void setFont(const Font &font)
    {
        text_.setFont(font.font_);
    }

    void setCharacterSize(int size)
    {
        text_.setCharacterSize(size);
    }
    
    int getCharacterSize()
    {
        return text_.getCharacterSize();
    }

    void setPosition(const Vector2d &position)
    {
        text_.setPosition(position.x_, position.y_);
    }

    Vector2d getGlobalBounds()
    {
        return Vector2d(text_.getGlobalBounds().width, text_.getGlobalBounds().height);
    }

    void setString(const std::string &text)
    {
        text_.setString(text);
    }

    std::string getString()
    {
        return std::string(text_.getString());
    }

    void setFillColor(const Color &color)
    {
        text_.setFillColor(color.get_sf_color());
    }
    
    void setColor(const Color &color)
    {
        const sf::Color &sf_color = color.get_sf_color();
        text_.setColor(sf_color);
    }

    Font getFont() 
    {
        return Font(*text_.getFont());
    }

private:
    friend class Label;
    friend class RenderTexture;
};