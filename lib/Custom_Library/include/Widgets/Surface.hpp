#pragma once

#include "GraphLib.hpp"


class Surface : public SL::Object
{
public:
    Surface(SL::Vector2d shape, SL::Vector2d position, const SL::Image &image);
    Surface(const Surface &source);

    void draw() override;

    SL::Image *getImage();
    void setImage(const SL::Image &image);

private:
    SL::Image image_;

};

// git log --pretty=tformat: --numstat | gawk '{ add += $1; subs += $2; loc += $1 - $2 } END { printf "added lines: %s removed lines: %s total lines: %s\n", add, subs, loc }' -
