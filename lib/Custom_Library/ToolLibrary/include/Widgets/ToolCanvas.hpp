// #pragma once

// #include "GraphLib.hpp"
// #include "../Tool/Tool.hpp"


// namespace TOOL_SL
// {
    // class ToolCanvas : public SL::Object 
    // {
    // public:

    //     SL::Image image_;

    //     SL::Command<const booba::Event &> *command_ = nullptr;

    //     ToolCanvas(SL::Vector2d shape, SL::Vector2d position, const SL::Image &image = SL::Image()) : SL::Object(shape, position, image.getTexture()),
    //         image_(image)
    //     {}
        
    //     ToolCanvas(const ToolCanvas &source) : SL::Object(*(const SL::Object *)&source),
    //         image_(source.image_),
    //         command_(source.command_)
    //     {}

    //     ToolCanvas &operator=(const ToolCanvas &source)
    //     {
    //         SL::Object::operator=(source);
    //         image_ = source.image_;
    //         command_ = source.command_;

    //         return *this;
    //     }

    //     void draw() override
    //     {   
    //         SL::Sprite sprite(shape_, image_.getTexture());
    //         render_texture_.clear();
    //         render_texture_.draw(sprite);
            
    //         SL::Object::draw();
    //     }

    //     void setCommand(SL::Command<const booba::Event &> *command)
    //     {
    //         command_ = command;
    //     }

    //     SL::Command<const booba::Event &> *get_command()
    //     {
    //         return command_;
    //     }

    //     void clickLeftEvent(const SL::Event &event) override
    //     {
    //         if (pointBelong(event.Oleg_.mpedata.pos))
    //         {
    //             SL::Event new_event = event;
    //             new_event.type_ = SL::EventType::CanvasMPressed;
    //             new_event.Oleg_.cedata.id  = uint64_t(this); 
    //             new_event.Oleg_.cedata.pos = event.Oleg_.mpedata.pos - getField().first;
            
    //             if (command_)
    //             {
    //                 command_->Execute(convert_event(new_event));
    //             }
    //         }
    //     }

    //     void moveMouseEvent(const SL::Event &event) override
    //     {
    //         if (pointBelong(event.Oleg_.metion.pos))
    //         {
    //             SL::Event new_event = event;
    //             new_event.type_ = SL::EventType::CanvasMMoved;
    //             new_event.Oleg_.cedata.id  = uint64_t(this); 
    //             new_event.Oleg_.cedata.pos = event.Oleg_.metion.pos - getField().first;
                
    //             if (command_)
    //             {
    //                 command_->Execute(convert_event(new_event));
    //             }
    //         }
    //     }

    //     void releaseLeftEvent(const SL::Event &event) override
    //     {
    //         if (pointBelong(event.Oleg_.mredata.pos))
    //         {
    //             SL::Event new_event = event;
    //             new_event.type_ = SL::EventType::CanvasMReleased;
    //             new_event.Oleg_.cedata.id  = uint64_t(this); 
    //             new_event.Oleg_.cedata.pos = event.Oleg_.mredata.pos - getField().first;
            
    //             if (command_)
    //             {
    //                 command_->Execute(convert_event(new_event));
    //             }
    //         }
    //     }
    // };
// }