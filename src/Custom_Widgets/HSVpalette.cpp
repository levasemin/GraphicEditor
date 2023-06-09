// #include "HSVpalette.h"

// 

// HSVpalette::HSVpalette(SL::Vector2d shape, SL::Vector2d position) : SL::Object(shape, position),
//     color_(360.f, 0.f, 0.f),
//     palette_(shape),
//     scroll_bar_(SL::Vector2d(20, shape.y_), SL::Vector2d(position_.x_ + shape.x_ + 10, position_.y_), 0, 360)
// {   
//     scroll_bar_.set_scroll_command((Command<const Event &> *) new SL::SimpleCommand<HSVpalette, const Event&>(this, &HSVpalette::change_H));
//     scroll_bar_.set_scroll_button_size(SL::Vector2d(20, 4));
//     scroll_bar_.set_button(false);
//     Image scroll_bar_image(scroll_bar_.get_shape());
    
//     for (float y = 0; y < scroll_bar_image.getSize().y_; y++)
//     {
//         for (float x = 0; x < scroll_bar_image.getSize().x_; x++)
//         {
//             scroll_bar_image.setPixel(SL::Vector2d(x, y), Color((1.f - y / scroll_bar_.get_shape().y_) * 360.f, 1.f, 1.f));
//         }
//     }

//     scroll_bar_.set_texture(scroll_bar_image.getTexture());
// }

// HSVpalette::HSVpalette(const HSVpalette &source) : SL::Object(*(const SL::Object *)&source),
//     color_(source.color_),
//     palette_(source.palette_),
//     scroll_bar_(source.scroll_bar_),
//     palette_command_(source.palette_command_)
//     {}

// HSVpalette &HSVpalette::operator=(const HSVpalette &source)
// {
//     SL::Object::operator=(*(const SL::Object *)&source);
//     color_           = source.color_;
//     palette_         = source.palette_;
//     scroll_bar_      = source.scroll_bar_;
//     palette_command_ = source.palette_command_;

//     return *this;
// }

// void HSVpalette::set_command(Command<const Color&> *command)
// {
//     palette_command_ = command;
// }

// void HSVpalette::draw() 
// {   
//     scroll_bar_.draw();

//     for (float y = 0; y < shape_.y_; y++)
//     {
//         for (float x = 0; x < shape_.x_; x++)
//         {
//             if ((int)(color_.get_s() * shape_.x_) == (int)x || (int)((1 - color_.get_v()) * shape_.y_) == (int)y)
//             {
//                 palette_.setPixel(SL::Vector2d(x, y), Color::White);
//             }

//             else
//             {
//                 palette_.setPixel(SL::Vector2d(x, y), Color(color_.get_h(), x / shape_.x_, 1.f - y / shape_.y_));
//             }
//         }
//     }

//     Sprite sprite(shape_, palette_.getTexture());
//     render_texture_->clear();
//     render_texture_->draw(sprite);
//     render_texture_->display();
    
//     scroll_bar_.draw();
//     SL::Object::draw();
// }

// void HSVpalette::set_color(const Color &color)
// {
//     color_ = color;
//     Event new_event;
//     new_event.type_ = EventType::ScrollbarMoved;
//     new_event.Oleg_.smedata.value = 1.f - color_.get_h() / 360.f;
//     scroll_bar_.scroll_bar(new_event);
// }

// void HSVpalette::change_H(const Event &event)
// {
//     color_.set_h((1.f - event.Oleg_.smedata.value) * 360.f);

//     if (palette_command_)
//     {
//         palette_command_->Execute(color_);
//     }
// }

// void HSVpalette::ClickLeftEvent (const Event &event) 
// {
//     scroll_bar_.ClickLeftEvent(event);
    
//     if (point_belonging(event.Oleg_.mbedata.pos))
//     {
//         clicked_ = true;

//         color_.set_s((event.Oleg_.mbedata.pos.x_ - get_start_field().x_) / shape_.x_);
//         color_.set_v(1.f - (event.Oleg_.mbedata.pos.y_ - get_start_field().y_) / shape_.y_);

//         if (palette_command_)
//         {
//             palette_command_->Execute(color_);
//         }
//     }

//     else
//     {
//         clicked_ = false;
//     }
// }

// void HSVpalette::MoveMouseEvent(const Event &event) 
// {
//     scroll_bar_.MoveMouseEvent(event);
    
//     if (clicked_)
//     {
//         if (point_belonging(event.Oleg_.motion.pos))
//         {
//             color_.set_s((event.Oleg_.motion.pos.x_ - get_start_field().x_) / shape_.x_);
//             color_.set_v(1.f - (event.Oleg_.motion.pos.y_ - get_start_field().y_) / shape_.y_);
            
//             if (palette_command_)
//             {
//                 palette_command_->Execute(color_);
//             }
//         }
//     }
// }

// void HSVpalette::ReleasedLeftEvent (const Event &event) 
// {
//     clicked_ = false;
    
//     scroll_bar_.ReleasedLeftEvent(event);
//     SL::Object::ReleasedLeftEvent(event);
// }              

//  void HSVpalette::ClickRightEvent (const Event &event) 
// {
//     scroll_bar_.ClickRightEvent(event);
//     SL::Object::ClickRightEvent(event);
// }           

// void HSVpalette::ReleasedRightEvent (const Event &event) 
// {   
//     scroll_bar_.ReleasedRightEvent(event);
//     SL::Object::ReleasedRightEvent(event);
// }              

// void HSVpalette::PressKeyEvent (const Event &event) 
// {
//     scroll_bar_.MoveMouseEvent(event);
//     SL::Object::PressKeyEvent(event);
// }

// void HSVpalette::set_global_offset(SL::Vector2d offset) 
// {
//     scroll_bar_.set_global_offset(offset);
//     SL::Object::set_global_offset(offset);
// }

// void HSVpalette::display(Window *window) 
// {
//     scroll_bar_.display(window);
//     SL::Object::display(window);
// }

// void HSVpalette::set_parent(SL::Widget *parent_widget) 
// {
//     scroll_bar_.set_parent(parent_widget);
//     SL::Object::set_parent(parent_widget);
// }

// void HSVpalette::ScrollEvent (const Event &event)
// {
//     scroll_bar_.ScrollEvent(event);
//     SL::Object::ScrollEvent(event);    
// }