#pragma once
#pragma GCC diagnostic ignored "-Wswitch-enum"

#include "../../Graphic-Library/GraphLib/GraphLib.h"
#include "../../Custom_Widgets/Custom_Widgets.h"



class ToolEditor : public SL::Editor
{
    SL::Command<const booba::Event &> *tool_editor_command_ = nullptr;
public:

    ToolEditor(SL::Vector2d shape, SL::Vector2d position, const SL::Texture &texture = SL::Texture(CUST_SL::Color::White)) : SL::Editor(shape, position, texture)    
    {
        editor_command_ = (SL::Command<const SL::Event &> *) new SL::SimpleCommand<ToolEditor, const SL::Event &>(this, &ToolEditor::ToolTextEvent);
    }

    ToolEditor(const ToolEditor &source): SL::Editor(*(const SL::Editor*)&source)
    {}

    ToolEditor &operator=(const ToolEditor &source)
    {
        SL::Label::operator=(*(const SL::Label *)&source);
        default_sprite_color_ = source.default_sprite_color_;
        editor_command_ = source.editor_command_;

        return *this;
    }

    void ToolTextEvent(const SL::Event &event)
    {
        SL::Event new_event;
        new_event.type_ = SL::EventType::TextEvent;
        new_event.Oleg_.textedata.id = (uint64_t)this;
        new_event.Oleg_.textedata.text = event.Oleg_.textedata.text;
        tool_editor_command_->Execute(convert_event(new_event));
    }

    void set_editor_command(SL::Command<const booba::Event &> *command)
    {
        tool_editor_command_ = command;
    }

    ~ToolEditor(){}
};  