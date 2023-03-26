#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wswitch-enum"

#pragma once

#include "Library/RenderTexture.h"
#include "Library/CompositeObject.h"
#include <vector>
#include "Surface.h"
#include "ToolManager.h"
#include "ToolPalette.h"
#include "Library/Vector2d.h"
#include <filesystem>
#include <dlfcn.h>

using namespace SL;

class Canvas : public CompositeObject
{
public:
    Surface *surface_ = nullptr;    
    Surface *second_surface_ = nullptr;

    ToolManager &tool_manager_;


    bool is_left_clicked_ = false;
    bool is_right_clicked_ = false;

    float zoom_ = 1;

    Canvas(Vector2d shape, Vector2d center, ToolPalette *tool_palette = nullptr, Container * setting_palette = nullptr) : 
        CompositeObject(shape, center, Texture(Color::Grey)),
        tool_manager_(ToolManager::getInstance())
    {   
        surface_        = new Surface(Vector2d(1, 1), Vector2d(0, 0), Image(Texture(Color::Grey)));
        second_surface_ = new Surface(Vector2d(1, 1), Vector2d(0, 0), Image());
        
        add(surface_);
        add(second_surface_);
        
        tool_manager_.set_surface(surface_);
        tool_manager_.set_second_surface(second_surface_);

        if (tool_palette)
        {
            tool_manager_.set_tool_palette(tool_palette);
        }
        if (setting_palette)
        {
            tool_manager_.set_setting_field(setting_palette);
        }
               
        std::string dlPath = "./Plugins";
        
        for (const auto& curFile : std::filesystem::directory_iterator(dlPath)) 
        {
            if (curFile.is_directory()) 
            {
                continue;
            }

            std::cout << curFile.path().c_str() << std::endl;
            void* dlHandler = dlopen(curFile.path().c_str(), RTLD_LAZY);
            
            if (dlHandler) 
            {
                void (*init_func)()   = nullptr; 
                *((void**)&init_func) = dlsym(dlHandler, "init_module");

                (*init_func)();

                booba::GUID (*guid_func)()   = nullptr;
                *((void**)&guid_func) = dlsym(dlHandler, "getGUID");

                (*guid_func)();
                tool_manager_.add_guid(guid_func(), dlHandler);
            }

            else 
            {
                fprintf(stderr, "Unable to open lib: %s\n", dlerror());
            }
        }
    }
    
    Canvas (const Canvas &source): CompositeObject(*(const CompositeObject *)&source),
        surface_(source.surface_),
        tool_manager_(source.tool_manager_)
    {} 

    Canvas &operator= (const Canvas &source)
    { 
        CompositeObject::operator=(*(const CompositeObject *)&source);
        surface_         = source.surface_;
        second_surface_    = source.second_surface_;

        return *this;
    }

    void MoveMouseEvent (const Event &event) override
    {
        Event new_event = event;

        if (surface_->point_belonging(event.Oleg_.motion.pos))
        {
            new_event.type_ = EventType::MouseMoved;
            
            new_event.Oleg_.motion.pos  = event.Oleg_.motion.pos - surface_->get_global_offset() - (surface_->get_center() - surface_->get_shape() / 2);
            new_event.Oleg_.motion.pos /= zoom_;

            tool_manager_.apply(surface_, &new_event);
        }
    }

    void ClickLeftEvent(const Event &event) override
    {
        Event new_event = event;

        if (surface_->point_belonging(event.Oleg_.mbedata.pos))
        {
            new_event.type_ = EventType::MousePressed;
            
            new_event.Oleg_.mbedata.pos  = event.Oleg_.mbedata.pos - surface_->get_global_offset() - (surface_->get_center() - surface_->get_shape() / 2);
            new_event.Oleg_.mbedata.pos /= zoom_;
            new_event.Oleg_.mbedata.button = MouseButton::Left;

            tool_manager_.apply(surface_, &new_event);

            is_left_clicked_ = true;
        }           
    }

