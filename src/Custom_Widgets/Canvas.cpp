#include "Canvas.h"

Canvas *Canvas::Create(SL::Vector2d shape, SL::Vector2d position, ToolPalette *tool_palette)
{
    getInstance()->set_shape(shape);
    getInstance()->set_position(position);
    getInstance()->set_texture(SL::Texture(CUST_SL::Color::Grey));

    getInstance()->tool_manager_ = ToolManager::getInstance();
    getInstance()->main_layers_.emplace_back(SL::Vector2d(1, 1), SL::Vector2d(0, 0), Image(SL::Texture(CUST_SL::Color::Grey)));
    getInstance()->hidden_layer_ = new Surface(SL::Vector2d(1, 1), SL::Vector2d(0, 0), Image());
    getInstance()->mementoList_main_.push_back(std::deque<Memento *>());
    getInstance()->add(&getInstance()->main_layers_[0]);
    getInstance()->add(getInstance()->hidden_layer_);
    
    getInstance()->tool_manager_.set_surface(&getInstance()->main_layers_[0]);
    getInstance()->tool_manager_.set_second_surface(getInstance()->hidden_layer_);
    getInstance()->tool_manager_.set_mementoList(&getInstance()->mementoList_main_[0]);
    
    if (tool_palette)
    {
        getInstance()->tool_manager_.set_tool_palette(tool_palette);
    }
            
    std::string dlPath = "./../src/Plugins_so";
    
    for (const auto& curFile : std::filesystem::directory_iterator(dlPath)) 
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

            // booba::GUID (*guid_func)()   = nullptr;
            // *((void**)&guid_func) = dlsym(dlHandler, "getGUID");

            // (*guid_func)();
            // tool_manager_.add_guid(guid_func(), dlHandler);
        }

        else 
        {
            fprintf(stderr, "Unable to open lib: %s\n", dlerror());
        }
    }

    return getInstance();
}


void Canvas::MoveMouseEvent (const SL::Event &event)
{
    SL::Event new_event = event;

    if (main_layers_[current_layer_].point_belonging(event.Oleg_.motion.pos))
    {
        new_event.type_ = SL::EventType::MouseMoved;
        
        new_event.Oleg_.motion.pos  = event.Oleg_.motion.pos - main_layers_[current_layer_].get_global_offset() - main_layers_[current_layer_].get_position();
        new_event.Oleg_.motion.pos /= zoom_;

        tool_manager_.apply(&new_event);
    }
}

void Canvas::ClickLeftEvent(const SL::Event &event)
{
    SL::Event new_event = event;

    if (main_layers_[current_layer_].point_belonging(event.Oleg_.mbedata.pos))
    {
        new_event.type_ = SL::EventType::MousePressed;
        
        new_event.Oleg_.mbedata.pos  = event.Oleg_.mbedata.pos - main_layers_[current_layer_].get_global_offset() - main_layers_[current_layer_].get_position();
        new_event.Oleg_.mbedata.pos /= zoom_;
        new_event.Oleg_.mbedata.button = SL::MouseButton::Left;

        tool_manager_.apply(&new_event);

        is_left_clicked_ = true;
    }           
}

void Canvas::ClickRightEvent(const SL::Event &event)
{
    SL::Event new_event = event;

    if (main_layers_[current_layer_].point_belonging(event.Oleg_.mbedata.pos))
    {
        new_event.type_ = SL::EventType::MousePressed;
        
        new_event.Oleg_.mbedata.pos  = event.Oleg_.mbedata.pos - main_layers_[current_layer_].get_global_offset() - main_layers_[current_layer_].get_position();
        new_event.Oleg_.mbedata.pos /= zoom_;
        new_event.Oleg_.mbedata.button = SL::MouseButton::Right;

        tool_manager_.apply(&new_event);

        is_right_clicked_ = true;
    }           
}

void Canvas::ReleasedLeftEvent (const SL::Event &event)
{
    SL::Event new_event = event;

    new_event.type_ = SL::EventType::MouseReleased;
        
    new_event.Oleg_.mredata.pos  = event.Oleg_.mredata.pos - main_layers_[current_layer_].get_global_offset() - main_layers_[current_layer_].get_position();
    new_event.Oleg_.mredata.pos /= zoom_;
    new_event.Oleg_.mredata.button = SL::MouseButton::Left;
    tool_manager_.apply(&new_event);   


    is_left_clicked_ = false;
}

