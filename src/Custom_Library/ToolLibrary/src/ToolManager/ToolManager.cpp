#include "ToolManager.hpp"

namespace TOOL_SL
{
    class Canvas;

    ToolManager &ToolManager::getInstance()
    {
        static ToolManager instance;
        return instance;
    }

    void ToolManager::loadPlugins(std::string path)
    {
        std::string dlPath = "./../Plugins_so";

        for (const auto& curFile : std::filesystem::directory_iterator(path)) 
        {
            if (curFile.is_directory()) 
            {
                continue;
            }

            void* dlHandler = dlopen(curFile.path().c_str(), RTLD_LAZY | RTLD_GLOBAL);
            
            if (dlHandler) 
            {
                void (*init_func)()   = nullptr; 
                *((void**)&init_func) = dlsym(dlHandler, "init_module");

                (*init_func)();
            }

            else 
            {
                fprintf(stderr, "Unable to open lib: %s\n", dlerror());
            }
        }
    }

    void ToolManager::setToolPalette(ToolPalette *tool_palette)
    {
        tool_palette_ = tool_palette;
    }

    // void ToolManager::add(booba::Tool *new_tool)
    // {
    //     tools_.push_back(new_tool);

    //     SL::Button *tool_button_ = new SL::Button(SL::Vector2d(50, 50), SL::Vector2d(25, 25));

    //     tool_button_->setTexture(tool_palette_->getTexture());
    //     tool_button_->setTexture(SL::Texture(new_tool->getTexture()));
    //     tool_button_->setLeftClick((SL::Command<const SL::Event &> *) new SL::SimpleCommand<ToolManager, const SL::Event &>(this, &ToolManager::chooseTool));
    //     tool_palette_->add(tool_button_);

    //     SL::Container *setting_palette = new SL::Container(SL::Vector2d(setting_field_->getShape()), SL::Vector2d(0, 0));

    //     setting_palette->setTexture(setting_field_->getTexture());
    //     setting_palettes_.push_back(setting_palette);
    //     init_tool_ = new_tool;
    //     new_tool->buildSetupWidget();
    // }

    Canvas *ToolManager::getCanvas()
    {
        return canvas_;
    }

    void ToolManager::setCanvas(Canvas *canvas)
    {
        canvas_ = canvas;
    }

    void ToolManager::chooseTool(const SL::Event &event)
    {
        // canvas_->recoverySecondLayer();

        // std::vector<SL::Widget *> tool_palette_children = tool_palette_->getChildren();

        // for (size_t i = 0; i < tool_palette_children.size(); i++)
        // {
        //     if ((uint64_t)tool_palette_children[i] == event.Oleg_.bcedata.id)
        //     {
        //         if (active_tool_ != tools_[i])
        //         {
        //             // set_active_tool(tools_[i]);
        //         }

        //         else
        //         {
        //             // remove_active_tool();
        //         }
        //     }
        // }
    }

    void ToolManager::apply(const SL::Event *event)
    {
        // if (active_tool_)
        // {
        //     if ((event->type_ == SL::EventType::MouseReleased || event->type_ == SL::EventType::CanvasMPressed))
        //     {
        //         // create_memento(surface_);

        //         // surface_->image_.image_changed = false;
        //     }

        //     // booba::Event booba_event   = convert_event(*event);
        //     // active_tool_->apply(canvas_->getImage(), &booba_event);
        // }
    }
}