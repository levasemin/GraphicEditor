#pragma once
#pragma GCC diagnostic ignored "-Wswitch-enum"

#include "GraphLib.hpp"
#include "ToolEvent.hpp"
#include "PluginStandart.hpp"

namespace TOOL_SL
{
    class ToolEditor : public booba::Editor, protected SL::Editor
    {
    public:

        ToolEditor(SL::Vector2d shape, SL::Vector2d position);

        ToolEditor(const ToolEditor &source) = default;
        ToolEditor &operator=(const ToolEditor &source) = default;
        ~ToolEditor() override;

        int getX() override;
        void setX(int x) override;
        
        int getY() override;
        void setY(int y) override;

        int getW() override;
        void setW(int w) override;
        
        int getH() override;
        void setH(int h) override;

        void setColor(booba::Color color) override;

        const char *getText() override;
        void setText(std::string text) override;

        booba::Command<std::string> *getCommand() override;
        void setCommand(booba::Command<std::string> *command) override;

    protected:
        void textEvent(std::string text);

    private:
        booba::Command<std::string> *tool_editor_command_ = nullptr;
    };  
}