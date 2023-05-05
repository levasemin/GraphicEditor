#pragma once
#pragma GCC diagnostic ignored "-Wswitch-enum"

#include "../../Graphic-Library/GraphLib/GraphLib.h"

using namespace SL;

class ToolEditor : public Editor
{
    Command<const booba::Event &> *tool_editor_command_ = nullptr;
public:

    ToolEditor(Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::White)) : Editor(shape, position, texture)    
    {
        editor_command_ = (Command<const Event &> *) new SimpleCommand<ToolEditor, const Event &>(this, &ToolEditor::ToolTextEvent);
    }

    ToolEditor(const ToolEditor &source): Editor(*(const Editor*)&source)
    {}

    ToolEditor &operator=(const ToolEditor &source)
    {
        Label::operator=(*(const Label *)&source);
        default_sprite_color_ = source.default_sprite_color_;
        editor_command_ = source.editor_command_;

        return *this;
    }

    void ToolTextEvent(const Event &event)
    {
        Event new_event;
        new_event.type_ = EventType::TextEvent;
        new_event.Oleg_.textedata.id = (uint64_t)this;
        new_event.Oleg_.textedata.text = event.Oleg_.textedata.text;
        tool_editor_command_->Execute(convert_event(new_event));
    }

    void set_editor_command(Command<const booba::Event &> *command)
    {
        tool_editor_command_ = command;
    }

    ~ToolEditor(){}
};  