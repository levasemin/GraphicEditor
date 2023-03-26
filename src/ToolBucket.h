#pragma once

#include "Tool.h"
#include "Command.h"
#include "ToolCommand.h"
#include "ToolManager.h"
#include "Editor.h"
#include "Color.h"
#include "Circle.h"
#include <deque>
#include <stack>

class ToolBucket : public Tool
{
public:
    bool clicked_ = false;
    int dispersion_ = 0;
    Editor dispersion_editor_;
    uint32_t current_color_ = 0;

    ToolBucket() : Tool(),
        dispersion_editor_(Vector2d(50, 30), Vector2d(40, 20))
    {                
        char icon_path[128] = "source/Bucket.png";
        std::memcpy(icon_path_, icon_path, 128);
        booba::addTool(this);

        dispersion_editor_.set_editor_command((Command<const std::string &> *) new SimpleCommand<ToolBucket, const std::string &>(this, &ToolBucket::set_dispersion));
    }


    ToolBucket(const ToolBucket &) = default;
    ToolBucket &operator=(const ToolBucket &) = default;

    void set_dispersion(const std::string &string)
    {
        dispersion_ = string.size() > 0 ? int(std::stoi(string)) : 0;
        dispersion_ = dispersion_ <= 255 ? dispersion_ : 255;
    }

    void apply(booba::Image* image, const booba::Event* event) override;
    bool color_eq(const Color &color1, const Color &color2, int dispersion);
    void fill_field(booba::Image *image, Vector2d position);
    void fill_part(booba::Image *image, Vector2d position);
    std::pair<Vector2d, Vector2d> fill_ray(booba::Image *image, Vector2d position);

    const char* getTexture() override
    {
        return icon_path_;
    } 

    void buildSetupWidget() override
    {
        ToolManager &tool_manager = ToolManager::getInstance();

        tool_manager.setting_palettes_.back()->add(&dispersion_editor_);
    }

private:
};