    void ClickRightEvent(const Event &event) override
    {
        Event new_event = event;

        if (surface_->point_belonging(event.Oleg_.mbedata.pos))
        {
            new_event.type_ = EventType::MousePressed;
            
            new_event.Oleg_.mbedata.pos  = event.Oleg_.mbedata.pos - surface_->get_global_offset() - (surface_->get_center() - surface_->get_shape() / 2);
            new_event.Oleg_.mbedata.pos /= zoom_;
            new_event.Oleg_.mbedata.button = MouseButton::Right;

            tool_manager_.apply(surface_, &new_event);

            is_right_clicked_ = true;
        }           
    }
    
    void ReleasedLeftEvent (const Event &event) override
    {
        Event new_event = event;

        new_event.type_ = EventType::MouseReleased;
            
        new_event.Oleg_.mredata.pos  = event.Oleg_.mredata.pos - surface_->get_global_offset() - (surface_->get_center() - surface_->get_shape() / 2);
        new_event.Oleg_.mredata.pos /= zoom_;
        new_event.Oleg_.mredata.button = MouseButton::Left;
        tool_manager_.apply(surface_, &new_event);   


        is_left_clicked_ = false;
    }

    void ReleasedRightEvent (const Event &event) override
    {
        Event new_event = event;

        new_event.type_ = EventType::MouseReleased;
            
        new_event.Oleg_.mredata.pos  = event.Oleg_.mredata.pos - surface_->get_global_offset() - (surface_->get_center() - surface_->get_shape() / 2);
        new_event.Oleg_.mredata.pos /= zoom_;
        new_event.Oleg_.mredata.button = MouseButton::Right;
        tool_manager_.apply(surface_, &new_event);   

    
        is_right_clicked_ = false;
    }

    void PressKeyEvent(const Event &event) override
    {
        if (event.Oleg_.kpedata.ctrl)
        {            
            switch(event.Oleg_.kpedata.code)
            {
                case Key::Z:
                {
                    if (event.Oleg_.kpedata.shift)
                    {
                        tool_manager_.redo(surface_);
                    }

                    else
                    {
                        tool_manager_.undo(surface_);
                    }

                    break;
                }

                case Key::Equal:
                {
                    set_zoom(zoom_ + 0.1f);

                    break;
                }

                case Key::Hyphen:
                {
                    set_zoom(zoom_ - 0.1f);

                    break;
                }

                default:
                {
                    break;
                }
            }
        }
    }

    void set_zoom(float value)
    {
        zoom_ = value;

        surface_->set_shape(surface_->image_.getSize() * value);
        second_surface_->set_shape(surface_->image_.getSize() * value);
        
        Vector2d new_center = surface_->get_shape() / 2;

        new_center.x_ = surface_->get_shape().x_ > shape_.x_ ? new_center.x_ : shape_.x_ / 2; 
        new_center.y_ = surface_->get_shape().y_ > shape_.y_ ? new_center.y_ : shape_.y_ / 2; 
        
        surface_->set_center(new_center);
        second_surface_->set_center(new_center);
        
        reset_global_shape();
    }

    void set_image(const std::string &path_image)
    {
        Image image(path_image);
        set_image(image);
    }

    void set_image(const Image &new_image)
    {
        remove(surface_);
        remove(second_surface_);

        *surface_ = Surface(new_image.getSize(), new_image.getSize() / 2, new_image);
        *second_surface_ = Surface(new_image.getSize(), new_image.getSize() / 2, Image(new_image.getSize(), Color(0, 0, 0, 0)));

        Vector2d new_center = surface_->get_shape() / 2;

        new_center.x_ = surface_->get_shape().x_ > shape_.x_ ? new_center.x_ : shape_.x_ / 2; 
        new_center.y_ = surface_->get_shape().y_ > shape_.y_ ? new_center.y_ : shape_.y_ / 2; 
        
        surface_->set_center(new_center);
        second_surface_->set_center(new_center);
        
        add(surface_);
        add(second_surface_);
    }

    Image *get_image()
    {
        return &surface_->image_;
    }

    void add_tool(Tool *new_tool)
    {
        tool_manager_.add(new_tool);
    }    
};