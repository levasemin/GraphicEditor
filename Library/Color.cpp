#include "Color.h"

const Color Color::Black  ((uint8_t)0,   (uint8_t)0,   (uint8_t)0,    uint8_t(255));
const Color Color::White  ((uint8_t)255, (uint8_t)255, (uint8_t)255,  uint8_t(255));       
const Color Color::Red    ((uint8_t)255, (uint8_t)0,   (uint8_t)0,    uint8_t(255));         
const Color Color::Green  ((uint8_t)0,   (uint8_t)255, (uint8_t)0,    uint8_t(255));       
const Color Color::Blue   ((uint8_t)0,   (uint8_t)0,   (uint8_t)255,  uint8_t(255));
const Color Color::Grey   ((uint8_t)69,  (uint8_t)69,  (uint8_t)69,   uint8_t(255));        
const Color Color::Yellow ((uint8_t)255, (uint8_t)255, (uint8_t)0,    uint8_t(255));      
const Color Color::Magenta((uint8_t)255, (uint8_t)0,   (uint8_t)255,  uint8_t(255));     
const Color Color::Cyan   ((uint8_t)0,   (uint8_t)255, (uint8_t)255,  uint8_t(255));  

bool Color::operator == (const Color &color2)
{
    return !(doublecmp(r_, color2.r_) || doublecmp(g_, color2.g_) || doublecmp(b_, color2.b_));
}
bool Color::operator != (const Color &color2)
{
    return !operator==(color2);
}

Color &Color::operator += (const Color &color2)
{
    r_ = uint8_t(r_ + color2.r_);
    g_ = uint8_t(g_ + color2.g_);
    b_ = uint8_t(b_ + color2.b_);
    
    r_rel_ = r_ / 255.f;
    g_rel_ = g_ / 255.f;
    b_rel_ = b_ / 255.f;

    return *this;
}
Color &Color::operator += (float number)
{
    r_rel_ += number;
    g_rel_ += number;
    b_rel_ += number;

    r_ = uint8_t(r_rel_ * 255.f);
    g_ = uint8_t(g_rel_ * 255.f);
    b_ = uint8_t(b_rel_ * 255.f);

    return *this;
}

Color &Color::operator -= (const Color &color2)
{
    r_ = uint8_t(r_ - color2.r_);
    g_ = uint8_t(g_ - color2.g_);
    b_ = uint8_t(b_ - color2.b_);

    r_ = uint8_t(r_rel_ * 255.f);
    g_ = uint8_t(g_rel_ * 255.f);
    b_ = uint8_t(b_rel_ * 255.f);

    return *this;
}
Color &Color::operator -= (float number)
{
    r_rel_ -= number;
    g_rel_ -= number;
    b_rel_ -= number;

    r_ = uint8_t(r_rel_ * 255.f);
    g_ = uint8_t(g_rel_ * 255.f);
    b_ = uint8_t(b_rel_ * 255.f);

    return *this;
}

Color &Color::operator *= (const Color &color2)
{
    r_rel_ *= color2.r_rel_;
    g_rel_ *= color2.g_rel_;
    b_rel_ *= color2.b_rel_;

    r_ = uint8_t(r_rel_ * 255.f);
    g_ = uint8_t(g_rel_ * 255.f);
    b_ = uint8_t(b_rel_ * 255.f);

    return *this;
}
Color &Color::operator *= (float number)
{
    r_rel_ *= number;
    g_rel_ *= number;
    b_rel_ *= number;

    r_ = uint8_t(r_rel_ * 255.f);
    g_ = uint8_t(g_rel_ * 255.f);
    b_ = uint8_t(b_rel_ * 255.f);

    return *this;
}

Color &Color::operator /= (const Color &color2)
{
    r_rel_ /= color2.r_rel_;
    g_rel_ /= color2.g_rel_;
    b_rel_ /= color2.b_rel_;

    r_ = uint8_t(r_rel_ * 255.f);
    g_ = uint8_t(g_rel_ * 255.f);
    b_ = uint8_t(b_rel_ * 255.f);

    return *this;
}
Color &Color::operator /= (float number)
{
    r_rel_ /= number;
    g_rel_ /= number;
    b_rel_ /= number;

    r_ = uint8_t(r_rel_ * 255.f);
    g_ = uint8_t(g_rel_ * 255.f);
    b_ = uint8_t(b_rel_ * 255.f);

    return *this;
}

