#pragma once

#include <memory>
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wswitch-enum"

#pragma once

#include <filesystem>
#include <dlfcn.h>
#include <vector>

#include "GraphLib.h"


#include "Surface.h"
#include "ToolManager.h"
#include "ToolPalette.h"
#include "tools.hpp"

#include "Image.h"
#include "Color.h"


class Canvas : public SL::CompositeObject
{
    Canvas() : SL::CompositeObject(SL::Vector2d(0, 0), SL::Vector2d(0, 0)), tool_manager_(ToolManager::getInstance()) {}
    Canvas (const Canvas &source) = delete;

    Canvas &operator= (const Canvas &source) = delete;

    std::vector<std::deque<Memento *>> mementoList_main_;

public:
    ToolManager &tool_manager_;

    bool is_left_clicked_ = false;
    bool is_right_clicked_ = false;

    float zoom_ = 1;

    uint32_t current_layer_ = 0;

    std::vector<Surface>   main_layers_;
    std::vector<Surface *> visible_layers_;

    Surface *hidden_layer_;

    static Canvas *getInstance()
    {
        static Canvas canvas;
        return &canvas;
    }

    static Canvas *Create(SL::Vector2d shape, SL::Vector2d position, ToolPalette *tool_palette = nullptr);

    void MoveMouseEvent (const SL::Event &event) override;

    void ClickLeftEvent(const SL::Event &event) override;

    void ClickRightEvent(const SL::Event &event) override;

    void ReleasedLeftEvent (const SL::Event &event) override;

    void ReleasedRightEvent (const SL::Event &event) override;

    void PressKeyEvent(const SL::Event &event) override;

    void set_zoom(float value);

    void ConfigureSurface(Surface *surface);

    void set_image(const std::string &path_image);

    void set_image(const Image &new_image);

    Image *get_image();

    void add_tool(Tool *new_tool);

    Surface *get_surface();


    Surface *getLayer    (uint32_t index)
    {
        return &main_layers_[index];
    }

    Surface *createLayer (uint32_t index)
    {
        SL::Vector2d shape = main_layers_[0].get_image()->getSize();
        if (index == main_layers_.size())
        {
            Image im = Image(shape, CUST_SL::Color(0, 0, 0, 0));
            Surface surface(shape, SL::Vector2d(0, 0), im);
            // main_layers_.push_back(surface);
        }

        else
        {
            main_layers_.insert(main_layers_.begin() + index, Surface(shape, SL::Vector2d(0, 0), Image(shape, CUST_SL::Color(0, 0, 0, 0))));
        }

        return &main_layers_[index];
    }

    void deleteLayer   (int index)
    {
        main_layers_.erase(main_layers_.begin() + index);
    }

    size_t getCountMainlayer() const
    {
        return main_layers_.size();
    }

    void recovery_second_layer()
    {
        hidden_layer_->image_.create(hidden_layer_->image_.getSize(), CUST_SL::Color(0, 0, 0, 0));
    }

    void setCurrentLayer(uint32_t index)
    {
        current_layer_ = index;
    }

    void setVisibleLayer(uint32_t index)
    {
        for (int i = 0; i < visible_layers_.size(); i++)
        {
            if (&main_layers_[index] == visible_layers_[i])
            {
                return;
            }
        }

        visible_layers_.push_back(&main_layers_[index]);
        add(&main_layers_[index]);
    }

};
