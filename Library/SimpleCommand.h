#pragma once

#include "Command.h"

template <class Receiver, class ...TParams>
class SimpleCommand : public Command<TParams...>
{

public:
    using Action = void (Receiver:: *)(TParams...);

    SimpleCommand(Receiver *receiver, Action action) : Command<TParams...>(),
        receiver_(receiver),
        action_(action) 
    {}

    SimpleCommand(const SimpleCommand &command) = default;
    SimpleCommand &operator= (const SimpleCommand &command) = default; 

    void Execute(TParams... params) override
    {
        (receiver_->*action_)(params...);
    }
    
    void unExecute(TParams... params)
    {

    }


    ~SimpleCommand() override {}
    
private:
    Receiver *receiver_ = nullptr;
    Action action_;
};