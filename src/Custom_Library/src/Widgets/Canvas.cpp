#include "Canvas.hpp"
#include "ToolManager.hpp"

namespace CUST_SL
{
    class ToolManager;

    Canvas::Canvas(SL::Vector2d shape, SL::Vector2d position, const SL::Texture &texture):
        SL::CompositeObject(shape, position, texture),
        main_layer_(nullptr),
        hidden_layer_(nullptr),
        zoom_(1.f)
    {

    }

    Canvas::Canvas(const Canvas &source):
        SL::CompositeObject(*(SL::CompositeObject *)&source)
    {
        *main_layer_ = *source.main_layer_;
        *hidden_layer_ = *source.hidden_layer_;
    }

    Canvas &Canvas::operator=(const Canvas &source)
    {
        SL::CompositeObject::operator=(*(SL::CompositeObject *)&source);
        *main_layer_ = *source.main_layer_;
        *hidden_layer_ = *source.hidden_layer_;

        return *this;
    }

    Canvas::~Canvas()
    {
        if (main_layer_ != nullptr)
        {
            delete main_layer_;
        }

        if (hidden_layer_ != nullptr)
        {
            delete hidden_layer_;
        }
    }

    void Canvas::recoverySecondLayer()
    {
        if (hidden_layer_)
        {
            hidden_layer_->getImage()->create(hidden_layer_->getImage()->getSize(), SL::Color(0, 0, 0, 0));
        }
    }

    void Canvas::set_zoom(float value)
    {
        if (main_layer_)
        {
            zoom_ = value;

            main_layer_->setShape(main_layer_->getImage()->getSize() * value);
            
            hidden_layer_->setShape(hidden_layer_->getImage()->getSize() * value);
            
            SL::Vector2d new_center = main_layer_->getShape() / 2;

            new_center.x_ = main_layer_->getShape().x_ > getShape().x_ ? new_center.x_ : getShape().x_ / 2; 
            new_center.y_ = main_layer_->getShape().y_ > getShape().y_ ? new_center.y_ : getShape().y_ / 2; 
            
            main_layer_->setPosition(new_center - main_layer_->getShape() / 2);

            hidden_layer_->setPosition(new_center - hidden_layer_->getShape() / 2);
        }
    }


    void Canvas::moveMouseEvent(const SL::Event &event)
    {
        if (pointBelong(event.Oleg_.metion.pos) && main_layer_)
        {
            SL::Event new_event = event;

            new_event.type_ = SL::EventType::MouseMoved;
            
            new_event.Oleg_.metion.pos  = event.Oleg_.metion.pos - getField().first - main_layer_->getPosition();
            new_event.Oleg_.metion.pos /= zoom_;

            TOOL_SL::ToolManager::getInstance().apply(getImage(), new_event);
        }
    }

    void Canvas::clickLeftEvent(const SL::Event &event)
    {
        if (pointBelong(event.Oleg_.mpedata.pos) && main_layer_)
        {
            SL::Event new_event = event;

            new_event.type_ = SL::EventType::MousePressed;
            
            new_event.Oleg_.mpedata.pos  = event.Oleg_.mpedata.pos - getField().first - main_layer_->getPosition();
            new_event.Oleg_.mpedata.pos /= zoom_;
            new_event.Oleg_.mpedata.button = SL::MouseButton::Left;

            TOOL_SL::ToolManager::getInstance().apply(getImage(), new_event);
        }           
    }

    void Canvas::releaseLeftEvent (const SL::Event &event)
    {
        if (main_layer_)
        {
            SL::Event new_event = event;

            new_event.type_ = SL::EventType::MouseReleased;
                
            new_event.Oleg_.mredata.pos  = event.Oleg_.mredata.pos - getField().first - main_layer_->getPosition();
            new_event.Oleg_.mredata.pos /= zoom_;
            new_event.Oleg_.mredata.button = SL::MouseButton::Left;

            TOOL_SL::ToolManager::getInstance().apply(getImage(), new_event);
        }
    }

    void Canvas::clickRightEvent(const SL::Event &event)
    {
        if (pointBelong(event.Oleg_.mpedata.pos) && main_layer_)
        {
            SL::Event new_event = event;

            new_event.type_ = SL::EventType::MousePressed;
            
            new_event.Oleg_.mpedata.pos  = event.Oleg_.mpedata.pos - getField().first - main_layer_->getPosition();
            new_event.Oleg_.mpedata.pos /= zoom_;
            new_event.Oleg_.mpedata.button = SL::MouseButton::Right;

            TOOL_SL::ToolManager::getInstance().apply(getImage(), new_event);
        }           
    }

    void Canvas::releaseRightEvent (const SL::Event &event)
    {
        if (main_layer_)
        {
            SL::Event new_event = event;

            new_event.type_ = SL::EventType::MouseReleased;
                
            new_event.Oleg_.mredata.pos  = event.Oleg_.mredata.pos - getField().first - main_layer_->getPosition();
            new_event.Oleg_.mredata.pos /= zoom_;
            new_event.Oleg_.mredata.button = SL::MouseButton::Right;
            
            TOOL_SL::ToolManager::getInstance().apply(getImage(), new_event);
        }
    }


    void Canvas::pressKeyEvent(const SL::Event &event)
    {
        if (event.Oleg_.kpedata.ctrl)
        {            
            switch(event.Oleg_.kpedata.code)
            {
                case SL::Key::Z:
                {
                    if (event.Oleg_.kpedata.shift)
                    {
                        // ToolManager::getInstance().redo(main_layer_);
                    }

                    else
                    {
                        // ToolManager::getInstance().undo(main_layer_);
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

    void Canvas::ConfigureSurface(Surface *surface)
    {
        SL::Vector2d new_center = surface->getShape() / 2;

        new_center.x_ = surface->getShape().x_ > getShape().x_ ? new_center.x_ : getShape().x_ / 2; 
        new_center.y_ = surface->getShape().y_ > getShape().y_ ? new_center.y_ : getShape().y_ / 2; 
        
        surface->setPosition(new_center - surface->getShape() / 2);
    }

    void Canvas::setImage(const SL::Image &new_image)
    {
        if (main_layer_)
        {
            remove(main_layer_);
            delete main_layer_;
        }
        
        if (hidden_layer_)
        {
            remove(hidden_layer_);
            delete hidden_layer_;
        }
        
        main_layer_   = new Surface(new_image.getSize(), SL::Vector2d(0, 0), new_image);
        hidden_layer_ = new Surface(new_image.getSize(),SL::Vector2d(0, 0), SL::Image(new_image.getSize(), SL::Color(0, 0, 0, 0)));
        
        SL::Vector2d new_center = main_layer_->getShape() / 2;

        ConfigureSurface (main_layer_);
        ConfigureSurface (hidden_layer_);
            
        add (main_layer_);
        add (hidden_layer_);

        setShape(new_image.getSize());
    }

    SL::Image *Canvas::getHiddenImage()
    {
        return hidden_layer_->getImage();
    }


    SL::Image *Canvas::getImage()
    {
        return main_layer_->getImage();
    }
}