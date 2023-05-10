#pragma once

#include "GraphLib.h"
#include "Custom_Widgets.h"



class ToolCanvas : public SL::Object 
{
public:

    Image image_;

    SL::Command<const booba::Event &> *command_ = nullptr;

    ToolCanvas(SL::Vector2d shape, SL::Vector2d position, const Image &image = Image()) : SL::Object(shape, position, image.getTexture()),
        image_(image)
    {}
    
    ToolCanvas(const ToolCanvas &source) : SL::Object(*(const SL::Object *)&source),
        image_(source.image_),
        command_(source.command_)
    {}

    ToolCanvas &operator=(const ToolCanvas &source)
    {
        SL::Object::operator=(source);
        image_ = source.image_;
        command_ = source.command_;

        return *this;
    }

    void draw() override
    {   
        SL::Sprite sprite(shape_, image_.getTexture());
        render_texture_->clear();
        render_texture_->draw(sprite);
        
        SL::Object::draw();
    }

    void set_command(SL::Command<const booba::Event &> *command)
    {
        command_ = command;
    }

    SL::Command<const booba::Event &> *get_command()
    {
        return command_;
    }

    void ClickLeftEvent(const SL::Event &event) override
    {
        if (point_belonging(event.Oleg_.mbedata.pos))
        {
            SL::Event new_event = event;
            new_event.type_ = SL::EventType::CanvasMPressed;
            new_event.Oleg_.cedata.id  = uint64_t(this); 
            new_event.Oleg_.cedata.pos = event.Oleg_.mbedata.pos - get_start_field();
        
            if (command_)
            {
                command_->Execute(convert_event(new_event));
            }
        }
    }

    void MoveMouseEvent(const SL::Event &event) override
    {
        if (point_belonging(event.Oleg_.motion.pos))
        {
            SL::Event new_event = event;
            new_event.type_ = SL::EventType::CanvasMMoved;
            new_event.Oleg_.cedata.id  = uint64_t(this); 
            new_event.Oleg_.cedata.pos = event.Oleg_.motion.pos - get_start_field();
            
            if (command_)
            {
                command_->Execute(convert_event(new_event));
            }
        }
    }

    void ReleasedLeftEvent(const SL::Event &event) override
    {
        if (point_belonging(event.Oleg_.mredata.pos))
        {
            SL::Event new_event = event;
            new_event.type_ = SL::EventType::CanvasMReleased;
            new_event.Oleg_.cedata.id  = uint64_t(this); 
            new_event.Oleg_.cedata.pos = event.Oleg_.mredata.pos - get_start_field();
        
            if (command_)
            {
                command_->Execute(convert_event(new_event));
            }
        }
    }
};