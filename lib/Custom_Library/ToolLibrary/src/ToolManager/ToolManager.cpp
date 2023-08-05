#include "ToolManager.hpp"

booba::ApplicationContext* booba::APPCONTEXT = nullptr;

namespace TOOL_SL
{
    ToolManager::ToolManager():
        plugin_buttons_({}),
        tools_({}),
        settings_containers_({})
    {
        booba::APPCONTEXT = new booba::ApplicationContext();
        booba::APPCONTEXT->fgColor = booba::Color(255, 255, 255);
        booba::APPCONTEXT->bgColor = booba::Color();
    }

    ToolManager &ToolManager::getInstance()
    {
        static ToolManager instance;
        return instance;
    }


    void ToolManager::loadPlugins(std::string path)
    {
        for (const auto& curFile : std::filesystem::directory_iterator(path)) 
        {
            if (curFile.is_directory()) 
            {
                continue;
            }

            void* dlHandler = dlopen(curFile.path().c_str(), RTLD_LAZY | RTLD_GLOBAL);
            
            if (dlHandler) 
            {
                void *(*init_func)()   = nullptr; 
                *((void**)&init_func) = dlsym(dlHandler, "init_module");
                booba::Tool *new_tool = (booba::Tool *)(*init_func)();

                tools_[new_tool] = new_tool;
                
                PluginButton *tool_button_ = new PluginButton(SL::Vector2d(50, 50), SL::Vector2d(25, 25), new_tool);
                tool_button_->setTexture(SL::Texture(new_tool->getTexture()));
                tool_button_->setLeftClick((SL::Command<booba::Tool *> *) new SL::SimpleCommand<ToolManager, booba::Tool *>(this, &ToolManager::chooseTool));
                plugin_buttons_.push_back(tool_button_);
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

        for (auto plugin_button : plugin_buttons_)
        {
            tool_palette_->add(plugin_button);
        }
    }

    void ToolManager::setSettingsField(SL::Container *settings_field)
    {
        settings_field_ = settings_field;
    }

    void ToolManager::chooseTool(booba::Tool *tool)
    {
        if (settings_field_)
        {
            if (current_plugin_)
            {
                settings_field_->remove(settings_containers_[current_plugin_]);
            }

            current_plugin_ = tool;

            if (settings_containers_[current_plugin_])
            {
                settings_field_->add(settings_containers_[current_plugin_]);
            }
        }
    }

    void ToolManager::apply(SL::Image *image, SL::Image *hidden_layer, const SL::Event &event)
    {
        if (current_plugin_)
        {
            if ((event.type_ == SL::EventType::MouseReleased))
            {
                // create_memento(surface_);

                // surface_->image_.image_changed = false;
            }

            booba::Event booba_event   = convert_event(event);
            auto tool_image = ToolImage(image);
            auto tool_hidden_layer = ToolImage(hidden_layer);
            tools_[current_plugin_]->apply(&tool_image, &tool_hidden_layer, &booba_event);
        }
    }

    SL::Container *ToolManager::getSettingsContainer(booba::Tool *tool)
    {
        return settings_containers_[tool];
    }
    
    void ToolManager::addSettingsContainer(booba::Tool *tool, SL::Container *container)
    {
        settings_containers_[tool] = container;
    }

    PluginButton::PluginButton(SL::Vector2d shape, SL::Vector2d position, booba::Tool *tool, const SL::Texture &texture):
        SL::Button(shape, position, texture),
        tool_(tool)
    {
        Button::setLeftClick((SL::Command<> *) new SL::SimpleCommand<PluginButton>(this, &PluginButton::clickLeftEvent));
    }

    PluginButton::~PluginButton()
    {
        delete command_;
    }

    SL::Command<booba::Tool *> *PluginButton::getLeftClick()
    {
        return command_;
    }

    void PluginButton::setLeftClick(SL::Command<booba::Tool *> *command)
    {
        command_ = command;
    }
    
    void PluginButton::clickLeftEvent()
    {
        if (command_)
        {
            command_->Execute(tool_);        
        }
    }
}