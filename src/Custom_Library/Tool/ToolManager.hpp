#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include <vector>
#include <deque>
#include <unordered_map>

#include "GraphLib.hpp"
#include "../Event/Event.hpp"

#include "Tool.hpp"
#include "../Widgets/ToolPalette.hpp"
#include "../Additional_Widgets/Surface.hpp"
#include "../HistoryManager/HistoryManager.hpp"

const int MAX_BACKUP = 32;

template<>
struct std::hash<booba::GUID> {
    std::size_t operator()(const booba::GUID& g) const {
        std::string str(g.str);
        std::hash<std::string> hashsa;

        return hashsa(str);
    }
};

template <>
struct std::equal_to<booba::GUID> {
    constexpr bool operator()( const booba::GUID& lhs, const booba::GUID& rhs ) const {
        for (uint32_t curIdx = 0; curIdx < sizeof(lhs.str); curIdx++) {
            if (rhs.str[curIdx] != lhs.str[curIdx]) {
                return 0;
            }
        }

        return 1;
    }
};


class ToolManager
{
private:
    std::vector<booba::Tool *> tools_;
    std::unordered_map<booba::GUID, void *> plugins_;

    booba::Tool* active_tool_ = nullptr;

    ToolManager():
        tools_({}),
        plugins_({}),
        setting_palettes_({})
    {}

    ToolManager( const ToolManager &source):
        tools_(source.tools_),
        plugins_(source.plugins_),
        active_tool_(source.active_tool_),
        tool_palette_(source.tool_palette_),
        setting_field_(source.setting_field_),
        setting_palettes_(source.setting_palettes_)
    {}

    ToolManager& operator=(const ToolManager& source)
    {
        tools_            = source.tools_;
        plugins_          = source.plugins_;
        active_tool_      = source.active_tool_;
        tool_palette_     = source.tool_palette_;
        setting_field_    = source.setting_field_;
        setting_palettes_ = source.setting_palettes_;

        return *this;
    }

public:

    booba::Tool *init_tool_ = nullptr;

    ToolPalette *tool_palette_ = nullptr;
    SL::Container *setting_field_ = nullptr;

    std::vector<SL::Container *> setting_palettes_;

    Surface *surface_ = nullptr;
    Surface *second_surface_ = nullptr;

    static ToolManager& getInstance()
    {
        static ToolManager instance;
        return instance;
    }

    void set_tool_palette(ToolPalette *tool_palette)
    {
        tool_palette_ = tool_palette;
    }

    ToolPalette *get_tool_palette()
    {
        return tool_palette_;
    }

    void set_setting_field(SL::Container *setting_palette)
    {
        setting_field_ = setting_palette;
    }

    SL::Container *get_setting_field()
    {
        return setting_field_;
    }

    void add(booba::Tool *new_tool)
    {
        tools_.push_back(new_tool);

        SL::Button *tool_button_ = new SL::Button(SL::Vector2d(50, 50), SL::Vector2d(25, 25));

        tool_button_->set_texture(tool_palette_->get_texture());
        tool_button_->set_texture(SL::Texture(new_tool->getTexture()));
        tool_button_->set_left_click((SL::Command<const SL::Event &> *) new SL::SimpleCommand<ToolManager, const SL::Event &>(this, &ToolManager::tool_choose));
        tool_button_->set_pressed(true);
        tool_palette_->add(tool_button_);

        SL::Container *setting_palette = new SL::Container(SL::Vector2d(setting_field_->get_shape()), SL::Vector2d(0, 0));

        setting_palette->set_texture(setting_field_->get_texture());
        setting_palettes_.push_back(setting_palette);
        init_tool_ = new_tool;
        std::cout << "buildSetupWidget\n";
        new_tool->buildSetupWidget();
    }

    void tool_choose(const SL::Event &event)
    {
        recovery_second_layer();

        std::vector<SL::Widget *> tool_palette_children = tool_palette_->get_children();

        for (size_t i = 0; i < tool_palette_children.size(); i++)
        {
            if ((uint64_t)tool_palette_children[i] == event.Oleg_.bcedata.id)
            {
                if (active_tool_ != tools_[i])
                {
                    set_active_tool(tools_[i]);
                }

                else
                {
                    remove_active_tool();
                }
            }

            else
            {
                ((SL::Button *)(tool_palette_children[i]))->is_pressed_ = false;
            }
        }
    }

    void set_node(HistoryManager::Node *node)
    {
        current_node = node;
        surface_->set_image(HistoryManager::getInstance().get_state(node));
    }

    static HistoryManager::Node *get_node()
    {
        return current_node;
    }

    void create_memento(Surface *surface)
    {
        if (current_node == nullptr)
        {
            current_node = HistoryManager::getInstance().create_root(*surface->get_image());
        }
        else {
            HistoryManager::getInstance().add_state(current_node, *surface->get_image());    
        }
    }

    void apply(const SL::Event *event)
    {
        if (active_tool_)
        {
            if ((event->type_ == SL::EventType::MouseReleased || event->type_ == SL::EventType::CanvasMPressed) && surface_->image_.image_changed)
            {
                create_memento(surface_);

                surface_->image_.image_changed = false;
            }

            booba::Event booba_event   = convert_event(*event);
            active_tool_->apply(&surface_->image_, &booba_event);
        }
    }

    static void undo(Surface *surface)
    {
        auto image = HistoryManager::getInstance().undo_state(current_node);
        surface->set_image(image);
    }

    static void redo(Surface *surface)
    {
        auto image = HistoryManager::getInstance().redo_state(current_node);
        surface->set_image(image);
    }

    void remove_active_tool()
    {
        active_tool_ = nullptr;
    }

    void set_surface(Surface *surface)
    {
        surface_ = surface;
        current_node = HistoryManager::getInstance().create_root(*surface_->get_image());
        create_memento(surface);
    }

    void set_second_surface(Surface *second_surface)
    {
        second_surface_ = second_surface;
    }

    void recovery_second_layer()
    {
        second_surface_->image_.create(second_surface_->image_.getSize(), CUST_SL::Color(0, 0, 0, 0));
    }

    void set_active_tool(booba::Tool *tool)
    {
        size_t current_tool = -1;

        for (size_t i = 0; i < tools_.size(); i++)
        {
            if (tools_[i] == tool)
            {
                current_tool = i;
                break;
            }
        }

        active_tool_    = tool;

        std::vector<SL::Widget *> setting_field_children = setting_field_->get_children();

        for (size_t i = 0; i < setting_field_children.size(); i++)
        {
            setting_field_->remove(setting_field_children[i]);
        }

        setting_field_->add(setting_palettes_[current_tool]);
    }

    booba::Tool *get_active_tool(booba::Tool *tool)
    {
        return active_tool_;
    }

    void add_guid(const booba::GUID &guid, void *handler)
    {
        if (plugins_.find(guid) == plugins_.end())
        {
            plugins_[guid] = handler;
        }
    }

    void* get_guid_handler(const booba::GUID& guid)
    {
        if (plugins_.find(guid) != plugins_.end()) {
            return plugins_[guid];
        }

        return nullptr;
    }

    ~ToolManager() {};

protected:
    static HistoryManager::Node *current_node;
    static int numCommands_;
    static int max_forward_;
    static const int max_backup_ = MAX_BACKUP;

    friend class Canvas;
};

