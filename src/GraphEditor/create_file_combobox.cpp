#include "GraphEditor.hpp"

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
