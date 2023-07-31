#pragma once

#include <vector>
#include <deque>
#include <unordered_map>
#include <filesystem>
#include <dlfcn.h>
#include "GraphLib.hpp"
#include "ToolLibrary.hpp"
#include "ToolPalette.hpp"

namespace TOOL_SL
{
    class Canvas;

    class ToolManager
    {
        ToolManager() = default;

        ToolManager(const ToolManager &) = default;
        ToolManager &operator =(const ToolManager &) = default;

        ~ToolManager() = default;
        
    public:

        static ToolManager &getInstance();
        
        void loadPlugins(std::string path);

        void setToolPalette(ToolPalette *tool_palette);
        
        Canvas *getCanvas();
        void setCanvas(Canvas *canvas);
        
        // void add(booba::Tool *new_tool);

        void chooseTool(const SL::Event &event);

        void apply(const SL::Event *event);
        
    private:
        booba::Tool *init_tool_ = nullptr;

        // std::vector<booba::Tool *> tools_;
        std::vector<SL::Container *> setting_palettes_;

        booba::Tool* active_tool_ = nullptr;

        ToolPalette *tool_palette_ = nullptr;
        SL::Container *setting_field_ = nullptr;

        Canvas *canvas_;

    };
}