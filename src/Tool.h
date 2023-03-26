#pragma once
#define ELPIDIFOR_HIDDEN_LAYER 

#include "Library/GraphicLib.h"
#include "ToolCommand.h"
#include "ToolButton.h"

#include "tools.h"
#include "optionals.h"


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