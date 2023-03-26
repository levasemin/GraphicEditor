#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#pragma once

#include "Texture.h"
#include "CompositeObject.h"
#include "Command.h"
#include "Button.h"
#include "SimpleCommand.h"
#include "Command.h"
#include "constants.h"
#include "TextureManager.h"

class HorizontalScrollBar : public CompositeObject
{
protected:
    Button left_button_;
    Button right_button_;    
    Button scroll_button_;
    Vector2d scroll_field_shape;

public:
    Command<const Event&> *scroll_command_ = nullptr;

    float scroll_coeff_ = SCROLL_COEFF;
    
    Vector2d click_place_;
    
    HorizontalScrollBar(Vector2d shape, Vector2d center):
        CompositeObject  (shape, center),
        left_button_    (Vector2d(shape.y_, shape.y_), Vector2d(shape.y_ / 2, shape.y_ / 2)),
        right_button_  (Vector2d(shape.y_, shape.y_), Vector2d(shape.x_   - shape.y_ / 2, shape.y_ / 2)),
        scroll_button_(Vector2d((shape.x_ - shape.y_ * 2) * SCROLL_COEFF, shape.y_),
                       Vector2d(left_button_.get_shape().x_ + shape.x_ * SCROLL_COEFF  / 2, shape.y_ / 2)),
        scroll_field_shape(shape.x_ - left_button_.get_shape().x_ - right_button_.get_shape().x_ - scroll_button_.get_shape().x_, shape.y_),
        click_place_(0.f, 0.f)
        {
            set_texture(Texture(Color((uint8_t)92, (uint8_t)92, (uint8_t)92)));
            
            TextureManager &texture_manager = TextureManager::getInstance();

            left_button_.set_texture  (Texture(Color((uint8_t)48, (uint8_t)48, (uint8_t)48)));
            right_button_.set_texture (Texture(Color((uint8_t)48, (uint8_t)48, (uint8_t)48)));
            scroll_button_.set_texture(Texture(Color((uint8_t)48, (uint8_t)48, (uint8_t)48)));
            
            left_button_.set_texture (texture_manager[TextureManager::Icon::LeftArrow]);
            right_button_.set_texture(texture_manager[TextureManager::Icon::RightArrow]);

            add(&left_button_);
            add(&right_button_);
            add(&scroll_button_);
            
            right_button_.set_has_local_offset(false);
            left_button_.set_has_local_offset(false);
            
            left_button_.set_left_click    ((Command<const Event &> *) new SimpleCommand<HorizontalScrollBar, const Event &>(this, &HorizontalScrollBar::scroll_up));
            right_button_.set_left_click  ((Command<const Event &> *) new SimpleCommand<HorizontalScrollBar, const Event &>(this, &HorizontalScrollBar::scroll_down));
            scroll_button_.set_left_click((Command<const Event &> *) new SimpleCommand<HorizontalScrollBar, const Event &>(this, &HorizontalScrollBar::clicked_scroll_button));
        };

        HorizontalScrollBar(const HorizontalScrollBar &source) : CompositeObject(*(const CompositeObject *)&source),
            left_button_(source.left_button_),
            right_button_(source.right_button_),
            scroll_button_(source.scroll_button_),
            scroll_field_shape(source.scroll_field_shape),
            click_place_(0.f, 0.f)
        {}

        HorizontalScrollBar &operator=(const HorizontalScrollBar &source)
        {
            CompositeObject::operator=(*(const CompositeObject *)&source);
            left_button_         = source.left_button_;
            right_button_       = source.right_button_;
            scroll_button_     = source.scroll_button_;
            scroll_field_shape = source.scroll_field_shape;
            click_place_ = Vector2d(0.f, 0.f);

            return *this;
        }

        void set_button(bool able)
        {
            Vector2d new_shape = left_button_.get_shape();
            
            if (!able)
            {
                new_shape = Vector2d(0, 0);    
            }

            else 
            {
                new_shape = Vector2d(shape_.y_, shape_.y_);
            }

            set_up_right_button_shape(new_shape);
        }

