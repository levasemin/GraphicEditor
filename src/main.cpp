#include "Graphic-Library/GraphLib/GraphLib.h"

#include "Custom_Widgets/SaveWindow.h"
#include "Custom_Widgets/OpenWindow.h"
#include "Custom_Widgets/ColorPicker.h"

#include "Custom_Widgets/Canvas.h"
#include "Custom_Widgets/HSVpalette.h"
#include "Custom_Widgets/HSVwindow.h"
#include "Custom_Widgets/LayerManager.hpp"
#include <iostream>
#include <vector>
#include <string>



const std::string path_mountain = "british.png";

booba::ApplicationContext* booba::APPCONTEXT = nullptr;

const CUST_SL::Color back_ground_color(uint8_t(69),  uint8_t(69),  uint8_t(69));
const CUST_SL::Color tool_color       (uint8_t(48),  uint8_t(48),  uint8_t(48));

SaveWindow *create_save_window()
{
    SL::Editor *path_editor = new SL::Editor(SL::Vector2d(200, 40), SL::Vector2d(50, 60));
    path_editor->setTextColor(CUST_SL::Color::TEXT);
    path_editor->set_texture(SL::Texture(CUST_SL::Color::EDITOR));
    path_editor->setAlignment(SL::Label::Alignment::LeftCenter);
    
    SL::Button *save_button = new SL::Button(SL::Vector2d(70, 20), SL::Vector2d(20, 155), SL::Texture(CUST_SL::Color::Color::BUTTON_DARK));
    save_button->setString("Save");
    save_button->setCharacterSize(20);
    
    SL::Button *cancel_button = new SL::Button(SL::Vector2d(70, 20), SL::Vector2d(210, 155), SL::Texture(CUST_SL::Color::Color::BUTTON_DARK));
    cancel_button->setString("Cancel");
    cancel_button->setCharacterSize(20);

    SaveWindow *save_window = new SaveWindow(SL::Vector2d(300, 200), save_button, cancel_button, path_editor);

    return save_window;
}

OpenWindow *create_open_window()
{
   
    SL::Editor *path_editor = new SL::Editor(SL::Vector2d(200, 40), SL::Vector2d(50, 60));
    path_editor->setTextColor(CUST_SL::Color::TEXT);
    path_editor->set_texture(SL::Texture(CUST_SL::Color::EDITOR));
    path_editor->setAlignment(SL::Label::Alignment::LeftCenter);

    SL::Button *open_button = new SL::Button(SL::Vector2d(70, 20), SL::Vector2d(20, 155), SL::Texture(CUST_SL::Color::Color::BUTTON_DARK));
    open_button->setString("Open");
    open_button->setCharacterSize(20);
    
    SL::Button *cancel_button = new SL::Button(SL::Vector2d(70, 20), SL::Vector2d(215, 155), SL::Texture(CUST_SL::Color::Color::BUTTON_DARK));
    cancel_button->setString("Cancel");
    cancel_button->setCharacterSize(20);

    OpenWindow *open_window = new OpenWindow(SL::Vector2d(300, 200), open_button, cancel_button, path_editor);

    return open_window;
}

HSVwindow *create_hsv_window()
{
    HSVpalette *hsv_palette = new HSVpalette(SL::Vector2d(175, 315), SL::Vector2d(30, 20));
    
    SL::Editor *r_editor        = new SL::Editor(SL::Vector2d(50, 30), SL::Vector2d(245, 20));
    SL::Editor *g_editor        = new SL::Editor(SL::Vector2d(50, 30), SL::Vector2d(245, 60));
    SL::Editor *b_editor        = new SL::Editor(SL::Vector2d(50, 30), SL::Vector2d(245, 100));
    SL::Button *cancel_button   = new SL::Button(SL::Vector2d(70, 20), SL::Vector2d(20, 360),  SL::Texture(CUST_SL::Color::Color::BUTTON_DARK));
    SL::Button *ok_button       = new SL::Button(SL::Vector2d(70, 20), SL::Vector2d(210, 360), SL::Texture(CUST_SL::Color::Color::BUTTON_DARK));

    r_editor->set_texture  (CUST_SL::Color::EDITOR);
    r_editor->setTextColor (CUST_SL::Color::TEXT);

    g_editor->set_texture  (CUST_SL::Color::EDITOR);
    g_editor->setTextColor (CUST_SL::Color::TEXT);
    
    b_editor->set_texture  (CUST_SL::Color::EDITOR);
    b_editor->setTextColor (CUST_SL::Color::TEXT);

    ok_button->setString("Ok");
    ok_button->setTextColor(CUST_SL::Color::TEXT);
    ok_button->setCharacterSize(22);

    cancel_button->setString("Cancel");
    cancel_button->setTextColor(CUST_SL::Color::TEXT);
    cancel_button->setCharacterSize(22);

    HSVwindow *hsv_window = new HSVwindow(SL::Vector2d(300, 400), SL::Texture(back_ground_color), hsv_palette, r_editor, g_editor, b_editor, ok_button, cancel_button);
    return hsv_window;
}

