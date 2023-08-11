#include "Surface.hpp"

Surface::Surface(SL::Vector2d shape, SL::Vector2d position, const SL::Image &image = SL::Image()) : SL::Object(shape, position, image.getTexture()),
    image_(image)
{}

Surface::Surface(const Surface &source) : SL::Object(source.getShape(), source.getPosition(), source.image_.getTexture()),
    image_(source.image_)
{}

void Surface::draw()
{
    SL::Sprite sprite(getShape(), image_.getTexture());
    getRenderTexture()->clear(SL::Color(0, 0, 0, 0));
    getRenderTexture()->draw(sprite);

    SL::Object::draw();
}

void Surface::setImage(const SL::Image &image)
{
    image_ = image;
}

SL::Image *Surface::getImage()
{
    return &image_;
}