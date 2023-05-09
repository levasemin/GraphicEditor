#pragma once

#include <deque>
#include <stack>

#include "../Graphic-Library/GraphLib/GraphLib.h"


#include "optionals.h"
#include "../Tool/Tool.h"
#include "../Tool/ToolCommand.h"
#include "../Tool/ToolManager.h"
#include "Circle.h"

class ToolBucket : public Tool
{
public:
    bool clicked_ = false;
    int dispersion_ = 0;
    SL::Editor dispersion_editor_;
    CUST_SL::Color current_color_;

    ToolBucket() : Tool(),
        dispersion_editor_(SL::Vector2d(50, 30), SL::Vector2d(40, 20))
    {                
        char icon_path[128] = "source/Bucket.png";
        std::memcpy(icon_path_, icon_path, 128);
        booba::addTool(this);

        dispersion_editor_.set_editor_command((SL::Command<const SL::Event &> *) new SL::SimpleCommand<ToolBucket, const SL::Event &>(this, &ToolBucket::change_dispersion));
    }


    ToolBucket(const ToolBucket &) = default;
    ToolBucket &operator=(const ToolBucket &) = default;

    void change_dispersion(const SL::Event &event)
    {
        set_dispersion(dispersion_editor_.get_text());
    }

    void set_dispersion(const std::string &string)
    {
        dispersion_ = string.size() > 0 ? int(std::stoi(string)) : 0;
        dispersion_ = dispersion_ <= 255 ? dispersion_ : 255;
    }

    void apply(booba::Image* image, const booba::Event* event) override;
    bool color_eq(const CUST_SL::Color &color1, const CUST_SL::Color &color2, int dispersion);
    void fill_field(booba::Image *image, SL::Vector2d position);
    void fill_part(booba::Image *image, SL::Vector2d position);
    std::pair<SL::Vector2d, SL::Vector2d> fill_ray(booba::Image *image, SL::Vector2d position);

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

