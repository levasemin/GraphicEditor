#pragma once

#include "Library/Image.h"
#include "Library/Widget.h"
#include "Library/Object.h"

using namespace SL;

class Surface;

class Memento
{
  public:
    Memento(const SL::Image &image):
        state_()
    {
        state_ = image;
    }
  private:
    friend class Surface;
    SL::Image state_;
};

class Surface : public Object 
{
public:

    Image image_;

    Surface(Vector2d shape, Vector2d center, const Image &image = Image()) : Object(shape, center, image.getTexture()),
        image_(image)
    {}
        
    void draw() override
    {   
        Sprite sprite(shape_, image_.getTexture());
        render_texture_->clear(Color(0, 0, 0, 0));
        render_texture_->draw(sprite);
        
        Object::draw();
    }

    Memento *createMemento()
    {
        return new Memento(image_);
    }

    void reinstateMemento(Memento *mem)
    {
        image_ = mem->state_;
    }

    void set_image(const Image &image)
    {
        image_ = image;
    }

    Image *get_image()
    {
        return &image_;
    }
};

// git log --pretty=tformat: --numstat | gawk '{ add += $1; subs += $2; loc += $1 - $2 } END { printf "added lines: %s removed lines: %s total lines: %s\n", add, subs, loc }' -
