#include "Library/GraphicLib.h"
#include "SaveWindow.h"
#include "OpenWindow.h"
#include "ColorPicker.h"

#include "Canvas.h"
#include "HSVpalette.h"
#include "HSVwindow.h"

#include <iostream>
#include <vector>
#include <string>

const std::string path_mountain = "/home/levce/projectsDED/event_handler2/Event_handler/source/british.png";

booba::ApplicationContext* booba::APPCONTEXT = nullptr;

const Color back_ground_color(uint8_t(69),  uint8_t(69),  uint8_t(69));
const Color tool_color       (uint8_t(48),  uint8_t(48),  uint8_t(48));
const Color text_color       (uint8_t(190), uint8_t(190), uint8_t(190));
const Color editor_color     (uint8_t(31),  uint8_t(31),  uint8_t(31));
const Color button_color     (uint8_t(44),  uint8_t(44),  uint8_t(44));

SaveWindow *create_save_window()
{
    Editor *path_editor = new Editor(Vector2d(200, 40), Vector2d(150, 80));
    path_editor->setTextColor(text_color);
    path_editor->set_texture(Texture(editor_color));
    path_editor->setAlignment(Label::Alignment::LeftCenter);
    
    Button *save_button = new Button(Vector2d(70, 20), Vector2d(55, 165), Texture(button_color));
    save_button->setString("Save");
    save_button->setCharacterSize(20);
    
    Button *cancel_button = new Button(Vector2d(70, 20), Vector2d(245, 165), Texture(button_color));
    cancel_button->setString("Cancel");
    cancel_button->setCharacterSize(20);

    SaveWindow *save_window = new SaveWindow(Vector2d(300, 200), save_button, cancel_button, path_editor);

    return save_window;
}

OpenWindow *create_open_window()
{
   
    Editor *path_editor = new Editor(Vector2d(200, 40), Vector2d(150, 80));
    path_editor->setTextColor(text_color);
    path_editor->set_texture(Texture(editor_color));
    path_editor->setAlignment(Label::Alignment::LeftCenter);

    Button *open_button = new Button(Vector2d(70, 20), Vector2d(55, 165), Texture(button_color));
    open_button->setString("Open");
    open_button->setCharacterSize(20);
    
    Button *cancel_button = new Button(Vector2d(70, 20), Vector2d(245, 165), Texture(button_color));
    cancel_button->setString("Cancel");
    cancel_button->setCharacterSize(20);

    OpenWindow *open_window = new OpenWindow(Vector2d(300, 200), open_button, cancel_button, path_editor);

    return open_window;
}

HSVwindow *create_hsv_window()
{
    HSVpalette *hsv_palette = new HSVpalette(Vector2d(175, 315), Vector2d(120, 178));
    Editor *r_editor        = new Editor(Vector2d(50, 30), Vector2d(270, 35));
    Editor *g_editor        = new Editor(Vector2d(50, 30), Vector2d(270, 75));
    Editor *b_editor        = new Editor(Vector2d(50, 30), Vector2d(270, 115));
    Button *cancel_button   = new Button(Vector2d(70, 20), Vector2d(55, 370), Texture(button_color));
    Button *ok_button       = new Button(Vector2d(70, 20), Vector2d(245, 370), Texture(button_color));

    r_editor->set_texture  (editor_color);
    r_editor->setTextColor (text_color);
    // r_editor->setCharacterSize(18);

    g_editor->set_texture  (editor_color);
    g_editor->setTextColor (text_color);
    // r_editor->setCharacterSize(18);
    
    b_editor->set_texture  (editor_color);
    b_editor->setTextColor (text_color);
    // r_editor->setCharacterSize(18);

    ok_button->setString("Ok");
    ok_button->setTextColor(text_color);
    ok_button->setCharacterSize(22);

    cancel_button->setString("Cancel");
    cancel_button->setTextColor(text_color);
    cancel_button->setCharacterSize(22);

    HSVwindow *hsv_window = new HSVwindow(Vector2d(300, 400), Texture(back_ground_color), hsv_palette, r_editor, g_editor, b_editor, ok_button, cancel_button);
    return hsv_window;
}

ComboBox *create_file_combobox(Canvas *canvas)
{
    ComboBox *file_button = new ComboBox(Vector2d(60, 20), Vector2d(30, 10), Texture(button_color));
    file_button->setString("File");
    file_button->setCharacterSize(16);
    file_button->set_box_texture(Texture(button_color));


    Button *file_save_button = new Button(Vector2d(50, 30), Vector2d(25, 15), Texture(button_color));
    file_save_button->setCharacterSize(16);
    file_save_button->setString("Save");
    file_save_button->setTextColor(text_color);

    SaveWindow *save_window = create_save_window();
    save_window->set_canvas(canvas);
    file_save_button->set_left_click((Command<const Event &> *) new SimpleCommand<SaveWindow, const Event &>(save_window, &SaveWindow::exec));

    Button *file_open_button = new  Button(Vector2d(50, 30), Vector2d(25, 45), Texture(button_color));
    
    file_open_button->setCharacterSize(16);
    file_open_button->setString("Open");
    file_open_button->setTextColor(text_color);

    OpenWindow *open_window = create_open_window();
    open_window->set_canvas(canvas);
    file_open_button->set_left_click((Command<const Event &> *) new SimpleCommand<OpenWindow, const Event &>(open_window, &OpenWindow::exec));


    file_button->add(file_save_button);
    file_button->add(file_open_button);

    return file_button;
}

ColorPicker *create_color_picker()
{
    TextureManager &texture_manager = TextureManager::getInstance();

    Button *foreground_button = new Button(Vector2d(40, 40), Vector2d(140, 355), Texture(Color::White));
    Button *background_button = new Button(Vector2d(40, 40), Vector2d(180, 395), Texture(Color::Black));    
    Button *swap_button       = new Button(Vector2d(20, 20), Vector2d(170, 365), Texture(Color(button_color)));    
    swap_button->set_texture(texture_manager[TextureManager::Icon::Swap]);
    booba::APPCONTEXT->fgColor = Color::convert_color_uint(Color::White);
    booba::APPCONTEXT->bgColor = Color::convert_color_uint(Color::Black);

    HSVwindow *hsv_window = create_hsv_window();

    ColorPicker *color_picker = new ColorPicker(foreground_button, background_button, swap_button, hsv_window); 
    return color_picker;
}

int main()
{   
    booba::APPCONTEXT = new booba::ApplicationContext();
    booba::APPCONTEXT->fgColor = 0xFF000000;
    booba::APPCONTEXT->bgColor = 0xFF000000;
    
    MainWindow main_window(Vector2d(WIDTH, HEIGHT), Texture(back_ground_color));

    TextureManager &texture_manager = TextureManager::getInstance();
    texture_manager.load_textures("Textures");

    Image image(path_mountain);
    ToolPalette tool_palette(Vector2d(300, 300), Vector2d(160, 173), Texture(tool_color));
    Container setting_container(Vector2d(300, 568), Vector2d(160, 710));
    setting_container.set_texture(Texture(tool_color));
    
    Canvas canvas(Vector2d(1400, 970), Vector2d(1020, 508), &tool_palette, &setting_container);

    canvas.set_image(image);
    
    DecoratorScrollBar scroll_bar_canvas(&canvas);
    
    ComboBox *file_button = create_file_combobox(&canvas);

    ColorPicker *color_picker = create_color_picker();

    main_window.add(&scroll_bar_canvas);    
    main_window.add(&tool_palette);
    main_window.add(&setting_container);
    main_window.add(file_button);
    main_window.add(color_picker);
    Application app(&main_window);
    
    app.exec();
}