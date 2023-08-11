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
                tool_button_->setLeftClick(dynamic_cast<SL::Command<booba::Tool *> *>(new SL::SimpleCommand<ToolManager, booba::Tool *>(this, &ToolManager::chooseTool)));
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
                if (settings_containers_[current_plugin_]->getShape().x_ > settings_field_->getShape().x_ ||
                    settings_containers_[current_plugin_]->getShape().y_ > settings_field_->getShape().y_)
                {
                    SL::DecoratorScrollBar *scroll_container = new SL::DecoratorScrollBar(settings_containers_[current_plugin_], settings_field_->getShape(), SL::Vector2d(0, 0));
                    settings_field_->add(scroll_container);
                }

                else
                {
                    settings_field_->add(settings_containers_[current_plugin_]);
                }
            }
        }
    }

    bool ToolManager::apply(SL::Image *image, SL::Image *hidden_layer, const SL::Event &event)
    {
        if (!current_plugin_)
        {
            return false;
        }

        booba::Event booba_event   = convert_event(event);
        ToolImage tool_image(image);
        ToolImage tool_hidden_layer(hidden_layer);
        tools_[current_plugin_]->apply(&tool_image, &tool_hidden_layer, &booba_event);
        
        return  tool_image.image_changed_;
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
        Button::setLeftClick(dynamic_cast<SL::Command<> *>(new SL::SimpleCommand<PluginButton>(this, &PluginButton::clickLeftEvent)));
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
