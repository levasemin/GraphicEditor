#pragma once
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "GraphLib.hpp"
#include "PluginStandart.hpp"

namespace TOOL_SL
{
    class ToolButton : public booba::Button
    {
    public:
        ToolButton(SL::Button *button);

        ToolButton(const ToolButton &source) = default;
        ToolButton &operator= (const ToolButton &source) = default;
        ~ToolButton();

        booba::Vector2d getPosition() const override;
        void setPosition(booba::Vector2d position) override;
        
        booba::Vector2d getShape() const override;
        void setShape(booba::Vector2d shape) override;
        
        void setColor(booba::Color color) override;
            
        void setText(std::string text) override;

        booba::Command<> *getLeftClick() override;
        void setLeftClick (booba::Command<> *command) override;

        booba::Command<> *getReleaseLeftClick() override;
        void setReleaseLeftClick (booba::Command<> *command) override;

        booba::Command<> *getRightClick() override;
        void setRightClick (booba::Command<> *command) override;

        booba::Command<> *getReleaseRightClick() override;
        void setReleaseRightClick (booba::Command<> *command) override;

    protected:
        void clickLeftEvent    ();
        void releaseLeftEvent  ();

        void clickRightEvent   ();
        void releaseRightEvent ();

    private:
        SL::Button *button_ = nullptr;

        booba::Command<> *tool_left_click_command_    = nullptr;
        booba::Command<> *tool_left_release_command_  = nullptr;

        booba::Command<> *tool_right_click_command_   = nullptr;
        booba::Command<> *tool_right_release_command_ = nullptr;
    };
}