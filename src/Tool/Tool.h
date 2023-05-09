#pragma once

#include "GraphLib.h"
#include "tools.hpp"

class Tool : public booba::Tool
{

public:
    char icon_path_[128] = "";
    bool is_on_ = false;

    Tool()
    {

    };

    ~Tool() override {};
};
