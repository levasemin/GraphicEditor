#pragma once

#include "../Graphic-Library/GraphLib/GraphLib.h"


#include "ToolCommand.h"
#include "Widgets/ToolButton.h"




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