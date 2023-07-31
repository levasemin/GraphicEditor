#pragma once
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "GraphLib.hpp"
#include "PluginStandart.hpp"

namespace TOOL_SL
{
    class ToolButton : public SL::Button, protected booba::Button
    {
    public:
        ToolButton(SL::Vector2d shape, SL::Vector2d position);

        ToolButton(const ToolButton &source) = default;
        ToolButton &operator= (const ToolButton &source) = default;
        ~ToolButton();

        int getX() override;
        void setX(int x) override;
        
        int getY() override;
        void setY(int y) override;

        int getW() override;
        void setW(int w) override;
        
        int getH() override;
        void setH(int h) override;
        
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
        booba::Command<> *tool_left_click_command_    = nullptr;
        booba::Command<> *tool_left_release_command_  = nullptr;

        booba::Command<> *tool_right_click_command_   = nullptr;
        booba::Command<> *tool_right_release_command_ = nullptr;
    };
}