void Canvas::ReleasedRightEvent (const SL::Event &event)
{
    SL::Event new_event = event;

    new_event.type_ = SL::EventType::MouseReleased;
        
    new_event.Oleg_.mredata.pos  = event.Oleg_.mredata.pos - main_layers_[current_layer_].get_global_offset() - main_layers_[current_layer_].get_position();
    new_event.Oleg_.mredata.pos /= zoom_;
    new_event.Oleg_.mredata.button = SL::MouseButton::Right;
    tool_manager_.apply(&new_event);   


    is_right_clicked_ = false;
}

void Canvas::PressKeyEvent(const SL::Event &event)
{
    if (event.Oleg_.kpedata.ctrl)
    {            
        switch(event.Oleg_.kpedata.code)
        {
            case SL::Key::Z:
            {
                if (event.Oleg_.kpedata.shift)
                {
                    tool_manager_.redo(&main_layers_[current_layer_]);
                }

                else
                {
                    tool_manager_.undo(&main_layers_[current_layer_]);
                }

                break;
            }

            case SL::Key::Equal:
            {
                set_zoom(zoom_ + 0.1f);

                break;
            }

            case SL::Key::Hyphen:
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

void Canvas::set_zoom(float value)
{
    zoom_ = value;

    for (int i = 0; i < main_layers_.size(); i++)
    {
        main_layers_[i].set_shape(main_layers_[i].image_.getSize() * value);
    }

    hidden_layer_->set_shape(hidden_layer_->image_.getSize() * value);
    
    SL::Vector2d new_center = main_layers_[current_layer_].get_shape() / 2;

    new_center.x_ = main_layers_[current_layer_].get_shape().x_ > shape_.x_ ? new_center.x_ : shape_.x_ / 2; 
    new_center.y_ = main_layers_[current_layer_].get_shape().y_ > shape_.y_ ? new_center.y_ : shape_.y_ / 2; 
    
    for (int i = 0; i < main_layers_.size(); i++)
    {
        main_layers_[i].set_position(new_center - main_layers_[i].get_shape() / 2);
    }


    hidden_layer_->set_position(new_center - hidden_layer_->get_shape() / 2);

    reset_global_shape();
}

void Canvas::set_image(const std::string &path_image)
{
    Image image(path_image);
    set_image(image);
}

void Canvas::ConfigureSurface(Surface *surface)
{
    SL::Vector2d new_center = surface->get_shape() / 2;

    new_center.x_ = surface->get_shape().x_ > shape_.x_ ? new_center.x_ : shape_.x_ / 2; 
    new_center.y_ = surface->get_shape().y_ > shape_.y_ ? new_center.y_ : shape_.y_ / 2; 
    
    surface->set_position(new_center - surface->get_shape() / 2);
}

void Canvas::set_image(const Image &new_image)
{
    remove(&main_layers_[current_layer_]);
    remove(hidden_layer_);
    // #TODO
    
    main_layers_.clear();
    mementoList_main_.clear();

    main_layers_.push_back(Surface(new_image.getSize(), SL::Vector2d(0, 0), new_image));
    hidden_layer_ = new Surface(      new_image.getSize(),SL::Vector2d(0, 0), Image(new_image.getSize(), CUST_SL::Color(0, 0, 0, 0)));
    mementoList_main_.push_back(std::deque<Memento *>());
    
    SL::Vector2d new_center = main_layers_[current_layer_].get_shape() / 2;

    ConfigureSurface(&main_layers_[current_layer_]);
    ConfigureSurface(hidden_layer_);
    
    getInstance()->tool_manager_.set_surface(&getInstance()->main_layers_[current_layer_]);
    getInstance()->tool_manager_.set_second_surface(getInstance()->hidden_layer_);
    getInstance()->tool_manager_.set_mementoList(&getInstance()->mementoList_main_[current_layer_]);
    
    add(&main_layers_[current_layer_]);
    add(hidden_layer_);
}

Image *Canvas::get_image()
{
    return &main_layers_[current_layer_].image_;
}

void Canvas::add_tool(Tool *new_tool)
{
    tool_manager_.add(new_tool);
}       

Surface *Canvas::get_surface()
{
    return &main_layers_[current_layer_];
}

booba::Image *Image::getHiddenLayer()
{
    return &Canvas::getInstance()->hidden_layer_->image_;
}