SL::ComboBox *create_file_combobox(Canvas *canvas)
{
    SL::ComboBox *file_button = new SL::ComboBox(SL::Vector2d(60, 20), SL::Vector2d(0, 0), SL::Texture(CUST_SL::Color::Color::BUTTON_DARK));
    file_button->setString("File");
    file_button->setCharacterSize(16);
    file_button->set_box_texture(SL::Texture(CUST_SL::Color::Color::BUTTON_DARK));


    SL::Button *file_save_button = new SL::Button(SL::Vector2d(50, 30), SL::Vector2d(0, 0), SL::Texture(CUST_SL::Color::Color::BUTTON_DARK));
    file_save_button->setCharacterSize(16);
    file_save_button->setString("Save");
    file_save_button->setTextColor(CUST_SL::Color::TEXT);

    SaveWindow *save_window = create_save_window();
    save_window->set_canvas(canvas);
    file_save_button->set_left_click((SL::Command<const SL::Event &> *) new SL::SimpleCommand<SaveWindow, const SL::Event &>(save_window, &SaveWindow::exec));

    SL::Button *file_open_button = new  SL::Button(SL::Vector2d(50, 30), SL::Vector2d(0, 30), SL::Texture(CUST_SL::Color::Color::BUTTON_DARK));
    
    file_open_button->setCharacterSize(16);
    file_open_button->setString("Open");
    file_open_button->setTextColor(CUST_SL::Color::TEXT);

    OpenWindow *open_window = create_open_window();
    open_window->set_canvas(canvas);
    file_open_button->set_left_click((SL::Command<const SL::Event &> *) new SL::SimpleCommand<OpenWindow, const SL::Event &>(open_window, &OpenWindow::exec));

    file_button->add(file_save_button);
    file_button->add(file_open_button);

    return file_button;
}

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

int main()
{   
    booba::APPCONTEXT = new booba::ApplicationContext();
    booba::APPCONTEXT->fgColor = 0xFF000000;
    booba::APPCONTEXT->bgColor = 0xFF000000;
    
    SL::MainWindow main_window(SL::Vector2d(SL::WIDTH, SL::HEIGHT), SL::Texture(back_ground_color));

    SL::TextureManager &texture_manager = SL::TextureManager::getInstance();
    texture_manager.load_textures("Textures");

    Image image(path_mountain);
    ToolPalette tool_palette(SL::Vector2d(300, 300), SL::Vector2d(10, 23), SL::Texture(tool_color));
    SL::Container setting_container(SL::Vector2d(300, 568), SL::Vector2d(10, 430));
    setting_container.set_texture(SL::Texture(tool_color));
    //TODO order
// 1
    ToolManager::getInstance().set_setting_field(&setting_container);
// 2  
    Canvas *canvas = Canvas::Create(SL::Vector2d(1400, 970), SL::Vector2d(320, 20), &tool_palette);
    canvas->set_image(image);
    
    SL::DecoratorScrollBar scroll_bar_canvas(canvas);
    
    SL::ComboBox *file_button = create_file_combobox(canvas);

    ColorPicker *color_picker = create_color_picker();

    SL::Container layer_palette = SL::Container(SL::Vector2d(150, 400), SL::Vector2d(1760, 20), SL::Texture(tool_color));
    SL::Container layers_field  = SL::Container(SL::Vector2d(140, 250), SL::Vector2d(5, 55), SL::Texture(CUST_SL::Color::White));
    SL::Button add_button = SL::Button(SL::Vector2d(50, 50), SL::Vector2d(0, 0), SL::Texture(CUST_SL::Color::Blue));
    add_button.setString("Add");
    LayerManager layer_manager(Canvas::getInstance(), &layer_palette, &layers_field, &add_button);

    layer_palette.add(&add_button);
    layer_palette.add(&layers_field);

    main_window.add(&layer_palette);
    main_window.add(&scroll_bar_canvas);    
    main_window.add(&tool_palette);
    main_window.add(&setting_container);
    main_window.add(file_button);
    main_window.add(color_picker);
    SL::Application app(&main_window);
    
    app.exec();
}