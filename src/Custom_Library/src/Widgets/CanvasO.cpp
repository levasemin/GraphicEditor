// #include "Canvas.hpp"
// #include "../HistoryManager/HistoryManager.hpp"

// Canvas *Canvas::Create(SL::Vector2d shape, SL::Vector2d position, ToolPalette *tool_palette)
// {
//     getInstance()->setShape(shape);
//     getInstance()->setPosition(position);
//     getInstance()->setTexture(SL::Texture(SL::Color::Grey));

//     getInstance()->tool_manager_ = ToolManager::getInstance();
//     getInstance()->main_layer_   = new Surface(SL::Vector2d(1, 1), SL::Vector2d(0, 0), SL::Image(SL::Texture(SL::Color::Grey)));
//     getInstance()->hidden_layer_ = new Surface(SL::Vector2d(1, 1), SL::Vector2d(0, 0), SL::Image());
//     getInstance()->add(getInstance()->main_layer_);
//     getInstance()->add(getInstance()->hidden_layer_);
    
//     getInstance()->tool_manager_.set_surface(getInstance()->main_layer_);
//     getInstance()->tool_manager_.set_second_surface(getInstance()->hidden_layer_);
    
//     if (tool_palette)
//     {
//         getInstance()->tool_manager_.set_tool_palette(tool_palette);
//     }
            
//     std::string dlPath = "./../Plugins_so";
    
//     for (const auto& curFile : std::filesystem::directory_iterator(dlPath)) 
//     {
//         if (curFile.is_directory()) 
//         {
//             continue;
//         }

//         void* dlHandler = dlopen(curFile.path().c_str(), RTLD_LAZY | RTLD_GLOBAL);
        
//         if (dlHandler) 
//         {
//             void (*init_func)()   = nullptr; 
//             *((void**)&init_func) = dlsym(dlHandler, "init_module");

//             (*init_func)();

//             // booba::GUID (*guid_func)()   = nullptr;
//             // *((void**)&guid_func) = dlsym(dlHandler, "getGUID");

//             // (*guid_func)();
//             // tool_manager_.add_guid(guid_func(), dlHandler);
//         }

//         else 
//         {
//             fprintf(stderr, "Unable to open lib: %s\n", dlerror());
//         }
//     }

//     return getInstance();
// }


// void Canvas::moveMouseEvent (const SL::Event &event)
// {
//     SL::Event new_event = event;

//     if (main_layer_->pointBelong(event.Oleg_.metion.pos))
//     {
//         new_event.type_ = SL::EventType::MouseMoved;
        
//         new_event.Oleg_.metion.pos  = event.Oleg_.metion.pos - main_layer_->getField().first - main_layer_->getPosition();
//         new_event.Oleg_.metion.pos /= zoom_;

//         tool_manager_.apply(&new_event);
//     }
// }

// void Canvas::clickLeftEvent(const SL::Event &event)
// {
//     SL::Event new_event = event;

//     if (main_layer_->pointBelong(event.Oleg_.mpedata.pos))
//     {
//         new_event.type_ = SL::EventType::MousePressed;
        
//         new_event.Oleg_.mpedata.pos  = event.Oleg_.mpedata.pos - main_layer_->getField().first - main_layer_->getPosition();
//         new_event.Oleg_.mpedata.pos /= zoom_;
//         new_event.Oleg_.mpedata.button = SL::MouseButton::Left;

//         tool_manager_.apply(&new_event);

//         is_left_clicked_ = true;
//     }           
// }

// void Canvas::clickRightEvent(const SL::Event &event)
// {
//     SL::Event new_event = event;

//     if (main_layer_->pointBelong(event.Oleg_.mpedata.pos))
//     {
//         new_event.type_ = SL::EventType::MousePressed;
        
//         new_event.Oleg_.mpedata.pos  = event.Oleg_.mpedata.pos - main_layer_->getField().first - main_layer_->getPosition();
//         new_event.Oleg_.mpedata.pos /= zoom_;
//         new_event.Oleg_.mpedata.button = SL::MouseButton::Right;

//         tool_manager_.apply(&new_event);

//         is_right_clicked_ = true;
//     }           
// }

// void Canvas::releaseLeftEvent (const SL::Event &event)
// {
//     SL::Event new_event = event;

//     new_event.type_ = SL::EventType::MouseReleased;
        
