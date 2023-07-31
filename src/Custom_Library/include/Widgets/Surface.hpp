#pragma once

#include "GraphLib.hpp"


class Surface : public SL::Object
{
public:
    Surface(SL::Vector2d shape, SL::Vector2d position, const SL::Image &image = SL::Image()) : SL::Object(shape, position, image.getTexture()),
        image_(image)
    {}

    Surface(const Surface &source) : SL::Object(source.getShape(), source.getPosition(), source.image_.getTexture()),
        image_(source.image_)
    {

    }

    void draw() override
    {
        SL::Sprite sprite(getShape(), image_.getTexture());
        getRenderTexture()->clear(SL::Color(0, 0, 0, 0));
        getRenderTexture()->draw(sprite);

        SL::Object::draw();
    }

    void SetImage(const SL::Image &image)
    {
        image_ = image;
    }

    SL::Image *getImage()
    {
        return &image_;
    }

private:
    SL::Image image_;

};

// git log --pretty=tformat: --numstat | gawk '{ add += $1; subs += $2; loc += $1 - $2 } END { printf "added lines: %s removed lines: %s total lines: %s\n", add, subs, loc }' -
