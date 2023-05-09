#pragma once

#include "../Graphic-Library/GraphLib/GraphLib.h"
#include "../Tool/tools.h"

namespace CUST_SL
{
    class Color : public SL::Color
    { 
    public:
        Color(float h, float s, float v) : SL::Color(h, s, v) 
        {
            
        };

        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : SL::Color(r, g, b, a) {} 
        Color(sf::Color color) : SL::Color(color) {}
        Color() : SL::Color(){};

        Color (const booba::Color &color) : Color(color.r, color.g, color.b, color.a) {}
        Color (const SL::Color &color) : SL::Color(color) {}

        operator booba::Color() const
        {
            return booba::Color(get_r(), get_g(), get_b(), get_a());
        }

        operator SL::Color() const
        {
            return SL::Color(get_r(), get_g(), get_b(), get_a());
        }

        static const Color TEXT;
        static const Color EDITOR;
        static const Color BUTTON_LIGHT;
        static const Color BUTTON_DARK;
        static const Color LABEL;
    };
}