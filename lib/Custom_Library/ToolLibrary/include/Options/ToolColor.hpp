// #pragma once

// #include "GraphLib.hpp"
// #include "PluginStandart.hpp"

// namespace TOOL_SL
// {
//     class Color : public SL::Color
//     {
//     public:
//         Color(float h, float s, float v) : SL::Color(h, s, v)
//         {

//         };

//         Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : SL::Color(r, g, b, a) {}
//         Color(sf::Color color) : SL::Color(color) {}
//         Color() : SL::Color(){};

//         Color (const booba::Color &color) : Color(color.r, color.g, color.b, color.a) {}
//         Color (const SL::Color &color) : SL::Color(color) {}

//         operator booba::Color() const
//         {
//             return booba::Color(get_r(), get_g(), get_b(), get_a());
//         }
//     };
// }
