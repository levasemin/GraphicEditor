#include "ToolEditor.hpp"

namespace TOOL_SL
{
    ToolEditor::ToolEditor(SL::Editor *editor) : editor_(editor)    
    {
        editor_->setEditorCommand(static_cast<SL::Command<std::string> *>(new SL::SimpleCommand<ToolEditor, std::string>(this, &ToolEditor::textEvent)));
    }

    ToolEditor::~ToolEditor()
    {
        delete tool_editor_command_;
    }

    booba::Vector2d ToolEditor::getPosition() const
    {
        return booba::Vector2d(editor_->getPosition().x_, editor_->getPosition().y_);
    }

    void ToolEditor::setPosition(booba::Vector2d position)
    {
        editor_->setPosition(SL::Vector2d(position.x_, position.y_));
    }

    booba::Vector2d ToolEditor::getShape() const
    {
        return booba::Vector2d(editor_->getShape().x_, editor_->getShape().y_);
    }

    void ToolEditor::setShape(booba::Vector2d shape)
    {
        editor_->setShape(SL::Vector2d(shape.x_, shape.y_));
    }

    void ToolEditor::setColor(booba::Color color)
    {
        editor_->setTexture(SL::Texture(SL::Color(color.r, color.g, color.b, color.a)));
    }

    const char *ToolEditor::getText()
    {
        return editor_->getText().c_str();
    }

    void ToolEditor::setText(std::string text)
    {
        editor_->setText(text);
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