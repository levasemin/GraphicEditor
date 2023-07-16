#include "GraphEditor.hpp"
#include "tools.hpp"

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