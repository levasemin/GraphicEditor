#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "Texture.h"
#include "CompositeObject.h"
#include "Command.h"
#include "Button.h"
#include "SimpleCommand.h"
#include "Command.h"
#include "constants.h"
#include "TextureManager.h"

class VerticalScrollBar : public CompositeObject
{
public:
    
    float scroll_coeff_ = SCROLL_COEFF;
    
    Vector2d click_place_;
    
    Button up_button_;
    Button down_button_;    
    Button scroll_button_;
    Vector2d scroll_field_shape;

    Command<const Event&> *scroll_command_ = nullptr;
    
    VerticalScrollBar(Vector2d shape, Vector2d center):
        CompositeObject  (shape, center),
        scroll_coeff_(SCROLL_COEFF),
        click_place_(0, 0),
        up_button_    (Vector2d(shape.x_, shape.x_), Vector2d(shape.x_ / 2, shape.x_ / 2)),
        down_button_  (Vector2d(shape.x_, shape.x_), Vector2d(shape.x_ / 2, shape_.y_   - shape.x_ / 2)),
        scroll_button_(Vector2d(shape.x_, (shape.y_ - shape.x_ * 2) * SCROLL_COEFF),
                       Vector2d(shape.x_ / 2, shape.x_ + shape_.y_ * SCROLL_COEFF  / 2)),
        scroll_field_shape(shape_.x_, shape_.y_ - shape_.x_ * 2 - scroll_button_.get_shape().y_)
        {
            set_texture(Texture(Color((uint8_t)92, (uint8_t)92, (uint8_t)92)));
            
            TextureManager &texture_manager = TextureManager::getInstance();

            up_button_.    set_texture(Texture(Color((uint8_t)48, (uint8_t)48, (uint8_t)48)));
            down_button_.  set_texture(Texture(Color((uint8_t)48, (uint8_t)48, (uint8_t)48)));
            scroll_button_.set_texture(Texture(Color((uint8_t)48, (uint8_t)48, (uint8_t)48)));
            
            up_button_.  set_texture(texture_manager[TextureManager::Icon::UpArrow]);
            down_button_.set_texture(texture_manager[TextureManager::Icon::DownArrow]);

            add(&up_button_);
            add(&down_button_);
            add(&scroll_button_);
            
            down_button_.set_has_local_offset(false);
            up_button_.set_has_local_offset(false);
            
            up_button_.set_left_click    ((Command<const Event &> *) new SimpleCommand<VerticalScrollBar, const Event &>(this, &VerticalScrollBar::scroll_up));
            down_button_.set_left_click  ((Command<const Event &> *) new SimpleCommand<VerticalScrollBar, const Event &>(this, &VerticalScrollBar::scroll_down));
            scroll_button_.set_left_click((Command<const Event &> *) new SimpleCommand<VerticalScrollBar, const Event &>(this, &VerticalScrollBar::clicked_scroll_button));
        };

        VerticalScrollBar(const VerticalScrollBar &source) : CompositeObject(*(const CompositeObject *)&source),
            scroll_coeff_(source.scroll_coeff_),
            click_place_(0, 0),
            up_button_(source.up_button_),
            down_button_(source.down_button_),    
            scroll_button_(source.scroll_button_),
            scroll_field_shape(source.scroll_field_shape),
            scroll_command_(source.scroll_command_)
        {}

        VerticalScrollBar &operator =(const VerticalScrollBar &source)
        {
            CompositeObject::operator=(*(const CompositeObject *)&source);
            scroll_coeff_      = source.scroll_coeff_;
            click_place_       = Vector2d(0, 0);
            up_button_         = source.up_button_;
            down_button_       = source.down_button_;    
            scroll_button_     = source.scroll_button_;
            scroll_field_shape = source.scroll_field_shape;
            scroll_command_    = source.scroll_command_;

            return *this;
        }
        
        ~VerticalScrollBar()
        {
            delete up_button_.get_left_click();
            delete down_button_.get_left_click();
            delete scroll_button_.get_left_click();
        }

        void set_button(bool able)
        {
            Vector2d new_shape = up_button_.get_shape();
            
            if (!able)
            {
                new_shape = Vector2d(0, 0);    
            }

            else 
            {
                new_shape = Vector2d(shape_.x_, shape_.x_);
            }

            up_button_.set_shape(new_shape);
            down_button_.set_shape(new_shape);
            
            scroll_button_.set_center(Vector2d(scroll_button_.get_shape().x_ / 2, up_button_.get_shape().y_ + scroll_button_.get_shape().y_  / 2));
            scroll_field_shape.y_ = shape_.y_ - down_button_.get_shape().x_ * 2 - scroll_button_.get_shape().y_;
        }

