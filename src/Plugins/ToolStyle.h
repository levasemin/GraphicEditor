#pragma once

#include <deque>

#include "../Graphic-Library/GraphLib/GraphLib.h"

#include "Circle.h"
#include "Interpolator.h"

extern booba::ApplicationContext* booba::APPCONTEXT;

class ToolStyle : booba::Tool
{
private:    

public:
    char icon_path[128] = "source/EyeDropper.png";

    ToolStyle()
    {                
        booba::addTool(this);
    }

    ToolStyle           (const ToolStyle &) = default;
    ToolStyle &operator=(const ToolStyle &) = default;

    void apply(booba::Image* image, const booba::Event* event) override
    {
        switch(event->type)
        {
            case booba::EventType::MousePressed:
            {
                std::cout << "HUI\n";
                booba::Picture pic(100, 100, 100, 100, image);

                for (int i = 0; i < 100; i++)
                {
                    for (int j = 0; j < 100; j++)
                    {
                        pic.getData()[i * 100 + j] = CUST_SL::Color::convert_color_uint(CUST_SL::Color(255, 255, 0, 255));
                    }
                }
                
                image->setPicture(std::move(pic));
            }
        };
    }

    void buildSetupWidget() override
    {
    }

    const char* getTexture() override
    {
        return icon_path;
    }
    ~ToolStyle()
    {}
};