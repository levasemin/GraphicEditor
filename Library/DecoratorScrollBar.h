#pragma once

#include "Decorator.h"
#include "RenderTexture.h"
#include "VerticalScrollBar.h"
#include "HorizontalScrollBar.h"

class DecoratorScrollBar : public Decorator
{
public:
    VerticalScrollBar scroll_bar_vertical_;
    HorizontalScrollBar scroll_bar_horizontal_;

    bool scroll_bar_horizontal_able_ = true;
    bool scroll_bar_vertical_able_   = true;

    DecoratorScrollBar(Widget *widget) : Decorator(widget),
        scroll_bar_vertical_(Vector2d(20, widget->get_shape().y_), Vector2d(widget->get_center().x_ + widget->get_shape().x_ / 2 + 10, widget->get_center().y_)),
        scroll_bar_horizontal_(Vector2d(widget->get_shape().x_, 20), Vector2d(widget->get_center().x_, widget->get_center().y_ + widget->get_shape().y_ / 2 + 10))
    {   
        scroll_bar_vertical_.set_scroll_command ((Command<const Event &> *) new SimpleCommand<DecoratorScrollBar, const Event &> (this, &DecoratorScrollBar::ScrollVerticalWidget));
        scroll_bar_horizontal_.set_scroll_command ((Command<const Event &> *) new SimpleCommand<DecoratorScrollBar, const Event &> (this, &DecoratorScrollBar::ScrollHorizontalWidget));        
    }


    void ScrollEvent(const Event &event) override
    {
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.ScrollEvent(event);
        }

        if (point_belonging(event.Oleg_.sedata.pos))
        {               
            if (doublecmp(widget_->get_global_shape().y_, widget_->get_shape().y_))
            {
                Event new_event = event;

                new_event.Oleg_.smedata.value = (float)( event.Oleg_.sedata.value * 2 / (widget_->get_global_shape().y_ - widget_->get_shape().y_) +
                                            widget_->get_local_offset().y_ / (widget_->get_global_shape().y_ - widget_->get_shape().y_));
                new_event.Oleg_.smedata.value *= -1;
                
                if (scroll_bar_vertical_able_)
                {
                    scroll_bar_vertical_.scroll_bar(new_event);
                }
            }
        }
    }

    void ScrollVerticalWidget(const Event &event)
    {
        Vector2d offset = get_local_offset();
        offset.y_ = - event.Oleg_.smedata.value * (widget_->get_global_shape().y_ - widget_->get_shape().y_);
        widget_->set_local_offset(offset);
    }

    void ScrollHorizontalWidget(const Event &event)
    {
        Vector2d offset = get_local_offset();
        offset.x_ = - event.Oleg_.smedata.value * (widget_->get_global_shape().x_ - widget_->get_shape().x_);
        widget_->set_local_offset(offset);
    }

    void draw() override
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.draw();
        }

        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.draw();
        }

        widget_->draw();
    }

    void ClickLeftEvent (const Event &event) override
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.ClickLeftEvent(event);
        }
        
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.ClickLeftEvent(event);
        }

        widget_->ClickLeftEvent(event);
    }

    void ReleasedLeftEvent (const Event &event) override
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.ReleasedLeftEvent(event);
        }
        
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.ReleasedLeftEvent(event);
        }

        widget_->ReleasedLeftEvent(event);
    }            
    
    void MoveMouseEvent (const Event &event) override
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.MoveMouseEvent(event);
        }
        
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.MoveMouseEvent(event);
        }

        widget_->MoveMouseEvent(event);
    }

    void set_global_offset(Vector2d offset) override
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.set_global_offset(offset);
        }
        
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.set_global_offset(offset);
        }

        widget_->set_global_offset(offset);
    }

    void display(Window *window) override
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.display(window);
        }
        
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.display(window);
        }

        widget_->display(window);
    }

    void set_parent(Widget *parent_widget) override
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.set_parent(parent_widget);
        }
        
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.set_parent(parent_widget);
        }

        widget_->set_parent(parent_widget);
    }
};