#pragma once
#pragma GCC diagnostic ignored "-Wswitch-enum"

#include "GraphLib.hpp"
#include "ToolEvent.hpp"
#include "PluginStandart.hpp"

namespace TOOL_SL
{
    class ToolEditor : public booba::Editor
    {
    public:

        ToolEditor(SL::Editor *editor);

        ToolEditor(const ToolEditor &source) = default;
        ToolEditor &operator=(const ToolEditor &source) = default;
        ~ToolEditor() override;

        booba::Vector2d getPosition() const override;
        void setPosition(booba::Vector2d position) override;
        
        booba::Vector2d getShape() const override;
        void setShape(booba::Vector2d shape) override;

        void setColor(booba::Color color) override;

        const char *getText() override;
        void setText(std::string text) override;

        booba::Command<std::string> *getCommand() override;
        void setCommand(booba::Command<std::string> *command) override;

    protected:
        void textEvent(std::string text);

    private:
        SL::Editor *editor_;
        booba::Command<std::string> *tool_editor_command_ = nullptr;
    };  
}