Color operator + (const Color &color1, const Color &color2)
{
    Color new_color = std::move(color1);
    new_color += color2;

    return new_color;
}
Color operator + (const Color &color, uint8_t number)
{
    Color new_color = color;
    new_color += number;
    
    return new_color;
}
Color operator + (uint8_t number, const Color &color)
{
    Color new_color = color;
    new_color += number;
    
    return new_color;
}
Color operator + (const Color &color, float number)
{
    Color new_color = color;
    new_color += number;
    
    return new_color;
}
Color operator + (float number, const Color &color)
{
    Color new_color = color;
    new_color += number;
    
    return new_color;
}

Color operator - (const Color &color1, const Color &color2)
{
    Color new_color = color1;
    new_color -= color2;
    
    return new_color;
}
Color operator - (const Color &color, uint8_t number)
{
    Color new_color = color;
    new_color -= number;
    
    return new_color;
}
Color operator - (const Color &color, float number)
{
    Color new_color = color;
    new_color -= number;
    
    return new_color;
}

Color operator * (const Color &color1, const Color &color2)
{
    Color new_color = color1;
    new_color *= color2;
    
    return new_color;
}
Color operator * (const Color &color, uint8_t number)
{
    Color new_color = color;
    new_color *= number;
    
    return new_color;
}
Color operator * (uint8_t number, const Color &color)
{
    Color new_color = color;
    new_color *= number;
    
    return new_color;
}
Color operator * (const Color &color, float number)
{
    Color new_color = color;
    new_color *= number;
    
    return new_color;
}
Color operator * (float number, const Color &color)
{
    Color new_color = color;
    new_color *= number;
    
    return new_color;
}

Color operator / (const Color &color1, const Color &color2)
{
    Color new_color = color1;
    new_color /= color2;
    
    return new_color;
}
Color operator / (const Color &color, uint8_t number)
{
    Color new_color = color;
    new_color /= number;
    
    return new_color;
}
Color operator / (const Color &color, float number)
{
    Color new_color = color;
    new_color /= number;
    
    return new_color;
}

void Color::pow(float degree)
{
    r_rel_ = powf32(r_rel_, degree);
    g_rel_ = powf32(g_rel_, degree);
    b_rel_ = powf32(b_rel_, degree);

    claim();
}

void Color::set_h(float h)
{
    h_ = h;
    convert_hsv_rgb();

    r_rel_ = r_ / 255.f;
    g_rel_ = g_ / 255.f;
    b_rel_ = b_ / 255.f;
    
    claim();
}

void Color::set_s(float s)
{
    s_ = s;
    convert_hsv_rgb();

    r_rel_ = r_ / 255.f;
    g_rel_ = g_ / 255.f;
    b_rel_ = b_ / 255.f;

    claim();
}

void Color::set_v(float v)
{
    v_ = v;
    convert_hsv_rgb();

    r_rel_ = r_ / 255.f;
    g_rel_ = g_ / 255.f;
    b_rel_ = b_ / 255.f;
    
    claim();
}

void Color::set_r(uint8_t r)
{
    r_rel_ = (float)r / 255.f;
    this->claim();

    convert_rgb_hsv();
}
void Color::set_g(uint8_t g)
{
    g_rel_ = (float)g / 255.f;
    this->claim();

    convert_rgb_hsv();
}
void Color::set_b(uint8_t b)
{
    b_rel_ = (float)b / 255.f;
    this->claim();

    convert_rgb_hsv();
}

void Color::set_a(uint8_t a)
{
    a_ = a;
}

float Color::get_h() const
{
    return h_;
}
float Color::get_s() const
{
    return s_;
}
float Color::get_v() const
{
    return v_;
}

uint8_t Color::get_r() const
{
    return r_;
}
uint8_t Color::get_g() const
{
    return g_;
}
uint8_t Color::get_b() const
{
    return b_;
}
uint8_t Color::get_a() const 
{
    return a_;
}

void Color::set_relation_r(float r_rel)
{
    r_rel_ = r_rel;
    this->claim();
}
void Color::set_relation_g(float g_rel)
{
    g_rel_ = g_rel;
    this->claim();
}
void Color::set_relation_b(float b_rel)
{
    b_rel_ = b_rel;
    this->claim();
}

float Color::get_relation_r()
{
    return r_rel_;
}

float Color::get_relation_g()
{
    return g_rel_;
}

float Color::get_relation_b()
{
    return b_rel_;
}

void Color::set_color(uint8_t r, uint8_t g, uint8_t b)
{
    r_rel_ = (float)r / 255.f;
    g_rel_ = (float)g / 255.f;
    b_rel_ = (float)b / 255.f;

    this->claim();
}

