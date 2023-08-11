#include "ToolEditor.hpp"

namespace TOOL_SL
{
    ToolEditor::ToolEditor(SL::Vector2d shape, SL::Vector2d position) : SL::Editor(shape, position)    
    {
        SL::Editor::setEditorCommand(static_cast<SL::Command<std::string> *>(new SL::SimpleCommand<ToolEditor, std::string>(this, &ToolEditor::textEvent)));
    }

    ToolEditor::~ToolEditor()
    {
        delete tool_editor_command_;
    }

    int ToolEditor::getX()
    {
        return SL::Editor::getPosition().x_;
    }

    void ToolEditor::setX(int x)
    {
        SL::Editor::setPosition(SL::Vector2d(static_cast<float>(x), SL::Editor::getPosition().y_));
    }

    int ToolEditor::getY()
    {
        return SL::Editor::getPosition().y_;
    }

    void ToolEditor::setY(int y)
    {
        SL::Editor::setPosition(SL::Vector2d(SL::Editor::getPosition().x_, static_cast<float>(y)));
    }

    int ToolEditor::getW()
    {
        return SL::Editor::getShape().x_;
    }

    void ToolEditor::setW(int w)
    {
        SL::Editor::setShape(SL::Vector2d(static_cast<float>(w), SL::Editor::getShape().y_));
    }

    int ToolEditor::getH()
    {
        return SL::Editor::getShape().y_;
    }

    void ToolEditor::setH(int h)
    {
        SL::Editor::setShape(SL::Vector2d(SL::Editor::getShape().x_, static_cast<float>(h)));
    }

    void ToolEditor::setColor(booba::Color color)
    {
        SL::Editor::setTexture(SL::Texture(SL::Color(color.r, color.g, color.b, color.a)));
    }

    const char *ToolEditor::getText()
    {
        return SL::Editor::getText().c_str();
    }

    void ToolEditor::setText(std::string text)
    {
        SL::Editor::setText(text);
    }

    void ToolEditor::textEvent(std::string text)
    {
        tool_editor_command_->Execute(text);
    }

    booba::Command<std::string> *ToolEditor::getCommand()
    {
        return tool_editor_command_;
    }

    void ToolEditor::setCommand(booba::Command<std::string> *command)
    {
        tool_editor_command_ = command;
    }
}