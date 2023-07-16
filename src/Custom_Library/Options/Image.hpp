#pragma once

#include "GraphLib.hpp"

#include "Color.hpp"

namespace CUST_SL
{
    class Image : public SL::Image, public booba::Image
    {
    public:
        bool image_changed = false;
        
        Image ();

        virtual ~Image();

        Image(const std::string &path);

        Image (const SL::Vector2d &shape, const CUST_SL::Color &color = CUST_SL::Color(uint8_t(0), uint8_t(0), uint8_t(0)));

        Image (const SL::Image &image);

        size_t getH() override;

        size_t getW() override;

        booba::Color getPixel(size_t x, size_t y) override;

        CUST_SL::Color getPixel(SL::Vector2d pos) const;

        using SL::Image::setPixel;

        void setPixel(size_t x, size_t y, booba::Color color) override;

        booba::Picture getPicture(size_t x, size_t y, size_t w, size_t h) override;

        void setPicture(booba::Picture &&pic) override;

        void clean(const booba::Color &color = booba::Color::WHITE) override;

        booba::Image *getHiddenLayer() override;
    };
}