// #pragma once

// #pragma GCC diagnostic ignored "-Wunused-parameter"
// #pragma GCC diagnostic ignored "-Wswitch-enum"

// #include <filesystem>
// #include <dlfcn.h>
// #include <vector>
// #include <memory>

// #include "GraphLib.hpp"

// #include "Surface.hpp"
// #include "../Tool/Tool.hpp"
// #include "../Widgets/ToolPalette.hpp"
// #include "PluginStandart.hpp"

// // #include "../Tool/ToolManager.hpp"

// class Canvas : public SL::CompositeObject
// {
//     Canvas() : SL::CompositeObject(SL::Vector2d(0, 0), SL::Vector2d(0, 0)), tool_manager_(ToolManager::getInstance()) {}
//     Canvas(const Canvas &source) = delete;

//     Canvas &operator=(const Canvas &source) = delete;

// public:
//     ToolManager &tool_manager_;

//     float zoom_ = 1;

//     Surface *main_layer_;
//     Surface *hidden_layer_;

//     static Canvas *getInstance()
//     {
//         static Canvas canvas;
//         return &canvas;
//     }

//     static Canvas *Create(SL::Vector2d shape, SL::Vector2d position, ToolPalette *tool_palette = nullptr);

// protected:
//     void moveMouseEvent(const SL::Event &event) override;

//     void clickLeftEvent(const SL::Event &event) override;

//     void clickRightEvent(const SL::Event &event) override;

//     void releaseLeftEvent(const SL::Event &event) override;

//     void releaseRightEvent(const SL::Event &event) override;

//     void pressKeyEvent(const SL::Event &event) override;

//     void set_zoom(float value);

//     void ConfigureSurface(Surface *surface);

//     void SetImage(const std::string &path_image);

//     void SetImage(const SL::Image &new_image);

//     SL::Image *getImage();

//     void add_tool(Tool *new_tool);

//     Surface *get_surface();

//     void set_current_node(HistoryManager::Node *node);
// };