//     new_event.Oleg_.mredata.pos  = event.Oleg_.mredata.pos - main_layer_->getField().first - main_layer_->getPosition();
//     new_event.Oleg_.mredata.pos /= zoom_;
//     new_event.Oleg_.mredata.button = SL::MouseButton::Left;
//     tool_manager_.apply(&new_event);   


//     is_left_clicked_ = false;
// }

// void Canvas::releaseRightEvent (const SL::Event &event)
// {
//     SL::Event new_event = event;

//     new_event.type_ = SL::EventType::MouseReleased;
        
//     new_event.Oleg_.mredata.pos  = event.Oleg_.mredata.pos - main_layer_->getField().first - main_layer_->getPosition();
//     new_event.Oleg_.mredata.pos /= zoom_;
//     new_event.Oleg_.mredata.button = SL::MouseButton::Right;
//     tool_manager_.apply(&new_event);   


//     is_right_clicked_ = false;
// }

// void Canvas::pressKeyEvent(const SL::Event &event)
// {
//     if (event.Oleg_.kpedata.ctrl)
//     {            
//         switch(event.Oleg_.kpedata.code)
//         {
//             case SL::Key::Z:
//             {
//                 if (event.Oleg_.kpedata.shift)
//                 {
//                     tool_manager_.redo(main_layer_);
//                 }

//                 else
//                 {
//                     tool_manager_.undo(main_layer_);
//                 }

//                 break;
//             }

//             case SL::Key::Equal:
//             {
//                 set_zoom(zoom_ + 0.1f);

//                 break;
//             }

//             case SL::Key::Hyphen:
//             {
//                 set_zoom(zoom_ - 0.1f);

//                 break;
//             }

//             default:
//             {
//                 break;
//             }
//         }
//     }
// }

// void Canvas::set_zoom(float value)
// {
//     zoom_ = value;

//     main_layer_->setShape(main_layer_->image_.getSize() * value);
    
//     hidden_layer_->setShape(hidden_layer_->image_.getSize() * value);
    
//     SL::Vector2d new_center = main_layer_->getShape() / 2;

//     new_center.x_ = main_layer_->getShape().x_ > shape_.x_ ? new_center.x_ : shape_.x_ / 2; 
//     new_center.y_ = main_layer_->getShape().y_ > shape_.y_ ? new_center.y_ : shape_.y_ / 2; 
    
//     main_layer_->setPosition(new_center - main_layer_->getShape() / 2);

//     hidden_layer_->setPosition(new_center - hidden_layer_->getShape() / 2);
// }

// void Canvas::SetImage(const std::string &path_image)
// {
//     SL::Image image(path_image);
//     SetImage(image);
// }

// void Canvas::ConfigureSurface(Surface *surface)
// {
//     SL::Vector2d new_center = surface->getShape() / 2;

//     new_center.x_ = surface->getShape().x_ > shape_.x_ ? new_center.x_ : shape_.x_ / 2; 
//     new_center.y_ = surface->getShape().y_ > shape_.y_ ? new_center.y_ : shape_.y_ / 2; 
    
//     surface->setPosition(new_center - surface->getShape() / 2);
// }

// void Canvas::SetImage(const SL::Image &new_image)
// {
//     remove(main_layer_);
//     remove(hidden_layer_);
    
//     main_layer_   = new Surface(new_image.getSize(), SL::Vector2d(0, 0), new_image);
//     hidden_layer_ = new Surface(new_image.getSize(),SL::Vector2d(0, 0), SL::Image(new_image.getSize(), SL::Color(0, 0, 0, 0)));
    
//     SL::Vector2d new_center = main_layer_->getShape() / 2;

//     ConfigureSurface(main_layer_);
//     ConfigureSurface(hidden_layer_);
    
//     getInstance()->tool_manager_.set_surface(getInstance()->main_layer_);
//     getInstance()->tool_manager_.set_second_surface(getInstance()->hidden_layer_);
    
//     add(main_layer_);
//     add(hidden_layer_);
// }

// void Canvas::set_current_node(HistoryManager::Node *node)
// {
    
// }

// SL::Image *Canvas::getImage()
// {
//     return &main_layer_->image_;
// }

// Surface *Canvas::get_surface()
// {
//     return main_layer_;
// }

// booba::Image *SL::Image::getHiddenLayer()
// {
//     return &Canvas::getInstance()->hidden_layer_->image_;
// }