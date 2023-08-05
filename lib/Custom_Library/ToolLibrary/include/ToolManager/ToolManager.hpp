#pragma once

#include <vector>
#include <deque>
#include <unordered_map>
#include <filesystem>
#include <dlfcn.h>
#include "GraphLib.hpp"
#include "ToolPalette.hpp"
#include "PluginStandart.hpp"
#include "ToolEvent.hpp"
#include "ToolImage.hpp"

namespace TOOL_SL
{
    class Canvas;
    class PluginButton;

    class ToolManager
    {
        ToolManager();

        ToolManager(const ToolManager &) = default;
        ToolManager &operator =(const ToolManager &) = default;

        ~ToolManager() = default;
        
    public:

        static ToolManager &getInstance();
        
        void loadPlugins(std::string path);

        void setToolPalette(ToolPalette *tool_palette);
        void setSettingsField(SL::Container *settings_field);

        void chooseTool(booba::Tool *tool);

        void apply(SL::Image *image, SL::Image *hidden_layer, const SL::Event &event);
        
        SL::Container *getSettingsContainer(booba::Tool *tool);

        void addSettingsContainer(booba::Tool *tool, SL::Container *container);

    private:
        std::vector<PluginButton *> plugin_buttons_;
        std::unordered_map<booba::Tool *, booba::Tool *> tools_;
        std::unordered_map<booba::Tool *, SL::Container *> settings_containers_;

        ToolPalette *tool_palette_ = nullptr;
        SL::Container *settings_field_ = nullptr;

        booba::Tool *current_plugin_ = nullptr;
    };

    class PluginButton : public SL::Button
    {
    public:
        PluginButton(SL::Vector2d shape, SL::Vector2d position, booba::Tool *tool, const SL::Texture &texture = SL::Texture(SL::Color::White));
        
        PluginButton(const PluginButton &source) = default;
        PluginButton &operator=(const PluginButton &source) = default;
        ~PluginButton();

        SL::Command<booba::Tool *> *getLeftClick();
        void setLeftClick(SL::Command<booba::Tool *> *command);

    private:
        booba::Tool *tool_;
        SL::Command<booba::Tool *> *command_;

        void clickLeftEvent();
    };
}