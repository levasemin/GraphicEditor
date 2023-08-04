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

template<>
struct std::hash<booba::GUID> {
    std::size_t operator()(const booba::GUID& g) const {
        std::string str(g.str);
        std::hash<std::string> hashsa;

        return hashsa(str);
    }
};

template <>
struct std::equal_to<booba::GUID> {
    constexpr bool operator()( const booba::GUID& lhs, const booba::GUID& rhs ) const {
        for (uint32_t curIdx = 0; curIdx < sizeof(lhs.str); curIdx++) {
            if (rhs.str[curIdx] != lhs.str[curIdx]) {
                return 0;
            }
        }

        return 1;
    }
};

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
        
        void chooseTool(booba::GUID guid);

        void apply(SL::Image *image, const SL::Event &event);
        
        SL::Container *getSettingsContainer(booba::GUID guid);

    private:
        booba::Tool *init_tool_ = nullptr;

        std::vector<PluginButton *> plugin_buttons_;
        std::unordered_map<booba::GUID, booba::Tool *> tools_;
        std::unordered_map<booba::GUID, SL::Container *> settings_containers_;

        ToolPalette *tool_palette_ = nullptr;
        SL::Container *setting_field_ = nullptr;

        booba::GUID current_plugin_;
    };

    class PluginButton : public SL::Button
    {
    public:
        PluginButton(SL::Vector2d shape, SL::Vector2d position, booba::GUID guid, const SL::Texture &texture = SL::Texture(SL::Color::White));
        
        PluginButton(const PluginButton &source) = default;
        PluginButton &operator=(const PluginButton &source) = default;
        ~PluginButton();

        SL::Command<booba::GUID> *getLeftClick();
        void setLeftClick(SL::Command<booba::GUID> *command);

    private:
        booba::GUID guid_;
        SL::Command<booba::GUID> *command_;

        void clickLeftEvent();
    };
}