#include "ToolPaint.h"

booba::GUID booba::getGUID()
{
    booba::GUID myToolsGUID = {"PAINT-TOOL"};
    
    return myToolsGUID;
}

void booba::init_module()
{
    new ToolPaint;
}