        void set_scroll_button_shape(const Vector2d &shape)
        {
            scroll_button_.set_shape(shape);
            scroll_button_.set_center(Vector2d(left_button_.get_shape().x_ + scroll_button_.get_shape().x_  / 2, scroll_button_.get_shape().y_ / 2));
            scroll_field_shape = Vector2d(shape_.x_ - left_button_.get_shape().x_ - right_button_.get_shape().x_ - scroll_button_.get_shape().x_, shape_.y_);
            scroll_coeff_ = scroll_button_.get_shape().x_ / (shape_.x_ - right_button_.get_shape().x_ * 2);
        }

        void set_up_right_button_shape(const Vector2d &shape)
        {
            left_button_.set_shape(shape);
            right_button_.set_shape(shape);
            
            scroll_button_.set_center(Vector2d(shape_.y_ / 2, left_button_.get_shape().x_ + shape_.x_ * SCROLL_COEFF  / 2));
            scroll_field_shape = Vector2d(shape_.x_ - left_button_.get_shape().x_ - right_button_.get_shape().x_ - scroll_button_.get_shape().x_, shape_.y_);
        }

        virtual void scroll_bar(const Event &event)
        {
            Event new_event = event;
            new_event.Oleg_.smedata.id = uint64_t(this);
            new_event.Oleg_.smedata.value = new_event.Oleg_.smedata.value < 0 ? 0 : new_event.Oleg_.smedata.value;
            new_event.Oleg_.smedata.value = new_event.Oleg_.smedata.value > 1 ? 1 : new_event.Oleg_.smedata.value;
            
            Vector2d offset = Vector2d(scroll_field_shape.x_, 0);
            offset *= event.Oleg_.smedata.value;

            offset.x_ = offset.x_ >= 0 ? offset.x_ : 0;
            offset.y_ = offset.y_ >= 0 ? offset.y_ : 0;
            
            Vector2d max_offset = Vector2d(shape_.x_ - left_button_.get_shape().x_ * 2 - scroll_button_.get_shape().x_, 0);
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
                new_event.Oleg_.smedata.id = (uint64_t)this;
                new_event.Oleg_.smedata.value = (event.Oleg_.motion.pos.x_ - click_place_.x_) / scroll_field_shape.x_ + local_offset_.x_ / scroll_field_shape.x_;
                new_event.Oleg_.smedata.id = (int64_t)&scroll_button_;
                
                scroll_bar(new_event);
                
                click_place_ = event.Oleg_.motion.pos;
            }
        };

        void scroll_up(const Event &event)
        {
            Event new_event;
            new_event.type_ = EventType::ScrollbarMoved;
            new_event.Oleg_.smedata.value = -scroll_coeff_ + local_offset_.x_ / scroll_field_shape.x_;
            new_event.Oleg_.smedata.id    = (int64_t)&left_button_;
            scroll_bar(new_event);
        }    

        void scroll_down(const Event &event)
        {
            Event new_event;
            new_event.type_ = EventType::ScrollbarMoved;
            new_event.Oleg_.smedata.value = scroll_coeff_ + local_offset_.x_ / scroll_field_shape.x_;
            new_event.Oleg_.smedata.id    = (int64_t)&right_button_;
            scroll_bar(new_event);
        }
        
        void ClickLeftEvent(const Event &event) override
        {
            if (point_belonging(event.Oleg_.mbedata.pos) &&
               !scroll_button_.point_belonging(event.Oleg_.mbedata.pos) &&
               !left_button_.point_belonging(event.Oleg_.mbedata.pos) &&
               !right_button_.point_belonging(event.Oleg_.mbedata.pos))
            {                
                Event new_event;

                new_event.type_ = EventType::ScrollbarMoved;
                new_event.Oleg_.smedata.id = (int64_t)&scroll_button_;
                new_event.Oleg_.smedata.value = (event.Oleg_.motion.pos.x_ - get_start_field().x_ - left_button_.get_shape().x_) / scroll_field_shape.x_ - scroll_coeff_ / 2;
                
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

        ~HorizontalScrollBar() override {}
};