void Color::set_relation(float r_rel, float g_rel, float b_rel)
{
    r_rel_ = r_rel;
    g_rel_ = g_rel;
    b_rel_ = b_rel;
    this->claim();
}

void Color::claim()
{
    r_rel_ = r_rel_ <= 1 ? r_rel_ : 1;
    g_rel_ = g_rel_ <= 1 ? g_rel_ : 1;
    b_rel_ = b_rel_ <= 1 ? b_rel_ : 1;

    r_rel_ = r_rel_ >= 0 ? r_rel_ : 0;
    g_rel_ = g_rel_ >= 0 ? g_rel_ : 0;
    b_rel_ = b_rel_ >= 0 ? b_rel_ : 0;

    r_ = uint8_t(r_rel_ * 255.f);
    g_ = uint8_t(g_rel_ * 255.f);
    b_ = uint8_t(b_rel_ * 255.f);
}

Color::Color (uint8_t r, uint8_t g, uint8_t b, uint8_t a): r_(r), g_(g), b_(b), a_(a)
{
    r_rel_ = (float)r / 255.f;
    g_rel_ = (float)g / 255.f;
    b_rel_ = (float)b / 255.f;
    
    this->claim();

    convert_rgb_hsv();
};

Color::Color (sf::Color color) : Color(color.r, color.g, color.b, color.a)
{}

Color::Color (float h, float s, float v): h_(h), s_(s), v_(v)
{
    convert_hsv_rgb();

    r_rel_ = r_ / 255.f;
    g_rel_ = g_ / 255.f;
    b_rel_ = b_ / 255.f;
    this->claim();
};

sf::Color Color::get_sf_color() const
{
    return sf::Color(r_, g_, b_, a_);
}

void Color::print_color() const
{
    std::cout << (int)r_ << std::endl;
    std::cout << (int)g_ << std::endl;
    std::cout << (int)b_ << std::endl;
    std::cout << (int)a_ << std::endl;
}

void Color::convert_rgb_hsv()
{
    float cmax = std::max(r_rel_, std::max(g_rel_, b_rel_));
    float cmin = std::min(r_rel_, std::min(g_rel_, b_rel_));

    float delta = cmax - cmin;

    if (!doublecmp(cmax, cmin))
        h_ = 0;
 
    else if (!doublecmp(cmax, r_rel_))
        h_ = fmod(60.f * ((g_rel_ - b_rel_) / delta) + 360.f, 360.f);
 
    else if (!doublecmp(cmax, g_rel_))
        h_ = fmod(60.f * ((b_rel_ - r_rel_) / delta) + 120.f, 360.f);
 
    else if (!doublecmp(cmax, b_rel_))
        h_ = fmod(60.f * ((r_rel_ - g_rel_) / delta) + 240.f, 360.f);

    if (!doublecmp(cmax, 0))
        s_ = 0;
    else
        s_ = (delta / cmax);
 
    v_ = cmax;
}

void Color::convert_hsv_rgb()
{
    float c = v_ * s_;
    float mod_2 = (fmod((h_ / 60.f), 2.f));
    float x = c * (1.f - abs( mod_2 - 1.f));
    float m = v_ - c;
    float r = 0.f, g = 0.f, b = 0.f;

    if (h_ < 60.f)
    {
        r = c;
        g = x;
        b = 0.f;
    }

    else if (h_ < 120.f)
    {
        r = x;
        g = c;
        b = 0.f;
    }

    else if (h_ < 180.f)
    {
        r = 0.f;
        g = c;
        b = x;
    }

    else if (h_ < 240.f)
    {
        r = 0.f;
        g = x;
        b = c;
    }

    else if (h_ < 300.f)
    {
        r = x;
        g = 0.f;
        b = c;
    }

    else
    {
        r = c;
        g = 0.f;
        b = x;
    }
    
    r_ = (uint8_t)(round((r + m) * 255.f));
    g_ = (uint8_t)(round((g + m) * 255.f));
    b_ = (uint8_t)(round((b + m) * 255.f));
}

Color Color::convert_uint_color(uint32_t color)
{
    return Color((uint8_t)(color >> 24), (uint8_t)(color >> 16), (uint8_t)(color >> 8), (uint8_t)color);
}

uint32_t Color::convert_color_uint(const Color &color)
{
    return ((uint32_t)color.get_r() << (uint32_t)24) + ((uint32_t)color.get_g() << (uint32_t)16) + ((uint32_t)color.get_b() << (uint32_t)8) + (uint32_t)color.get_a();
}