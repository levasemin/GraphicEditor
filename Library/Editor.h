#pragma once
#pragma GCC diagnostic ignored "-Wswitch-enum"

#include "Label.h"


class Editor : public Label 
{
    Color default_sprite_color_;
    Command<const std::string &> *editor_command_ = nullptr;

public:
    bool clicked_ = false;
    int current_pos_ = 0;

    Editor(Vector2d shape, Vector2d center) : Label(shape, center),
        default_sprite_color_(sprite_.getColor())
    {
        std::string string = text_.getString();
    }

    Editor(const Editor &source): Label(*(const Label *)&source),    
        default_sprite_color_(source.default_sprite_color_),
        editor_command_(source.editor_command_)
    {}
    Editor &operator=(const Editor &source)
    {
        Label::operator=(*(const Label *)&source);
        default_sprite_color_ = source.default_sprite_color_;
        editor_command_ = source.editor_command_;

        return *this;
    }

    void set_texture(const Texture &texture) override
    {
        Object::set_texture(texture);
        default_sprite_color_ = sprite_.getColor();
    }

    void set_editor_command(Command<const std::string &> *editor_command)
    {
        editor_command_ = editor_command;
    }

    void setFont(const Font &font)
    {
        text_.setFont(font);
    }

    void PressKeyEvent (const Event &event) override
    {
        if (clicked_)
        {
            std::string string = text_.getString();

            if (event.Oleg_.kpedata.code == Key::Backspace)
            {
                if (current_pos_ > 0)
                {
                    string.erase(string.begin() + current_pos_);
                    string.erase(string.begin() + current_pos_ - 1);
                    current_pos_ --;
                }
            }

            else
            {
                char letter = 0;

                switch(event.Oleg_.kpedata.code)
                {
                    case Key::Comma:
                    {
                        letter = ',';
                        break;
                    }
                
                    case Key::Period:
                    {
                        letter = '.';
                        break;
                    }
                    
                    case Key::Slash:
                    {
                        letter = '/';
                        break;
                    }

                    default:
                    {
                        break;
                    }
                }
                
                if (Key::Left == event.Oleg_.kpedata.code)
                {
                    if (current_pos_ > 0)
                    {
                        string.erase(string.begin() + current_pos_);

                        current_pos_ --;
                    }
                }

                else if (Key::Right == event.Oleg_.kpedata.code)
                {
                    if (current_pos_ < int(string.size() - 1))
                    {
                        string.erase(string.begin() + current_pos_);

                        current_pos_ ++;
                    }
                }

                else
                { 
                    if (Key::A <= event.Oleg_.kpedata.code && event.Oleg_.kpedata.code <= Key::Z)
                    {
                        letter = event.Oleg_.kpedata.shift ? char(event.Oleg_.kpedata.code + int('A')) : char(event.Oleg_.kpedata.code + int('a'));
                    }

                    else if (Key::Num0 <= event.Oleg_.kpedata.code && event.Oleg_.kpedata.code <= Key::Num9)    
                    {
                        letter = char(event.Oleg_.kpedata.code - Key::Num0 + int('0'));
                    }

                    else if (Key::Numpad0 <= event.Oleg_.kpedata.code && event.Oleg_.kpedata.code <= Key::Numpad9)
                    {
                        letter = char(event.Oleg_.kpedata.code - Key::Numpad0 + int('0'));
                    }
                    
                    if (current_pos_ > 0)
                    {
                        string.erase(string.begin() + current_pos_);
                    }
                    
                    string.insert(string.begin() + current_pos_, letter);
                    current_pos_ ++;
                }
            }
            
            setString(string);

            if (editor_command_)
            {
                std::string final_string = string;
                
                editor_command_->Execute(final_string);
            }
        }
    }

    void MoveMouseEvent(const Event &event) override
    {
        if (point_belonging(event.Oleg_.motion.pos))
        {
            Color new_color = default_sprite_color_;
        
            new_color /= 3;
            new_color *= 2;

            sprite_.setColor(new_color);
        }

        else if (!clicked_) 
        {
            sprite_.setColor(default_sprite_color_);
        }

        Label::MoveMouseEvent(event);
    }

    void ClickLeftEvent(const Event &event) override
    {
        if (point_belonging(event.Oleg_.mbedata.pos))
        {
            clicked_ = true;

            Color new_color = default_sprite_color_;
            new_color /= 3;
            new_color *= 2;

            sprite_.setColor(new_color);

            std::string string = text_.getString();

            setString(string);
        }

        else
        {
            if (clicked_ == true)
            {
                std::string string = text_.getString();
                string.erase(string.begin() + current_pos_);
    
                clicked_ = false;

                setString(string);
            }

            sprite_.setColor(default_sprite_color_);
        }
    }

    void setString(const std::string &string) override
    {
        std::string final_string = string;

        if (clicked_)
        {
            if (final_string.find('|') == std::string::npos)
            {
                final_string.insert(final_string.begin() + current_pos_, '|');
            }
        }
        
        std::cout << final_string << std::endl;

        Label::setString(final_string);
    }
};  