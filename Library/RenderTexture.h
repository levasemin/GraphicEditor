#pragma once

#include "Text.h"
#include "Vector2d.h"
#include "Sprite.h"

class RenderTexture
{
public:
    Vector2d shape_;
    sf::RenderTexture render_texture_;
    
    RenderTexture(Vector2d shape):
        shape_(shape),
        render_texture_()
    {
        create(shape);
    };
    
    RenderTexture(const RenderTexture &) = default;
    RenderTexture& operator=(const RenderTexture &source)
    {
        shape_ = source.shape_;
        render_texture_.create(source.render_texture_.getSize().x, source.render_texture_.getSize().y);
        sf::Sprite sprite(source.render_texture_.getTexture());
        render_texture_.draw(sprite);

        return *this;
    }

    void create(const Vector2d &shape)
    {
        render_texture_.create((uint32_t)shape.x_, (uint32_t)shape.y_);      
    }
 
    void draw(const Sprite &sprite)
    {
        render_texture_.draw(sprite.sprite_);
    }

    void draw(const Text &text)
    {
        render_texture_.draw(text.text_);
    }
    
    void display()
    {
        render_texture_.display();
    }

    Texture getTexture()
    {
        return Texture(render_texture_.getTexture());
    }

    Vector2d getSize()
    {
        return Vector2d(render_texture_.getSize());
    }

    void clear(const Color &color = Color(0, 0, 0, 255))
    {
        render_texture_.clear(color.get_sf_color());
    }

    ~RenderTexture() = default;
};