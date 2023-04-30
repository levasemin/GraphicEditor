#include "ToolStyle.h"

void booba::init_module()
{
    new ToolStyle;
}

booba::GUID booba::getGUID()
{
    booba::GUID myToolsGUID = {"STYLE-TOOL"};
    
    return myToolsGUID;
}