        void set_scroll_button_size(const Vector2d &shape)
        {
            scroll_button_.set_shape(shape);
            scroll_button_.set_center(Vector2d(scroll_button_.get_shape().x_ / 2, up_button_.get_shape().y_ + scroll_button_.get_shape().y_  / 2));
            scroll_field_shape.y_ = shape_.y_ - down_button_.get_shape().x_ * 2 - scroll_button_.get_shape().y_;
            scroll_coeff_ = scroll_button_.get_shape().y_ / (shape_.y_ - down_button_.get_shape().y_ * 2);
        }


        void ScrollEvent(const Event &event) override
        {            
            if (point_belonging(event.Oleg_.sedata.pos))
            {
                Event new_event;
                new_event.type_ = EventType::ScrollbarMoved;
                new_event.Oleg_.smedata.value = (-event.Oleg_.sedata.value + local_offset_.y_) / scroll_field_shape.y_;
                new_event.Oleg_.smedata.id    = (int64_t)&down_button_;
                scroll_bar(new_event);
            }
        }

        void scroll_bar(const Event &event)
        {
            Event new_event = event;
            new_event.Oleg_.smedata.value = new_event.Oleg_.smedata.value < 0 ? 0 : new_event.Oleg_.smedata.value;
            new_event.Oleg_.smedata.value = new_event.Oleg_.smedata.value > 1 ? 1 : new_event.Oleg_.smedata.value;
            
            Vector2d offset = Vector2d(0, scroll_field_shape.y_);
            offset *= event.Oleg_.smedata.value;

            offset.x_ = offset.x_ >= 0 ? offset.x_ : 0;
            offset.y_ = offset.y_ >= 0 ? offset.y_ : 0;
            
            Vector2d max_offset = Vector2d(0, shape_.y_ - up_button_.get_shape().y_ * 2 - scroll_button_.get_shape().y_);
            offset.x_ = offset.x_ <= max_offset.x_ ? offset.x_ : max_offset.x_;
            offset.y_ = offset.y_ <= max_offset.y_ ? offset.y_ : max_offset.y_;
            
            set_local_offset(offset);

            if (scroll_command_)
            {
                scroll_command_->Execute(new_event);
            }
        }   

        void MoveMouseEvent (const Event &event) override
        {
            if (scroll_button_.is_left_clicked_)
            {   
                Event new_event;

                new_event.type_ = EventType::ScrollbarMoved;
                new_event.Oleg_.smedata.value = (event.Oleg_.motion.pos.y_ - click_place_.y_) / scroll_field_shape.y_ + local_offset_.y_ / scroll_field_shape.y_;
                new_event.Oleg_.smedata.id = (int64_t)&scroll_button_;
                
                scroll_bar(new_event);
                
                click_place_ = event.Oleg_.motion.pos;
            }
        };

        void scroll_up(const Event &event)
        {
            Event new_event;
            new_event.type_ = EventType::ScrollbarMoved;
            new_event.Oleg_.smedata.value = -scroll_coeff_ + local_offset_.y_ / scroll_field_shape.y_;
            new_event.Oleg_.smedata.id    = (int64_t)&up_button_;
            scroll_bar(new_event);
        }    

        void scroll_down(const Event &event)
        {
            Event new_event;
            new_event.type_ = EventType::ScrollbarMoved;
            new_event.Oleg_.smedata.value = scroll_coeff_ + local_offset_.y_ / scroll_field_shape.y_;
            new_event.Oleg_.smedata.id    = (int64_t)&down_button_;
            scroll_bar(new_event);
        }
        
        void ClickLeftEvent(const Event &event) override
        {
            if (point_belonging(event.Oleg_.mbedata.pos) &&
               !scroll_button_.point_belonging(event.Oleg_.mbedata.pos) &&
               !up_button_.point_belonging(event.Oleg_.mbedata.pos) &&
               !down_button_.point_belonging(event.Oleg_.mbedata.pos))
            {                
                Event new_event;

                new_event.type_ = EventType::ScrollbarMoved;
                new_event.Oleg_.smedata.value = (event.Oleg_.motion.pos.y_ - get_start_field().y_ - up_button_.get_shape().y_) / scroll_field_shape.y_ - scroll_coeff_ / 2;
                new_event.Oleg_.smedata.id = (int64_t)&scroll_button_;
                
                scroll_bar(new_event);
                
                click_place_ = event.Oleg_.motion.pos;
            }
            
            CompositeObject::ClickLeftEvent(event);
        }

        void clicked_scroll_button(const Event &event)
        {
            click_place_ = Vector2d((scroll_button_.get_start_field() + scroll_button_.get_end_field()) / 2);
        }

        void set_scroll_command(Command<const Event &> *new_command)
        {
            scroll_command_ = new_command;
        }
};