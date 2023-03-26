#pragma once

#include "Widget.h"

class Decorator : public Widget
{

protected:

public:
    Widget *widget_ = nullptr;

    Decorator (Widget *widget): Widget(),
        widget_(widget)
    {
    }

    Decorator(const Decorator &source) = default;
    Decorator &operator=(const Decorator &source) = default;

    void ClickLeftEvent      (const Event &event) override
    {
        widget_->ClickLeftEvent(event);
    }
    void ReleasedLeftEvent   (const Event &event) override
    {
        widget_->ReleasedLeftEvent(event);
    }              

    virtual void ClickRightEvent (const Event &event) override
    {
        widget_->ClickRightEvent(event);
    }
              
    void ReleasedRightEvent (const Event &event) override
    {
        widget_->ReleasedRightEvent(event);
    }              
    
    void MoveMouseEvent (const Event &event) override
    {
        widget_->MoveMouseEvent(event);
    }

    void PressKeyEvent (const Event &event) override
    {
        widget_->PressKeyEvent(event);
    }

    void ScrollEvent (const Event &event) override
    {
        widget_->ScrollEvent(event);
    }
    

    bool point_belonging(Vector2d point) const override
    {
        return widget_->point_belonging(point);
    }

    void draw() override
    {
        widget_->draw();
    }
    
    void remove(Widget *window) override
    {
        widget_->remove(window);
    }

    void add(Widget *window) override
    {
        widget_->add(window);
    }

    void display(Window *window) override
    {
        widget_->display(window);
    }


    Vector2d get_center() const override
    {
        return widget_->get_center();
    }
    void set_center(Vector2d center) override
    {
        widget_->set_center(center);
    }

    Vector2d get_shape() const override
    {
        return widget_->get_shape();
    }
    void set_shape(Vector2d shape) override
    {
        widget_->set_shape(shape);
    }

    Widget *get_parent() const override
    {
        return widget_->get_parent();
    }
    void set_parent(Widget *parent) override
    {
        widget_->set_parent(parent);
    }

    virtual Texture get_texture() const override
    {
        return widget_->get_texture();
    }
    virtual void set_texture(const Texture &texture) override
    {
        return widget_->set_texture(texture);
    }

    RenderTexture *get_render_texture() const override
    {
        return widget_->get_render_texture();   
    }
    void set_render_texture(RenderTexture *render_texture) override
    {
        widget_->set_render_texture(render_texture);
    }

    Vector2d get_indent() const override     
    {
        return widget_->get_indent();
    }
    void set_indent(Vector2d indent) override
    {
        widget_->set_indent(indent);
    }

    Vector2d get_global_shape() const override
    {
        return widget_->get_global_shape();
    }
    void set_global_offset(Vector2d offset) override
    {
        widget_->set_global_offset(offset);
    }

    Vector2d get_global_offset() const override
    {
        return widget_->get_global_offset();
    }
    void set_global_shape(Vector2d global_shape) override
    {
        widget_->set_global_shape(global_shape);
    }
   
    Vector2d get_local_offset() const override
    {
        return widget_->get_local_offset();
    }
    void set_local_offset(Vector2d offset) override
    {
        widget_->set_local_offset(offset);
    }

    bool get_has_local_offset() const override
    {
        return widget_->get_has_local_offset();
    }    
    void set_has_local_offset(bool has) override
    {
        widget_->set_has_local_offset(has);
    }

    Vector2d get_start_field() const override          
    {
        return widget_->get_start_field(); 
    }
    Vector2d get_end_field() const override          
    {
        return widget_->get_end_field(); 
    }

    std::vector<Widget *> get_children() const override
    {
        return widget_->get_children();
    }
    void set_children(std::vector<Widget *> children) override
    {
        widget_->set_children(children);
    }

    virtual ~Decorator () {};
};