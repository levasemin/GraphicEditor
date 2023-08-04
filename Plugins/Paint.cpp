#include "Paint.hpp"

ToolPaint::ToolPaint() : booba::Tool(),
    interpolator_(Interpolator::CATMULL_ROM),
    points_({}),
    drawing_object_(1),
    drawing_object_frame_(1)
    {
        widget_creator_ = (booba::WidgetCreator *)booba::getWidgetCreator(booba::getGUID());
        width_scroll_bar_ = (booba::ScrollBar *) widget_creator_->createWidget(booba::WidgetCreator::Type::SCROLLBAR, 0, 0, 0, 0);
        width_scroll_bar_->setMinValue(1);
        width_scroll_bar_->setMaxValue(30);
        width_scroll_bar_->setCommand((booba::Command<float> *) new booba::SimpleCommand<ToolPaint, float>(this, &ToolPaint::set_width));

        width_editor_ = (booba::Editor *)widget_creator_->createWidget(booba::WidgetCreator::Type::EDITOR, 0, 0, 0, 0);
        width_editor_->setCommand((booba::Command<std::string> *) new booba::SimpleCommand<ToolPaint, std::string>(this, &ToolPaint::set_width));
    }

void ToolPaint::set_width(std::string string)
{    
    if (string.size() == 0)
    {
        width_scroll_bar_->setValue(0);
        return;
    }

    if ('0' > string[string.size() - 1] || string[string.size() - 1] > '9')
    {
        string.resize(string.size() - 1);
        width_editor_->setText(string);
        
        return;
    }
    
    float width = string.size() > 0 ? float(std::stoi(string)) : 0;
    width = width <= 30 ? width : 30;
    
    width_scroll_bar_->setValue(width);

    drawing_object_.setRadius(int(width / 2) == 0 ? 1 : int(width / 2));
    drawing_object_frame_.setRadius(int(width / 2) == 0 ? 1 : int(width / 2));
}

void ToolPaint::set_width(float width)
{    
    if (width != 0)
    {
        width_editor_->setText(std::to_string(width));
    }
    
    drawing_object_.setRadius(width / 2 == 0 ? 1 : width / 2);
    drawing_object_frame_.setRadius(int(width / 2) == 0 ? 1 : int(width / 2));
}

void ToolPaint::paint(booba::Image *image)
{
    drawing_object_.setColor(booba::APPCONTEXT->fgColor);
    drawing_object_frame_.setColor(booba::APPCONTEXT->fgColor);
    
    image->setPicture(std::move(drawing_object_), points_.back().first, points_.back().second);

    if (points_.size() == 4)
    {
        for (float t = 0; t <= 1.f; t += 0.1f)
        {
            std::pair<int, int> new_point = interpolator_(t, points_[0], points_[1], points_[2], points_[3]);
            
            image->setPicture(std::move(drawing_object_), points_.back().first, points_.back().second);
        }
    }
}

void ToolPaint::apply(booba::Image* image, const booba::Event* event)
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

            std::pair<int, int> new_point((float)event->Oleg.mpedata.x, (float)event->Oleg.mpedata.y);

            points_.push_back(new_point);
            paint(image);
            points_.pop_back();

            break;
        }

        case booba::EventType::MouseReleased:
        {
            clicked_ = false;
            break;
        }

        case booba::EventType::MouseMoved:
        {
            booba::Image *second_layer = image->getHiddenLayer();
            std::pair<int, int> new_point((float)event->Oleg.motion.x, (float)event->Oleg.motion.y);

            if (clicked_)
            {
                if (points_.size() > 0)
                {
                    if (abs(points_.back().first - new_point.first) > 10 || abs(points_.back().second - new_point.second) > 10)
                    {
                        points_.clear();
                    }
                }

                points_.push_back(new_point);
                
                if (points_.size() > 4)
                {
                    points_.pop_front();
                }

                paint(image);
            }
            
            drawing_object_.setColor(booba::APPCONTEXT->fgColor);

            second_layer->setPicture(std::move(drawing_object_), new_point.first, new_point.second);           

            break;
        }
        
        case booba::EventType::NoEvent:
        
        default:
            break;
    }
}

void ToolPaint::recovery_second_layer(booba::Image *second_layer, booba::Image *image)
{
    for (int y = 0; y < int(image->getH()); y++)
    {
        for (int x = 0; x < int(image->getW()); x++)
        {
            second_layer->setPixel(x, y, image->getPixel(x, y));
        }
    }
}

const char* ToolPaint::getTexture()
{
    return icon_path_.c_str();;
} 

std::pair<int, int> ToolPaint::getShape()
{
    return {200, 300};
}

extern "C" void *init_module()
{
    return new ToolPaint();
}

extern "C" booba::GUID getGUID()
{
    return {"paintSL"};
}