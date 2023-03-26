#include "ToolEraser.h"

booba::GUID booba::getGUID()
{
    booba::GUID myToolsGUID = {"ERASER-TOOL"};
    
    return myToolsGUID;
}

void booba::init_module()
{
    new ToolEraser();
}