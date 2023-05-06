#include "ToolBucket.h"

bool ToolBucket::color_eq(const Color &color1, const Color &color2, int dispersion)
{
    return abs(int(color1.get_r()) - int(color2.get_r())) <= dispersion &&
           abs(int(color1.get_g()) - int(color2.get_g())) <= dispersion &&
           abs(int(color1.get_b()) - int(color2.get_b())) <= dispersion;
}

std::pair<SL::Vector2d, SL::Vector2d> ToolBucket::fill_ray(booba::Image *image, SL::Vector2d position)
{
    Color current_color = current_color_;

    SL::Vector2d left_pos = SL::Vector2d(0.f, position.y_);
    SL::Vector2d right_pos = SL::Vector2d(float(image->getW()) - 1, position.y_);

    for (int x = int(position.x_); x > -1; x--)
    {
        Color im_color = image->getPixel(x, int(position.y_));
        Color image_color = im_color;

        if (color_eq(image_color, current_color, dispersion_))
        {
            image->setPixel(x, int(position.y_), booba::APPCONTEXT->fgColor);
        }

        else
        {
            left_pos.x_ = float(x + 1);
            break;
        }
    } 

    for (int x = int(position.x_) + 1; x < int(image->getW()); x ++)
    {
        Color im_color = image->getPixel(x, int(position.y_));
        Color image_color = im_color;

        if (color_eq(image_color, current_color, dispersion_))
        {
            image->setPixel(x, int(position.y_), booba::APPCONTEXT->fgColor);
        }

        else
        {
            right_pos.x_ = float(x - 1);
            break;
        }
    } 
    
    return {left_pos, right_pos};
}

void ToolBucket::fill_part(booba::Image *image, SL::Vector2d position)
{
    Color current_color = current_color_;

    std::stack<SL::Vector2d> zatr_pixels;
    zatr_pixels.push(position);

    while (!zatr_pixels.empty())
    {        
        position = zatr_pixels.top();
        zatr_pixels.pop();

        std::pair<SL::Vector2d, SL::Vector2d> result = fill_ray(image, position);
        SL::Vector2d left_position = result.first;
        SL::Vector2d right_position = result.second;

        for (int x = int(left_position.x_); x <= int(right_position.x_); x++)
        {
            Color im_color = image->getPixel(x, int(position.y_) + 1);
            Color pixel_color = im_color;

            if (color_eq(pixel_color, current_color, dispersion_) && 
               !color_eq(pixel_color, booba::APPCONTEXT->fgColor, 0))    
            {
                for (; color_eq(pixel_color, current_color, dispersion_) &&
                      !color_eq(pixel_color, booba::APPCONTEXT->fgColor, 0) && 
                       x < int(image->getW()); x++)
                {
                    pixel_color = image->getPixel(x, int(position.y_ + 1));
                }
                
                if (uint32_t(position.y_) + 1 < image->getH())
                {
                    zatr_pixels.push(SL::Vector2d(float(x - 2), position.y_ + 1));
                }
            }
        }

        for (int x = int(left_position.x_); x <= int(right_position.x_); x++)
        {
            Color im_color = image->getPixel(x, int(position.y_) - 1);
            Color pixel_color = im_color;

            if (color_eq(pixel_color, current_color, dispersion_) &&
               !color_eq(pixel_color, booba::APPCONTEXT->fgColor, 0))     
            {
                for (; color_eq(pixel_color, current_color, dispersion_) &&
                      !color_eq(pixel_color, booba::APPCONTEXT->fgColor, 0) &&
                       x < int(image->getW()); x++)
                {
                    pixel_color = image->getPixel(x, int(position.y_ - 1));
                }
                
                if (position.y_ > 1)
                {
                    zatr_pixels.push(SL::Vector2d(float(x - 2), position.y_ - 1));
                }
            }
        }
    }
}


void ToolBucket::fill_field(booba::Image *image, SL::Vector2d position)
{
    fill_part(image, position);
}

void ToolBucket::apply(booba::Image* image, const booba::Event* event)
{    
    if (image == nullptr && event == nullptr)
    {
        return;
    }

    switch (event->type)
    {
        case booba::EventType::MousePressed:
        {
            clicked_ = true;

            SL::Vector2d position((float)event->Oleg.mbedata.x, (float)event->Oleg.mbedata.y);
            current_color_ = image->getPixel(int(position.x_), int(position.y_));

            fill_field(image, position);

            break;
        }

        case booba::EventType::MouseReleased:
        {
            clicked_ = false;
            break;
        }

        case booba::EventType::MouseMoved:
        case booba::EventType::ButtonClicked:
        case booba::EventType::SliderMoved:
        case booba::EventType::NoEvent:
        case booba::EventType::CanvasMMoved:
        case booba::EventType::CanvasMPressed:
        case booba::EventType::CanvasMReleased:
        
        default:
            break;
    }
}

booba::GUID booba::getGUID()
{
    booba::GUID myToolsGUID = {"BUCKET-TOOL"};
    
    return myToolsGUID;
}

void booba::init_module()
{
    new ToolBucket();
}