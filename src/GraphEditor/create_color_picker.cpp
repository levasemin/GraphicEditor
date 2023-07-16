#include "GraphEditor.hpp"

ColorPicker *create_color_picker()
{
    SL::TextureManager &texture_manager = SL::TextureManager::getInstance();
    ;
    SL::Button *foreground_button = new SL::Button(SL::Vector2d(40, 40), SL::Vector2d(120, 335), SL::Texture(CUST_SL::Color::White));


    SL::Button *background_button = new SL::Button(SL::Vector2d(40, 40), SL::Vector2d(160, 375), SL::Texture(CUST_SL::Color::Black));
    SL::Button *swap_button       = new SL::Button(SL::Vector2d(20, 20), SL::Vector2d(160, 355), SL::Texture(CUST_SL::Color(CUST_SL::Color::Color::BUTTON_DARK)));
    swap_button->set_texture(texture_manager[SL::TextureManager::Icon::Swap]);
    booba::APPCONTEXT->fgColor = CUST_SL::Color::convert_color_uint(CUST_SL::Color::White);
    booba::APPCONTEXT->bgColor = CUST_SL::Color::convert_color_uint(CUST_SL::Color::Black);

    HSVwindow *hsv_window = create_hsv_window();

    ColorPicker *color_picker = new ColorPicker(foreground_button, background_button, swap_button, hsv_window);

    return color_picker;
}
