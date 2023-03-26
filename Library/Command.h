#pragma once

template<class ...Tparams>
class Command
{
public:
    virtual void Execute(Tparams... params) = 0;

    Command(){};
    virtual ~Command() = default;
};