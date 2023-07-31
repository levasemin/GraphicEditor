#include "GraphEditor.hpp"

CUST_SL::OpenWindow *create_open_window()
{

    SL::Editor *path_editor = new SL::Editor(SL::Vector2d(200, 40), SL::Vector2d(50, 60));
    path_editor->setTextColor(TEXT_COLOR);
    path_editor->setTexture(SL::Texture(EDITOR_COLOR));
    path_editor->setAlignment(SL::Label::Alignment::LeftCenter);

    SL::Button *open_button = new SL::Button(SL::Vector2d(70, 20), SL::Vector2d(20, 155), SL::Texture(BUTTON_DARK_COLOR));
    open_button->setText("Open");
    open_button->setCharacterSize(20);

    SL::Button *cancel_button = new SL::Button(SL::Vector2d(70, 20), SL::Vector2d(215, 155), SL::Texture(BUTTON_DARK_COLOR));
    cancel_button->setText("Cancel");
    cancel_button->setCharacterSize(20);

    CUST_SL::OpenWindow *open_window = new CUST_SL::OpenWindow(SL::Vector2d(300, 200), open_button, cancel_button, path_editor);

    return open_window;
}

CUST_SL::SaveWindow *create_save_window()
{
    SL::Editor *path_editor = new SL::Editor(SL::Vector2d(200, 40), SL::Vector2d(50, 60));
    path_editor->setTextColor(TEXT_COLOR);
    path_editor->setTexture(SL::Texture(EDITOR_COLOR));
    path_editor->setAlignment(SL::Label::Alignment::LeftCenter);

    SL::Button *save_button = new SL::Button(SL::Vector2d(70, 20), SL::Vector2d(20, 155), SL::Texture(BUTTON_DARK_COLOR));
    save_button->setText("Save");
    save_button->setCharacterSize(20);

    SL::Button *cancel_button = new SL::Button(SL::Vector2d(70, 20), SL::Vector2d(210, 155), SL::Texture(BUTTON_DARK_COLOR));
    cancel_button->setText("Cancel");
    cancel_button->setCharacterSize(20);

    CUST_SL::SaveWindow *save_window = new CUST_SL::SaveWindow(SL::Vector2d(300, 200), save_button, cancel_button, path_editor);

    return save_window;
}

CUST_SL::HSVwindow *create_hsv_window()
{
    CUST_SL::HSVpalette *hsv_palette = new CUST_SL::HSVpalette(SL::Vector2d(175, 315), SL::Vector2d(30, 20));

    SL::Editor *r_editor        = new SL::Editor(SL::Vector2d(50, 30), SL::Vector2d(245, 20));
    SL::Editor *g_editor        = new SL::Editor(SL::Vector2d(50, 30), SL::Vector2d(245, 60));
    SL::Editor *b_editor        = new SL::Editor(SL::Vector2d(50, 30), SL::Vector2d(245, 100));
    SL::Button *cancel_button   = new SL::Button(SL::Vector2d(70, 20), SL::Vector2d(20, 360),  SL::Texture(BUTTON_DARK_COLOR));
    SL::Button *ok_button       = new SL::Button(SL::Vector2d(70, 20), SL::Vector2d(210, 360), SL::Texture(BUTTON_DARK_COLOR));

    r_editor->setTexture  (EDITOR_COLOR);
    r_editor->setTextColor (TEXT_COLOR);

    g_editor->setTexture  (EDITOR_COLOR);
    g_editor->setTextColor (TEXT_COLOR);

    b_editor->setTexture  (EDITOR_COLOR);
    b_editor->setTextColor (TEXT_COLOR);

    ok_button->setText("Ok");
    ok_button->setTextColor(TEXT_COLOR);
    ok_button->setCharacterSize(22);

    cancel_button->setText("Cancel");
    cancel_button->setTextColor(TEXT_COLOR);
    cancel_button->setCharacterSize(22);

    CUST_SL::HSVwindow *hsv_window = new CUST_SL::HSVwindow(SL::Vector2d(300, 400), SL::Texture(back_ground_color), hsv_palette, r_editor, g_editor, b_editor, ok_button, cancel_button);
    return hsv_window;
}