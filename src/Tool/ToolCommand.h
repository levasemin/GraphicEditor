#pragma once

#include "GraphLib.h"

#include "Canvas.h"



template <class Receiver>
class ToolCommand : public SL::Command<const booba::Event &>
{

public:
    using Action = void (Receiver:: *)(booba::Image *, const booba::Event *);

    ToolCommand(Receiver *receiver, Action action) : SL::Command<const booba::Event &>(),
        receiver_(receiver),
        action_(action) 
    {

    }

    ToolCommand(const ToolCommand &source):
        receiver_(source.receiver_),
        action_  (source.action_)
    {}

    ToolCommand &operator=(const ToolCommand &source)
    {
        receiver_ = source.receiver_;
        action_   = source.action_;

        return *this; 
    }

    void Execute(const booba::Event &event) override
    {
        (receiver_->*action_)(Canvas::getInstance()->get_surface()->get_image(), &event);
    }

private:
    Receiver *receiver_;
    Action action_;
};