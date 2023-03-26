#pragma once

#include "Texture.h"

const int FILL   = 0;
const int FILL_X = 1;
const int FILL_Y = 2;
const int CROP   = 3;

class Sprite
{

private:
    int mode_;

public:
    Vector2d shape_;
    Texture texture_;
    sf::Sprite sprite_;

    Sprite(Vector2d shape, const Texture &texture, int mode = FILL):
        mode_(mode),
        shape_(shape),
        texture_(texture), 
        sprite_()
    {
        setTexture(texture_);
    };

    Sprite(sf::Sprite sprite):
        mode_(0),
        shape_(float(sprite.getTextureRect().width)   * sprite.getScale().x,
               float(sprite_.getTextureRect().height) * sprite.getScale().y),
        texture_(*sprite.getTexture()),
        sprite_(sprite)
    {
    }
    
    void setTextureRect(Vector2d start, Vector2d end)
    {
        sprite_.setTextureRect(sf::IntRect((int)start.x_, (int)start.y_, (int)end.x_, (int)end.y_));
    }

    void set_shape(Vector2d shape, bool with_rescale = true)
    {
        shape_ = shape;
        
        if (with_rescale)
        {
            rescale();
            setTexture(texture_);
        }
    }
    
    Texture getTexture()
    {
        return texture_;
    }

    Color getColor()
    {
        return Color(sprite_.getColor());
    }
    
    void setColor(const Color &color)
    {
        sprite_.setColor(color.get_sf_color());
    }

    void setTexture(const Texture &texture, bool resetRect = true)
    {
        texture_ = texture;
        sprite_.setTexture(texture_.texture_, resetRect);
        
        if (resetRect) 
        {
            rescale();
        }
    }

    void setPosition(Vector2d position)
    {
        sprite_.setPosition(sf::Vector2f(position.x_, position.y_));
    }

    void rescale()
    {
        float scale_x = shape_.x_ / float(sprite_.getTexture()->getSize().x);
        float scale_y = shape_.y_ / float(sprite_.getTexture()->getSize().y);

        if (mode_ == FILL_X)
        {
            scale_y = scale_x;
        }

        if (mode_ == FILL_Y)
        {
            scale_x = scale_y;
        }

        sprite_.setScale(scale_x, scale_y);
    }

    Vector2d getScale()
    {
        return Vector2d(sprite_.getScale());
    }
};