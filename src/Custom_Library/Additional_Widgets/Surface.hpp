#pragma once

#include "GraphLib.hpp"

#include "../Options/Image.hpp"
#include "../Options/Color.hpp"

class Surface : public SL::Object
{
public:

    CUST_SL::Image image_;

    Surface(SL::Vector2d shape, SL::Vector2d position, const CUST_SL::Image &image = CUST_SL::Image()) : SL::Object(shape, position, image.getTexture()),
        image_(image)
    {}

    Surface(const Surface &that) : SL::Object(that.shape_, that.position_, that.image_.getTexture()),
        image_(that.image_)
    {

    }

    void draw() override
    {
        SL::Sprite sprite(shape_, image_.getTexture());
        render_texture_.clear(CUST_SL::Color(0, 0, 0, 0));
        render_texture_.draw(sprite);

        SL::Object::draw();
    }

    void set_image(const CUST_SL::Image &image)
    {
        image_ = image;
    }

    CUST_SL::Image *get_image()
    {
        return &image_;
    }
};

// git log --pretty=tformat: --numstat | gawk '{ add += $1; subs += $2; loc += $1 - $2 } END { printf "added lines: %s removed lines: %s total lines: %s\n", add, subs, loc }' -
