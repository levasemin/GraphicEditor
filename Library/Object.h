#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "Window.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "Sprite.h"
#include "Vector2d.h"
#include "Widget.h"
#include "functions.h"

class Object : public Widget
{
    
protected:
    Vector2d shape_;
    Vector2d center_;
    Texture texture_;
    Sprite sprite_;
    Vector2d local_offset_;
    Vector2d global_offset_;
    
    RenderTexture *render_texture_ = nullptr;
    Widget *parent_ = nullptr;

    bool has_local_offset_ = true;

public:

    Object(Vector2d shape, Vector2d center, const Texture &texture = Texture(Color::White)): Widget(),
        shape_(shape),
        center_(center),    
        texture_(texture),
        sprite_(shape, texture, 0),
        local_offset_(0, 0),
        global_offset_(0, 0)
        {
            if (!doublecmp(center.x_, -1.f) && !doublecmp(center.y_, -1))
            {
                center_ = shape_ / 2;
            }
            
            render_texture_ = new RenderTexture(shape);
            
            sprite_.setTexture(texture);

            render_texture_->draw(sprite_);
        };

    Object(const Object& source):
        shape_(source.shape_),
        center_(source.center_),    
        texture_(source.texture_),
        sprite_(source.sprite_),
        local_offset_(source.local_offset_),
        global_offset_(source.global_offset_)
    {
        render_texture_ = new RenderTexture(shape_);
        *render_texture_ = *source.render_texture_;
    }

    Object &operator=(const Object& source)
    {
        shape_         = source.shape_;
        center_        = source.center_;    
        texture_       = source.texture_;
        sprite_        = source.sprite_;
        local_offset_  = source.local_offset_;
        global_offset_ = source.global_offset_;

        render_texture_ = new RenderTexture(shape_);
        *render_texture_ = *source.render_texture_;
        
        return *this;
    }
    
    virtual void ClickLeftEvent      (const Event &event) override {}
    virtual void ReleasedLeftEvent   (const Event &event) override {}              

    virtual void ClickRightEvent     (const Event &event) override {}
    virtual void ReleasedRightEvent  (const Event &event) override {}              
    
    virtual void MoveMouseEvent      (const Event &event) override {}

    virtual void PressKeyEvent       (const Event &event) override {}

    virtual void ScrollEvent         (const Event &event) override {}

    ~Object () override 
    {
        delete render_texture_;
    }

    bool point_belonging(Vector2d point) const override
    {
        Vector2d start_field = get_start_field();
        Vector2d end_field   = get_end_field();

        return start_field.x_ < point.x_ && point.x_ < end_field.x_ &&
               start_field.y_ < point.y_ && point.y_ < end_field.y_;
    }

    void draw() override
    {   
        render_texture_->display();
        sprite_.setTexture(render_texture_->getTexture());

        if (parent_)
        {
            sprite_.setPosition(parent_->get_local_offset() * has_local_offset_ + center_ - shape_ / 2);
            parent_->get_render_texture()->draw(sprite_);
        }
    }

    void remove(Widget *window) override
    {
        std::logic_error exception("removing child to widget\n");
        throw exception;
    }

    void add(Widget *window) override
    {
        std::logic_error exception("adding child to widget\n");
        throw exception;
    }

    void display(Window *window) override
    {
        render_texture_->display();
        window->draw(sprite_);
        window->display();
        window->clear();
    }


    Vector2d get_center() const override
    {
        return center_; 
    }
    void set_center(Vector2d center) override
    {
        center_ = center; 
    }

    Vector2d get_shape() const override
    {
        return shape_; 
    }
    
    void set_shape (Vector2d shape) override
    {
        shape_  = shape; 
        
        render_texture_->clear();
        sprite_.set_shape(shape);
        
        if (doublecmp(shape.x_, 0.f) && doublecmp(shape.y_, 0.f))
        {
            render_texture_->create(shape);
        }

        render_texture_->draw(sprite_);
    }

    Widget  *get_parent() const override
    {
        return parent_; 
    }
    void set_parent(Widget *parent) override
    { 
        parent_ = parent; 
    }

    virtual Texture get_texture() const override
    {
        return texture_;
    }

    virtual void set_texture(const Texture &texture) override
    {
        texture_ = texture;

        Sprite sprite(shape_, texture_);
        sprite_ = sprite;

        render_texture_->draw(sprite_);
    }

    RenderTexture *get_render_texture() const override
    {
        return render_texture_; 
    }
    void set_render_texture(RenderTexture *render_texture) override
    {
        render_texture_ = render_texture;
    }

    Vector2d get_indent() const override { return Vector2d(0, 0); }
    void set_indent(Vector2d indent) override {}

    Vector2d get_global_shape() const override
    {
        return shape_; 
    }
    void set_global_shape(Vector2d global_shape) override
    {
        shape_ = global_shape; 
    }

    Vector2d get_global_offset() const override
    {
        return global_offset_; 
    }   
    void set_global_offset(Vector2d offset) override
    {
        global_offset_ = offset; 
    }

    Vector2d get_local_offset() const override
    {
        return local_offset_;
    }

    void set_local_offset(Vector2d diff_offset) override
    { 
    }
    
    bool get_has_local_offset () const override
    {
        return has_local_offset_;
    }
    void set_has_local_offset(bool has) override
    {
        has_local_offset_ = has;
    }
    
    Vector2d get_start_field() const override
    {
        Vector2d start_field = center_ - shape_ / 2 + global_offset_;
        Vector2d down_limit  = parent_ != nullptr ? parent_->get_start_field() : center_ - shape_ / 2;

        start_field.x_ = start_field.x_ < down_limit.x_ ? down_limit.x_ : start_field.x_;
        start_field.y_ = start_field.y_ < down_limit.y_ ? down_limit.y_ : start_field.y_;

        return start_field;
    }
    
    Vector2d get_end_field() const override
    {
        Vector2d end_field = center_ + shape_ / 2 + global_offset_;
        Vector2d hight_limit = parent_ != nullptr ? parent_->get_end_field()   : center_ + shape_ / 2;

        end_field.x_ = end_field.x_ > hight_limit.x_ ? hight_limit.x_ : end_field.x_;
        end_field.y_ = end_field.y_ > hight_limit.y_ ? hight_limit.y_ : end_field.y_;

        return end_field;
    }

    std::vector<Widget *> get_children() const override
    {
        // std::logic_error exception("try getting children from object\n");
        // throw exception;
        return {};
    }
    void set_children(std::vector<Widget *> children) override
    {
        // std::logic_error exception("try setting children to object\n");
        // throw exception;
    }
};