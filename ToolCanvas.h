#pragma once

#include "Library/Image.h"
#include "Library/Command.h"
#include "Library/Widget.h"
#include "Library/Object.h"

using namespace SL;

class ToolCanvas;

class ToolCanvas : public Object 
{
public:

    Image image_;

    Command<const booba::Event &> *command_ = nullptr;

    ToolCanvas(Vector2d shape, Vector2d center, const Image &image = Image()) : Object(shape, center, image.getTexture()),
        image_(image)
    {}
    
    ToolCanvas(const ToolCanvas &source) : Object(*(const Object *)&source),
        image_(source.image_),
        command_(source.command_)
    {}

    ToolCanvas &operator=(const ToolCanvas &source)
    {
        Object::operator=(source);
        image_ = source.image_;
        command_ = source.command_;

        return *this;
    }

    void draw() override
    {   
        Sprite sprite(shape_, image_.getTexture());
        render_texture_->clear();
        render_texture_->draw(sprite);
        
        Object::draw();
    }

    void set_command(Command<const booba::Event &> *command)
    {
        command_ = command;
    }

    Command<const booba::Event &> *get_command()
    {
        return command_;
    }

    void ClickLeftEvent(const Event &event) override
    {
        if (point_belonging(event.Oleg_.mbedata.pos))
        {
            Event new_event = event;
            new_event.type_ = EventType::CanvasMPressed;
            new_event.Oleg_.cedata.id  = uint64_t(this); 
            new_event.Oleg_.cedata.pos = event.Oleg_.mbedata.pos - get_start_field();
        
            if (command_)
            {
                command_->Execute(convert_event(new_event));
            }
        }
    }

    void MoveMouseEvent(const Event &event) override
    {
        if (point_belonging(event.Oleg_.motion.pos))
        {
            Event new_event = event;
            new_event.type_ = EventType::CanvasMMoved;
            new_event.Oleg_.cedata.id  = uint64_t(this); 
            new_event.Oleg_.cedata.pos = event.Oleg_.motion.pos - get_start_field();
            
            if (command_)
            {
                command_->Execute(convert_event(new_event));
            }
        }
    }

    void ReleasedLeftEvent(const Event &event) override
    {
        if (point_belonging(event.Oleg_.mredata.pos))
        {
            Event new_event = event;
            new_event.type_ = EventType::CanvasMReleased;
            new_event.Oleg_.cedata.id  = uint64_t(this); 
            new_event.Oleg_.cedata.pos = event.Oleg_.mredata.pos - get_start_field();
        
            if (command_)
            {
                command_->Execute(convert_event(new_event));
            }
        }
    }
};