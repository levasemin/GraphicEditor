#pragma once

#include "Library/Command.h"
#include "tools.h"
#include "optionals.h"
#include "Library/Event.h"

template <class Receiver>
class ToolCommand : public Command<const booba::Event &>
{

public:
    using Action = void (Receiver:: *)(booba::Image *, const booba::Event *);

    ToolCommand(Receiver *receiver, Action action) : Command<const booba::Event &>(),
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
        (receiver_->*action_)(nullptr, &event);
    }

private:
    Receiver *receiver_;
    Action action_;
};