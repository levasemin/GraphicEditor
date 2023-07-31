#include "GraphEditor.hpp"

SL::ComboBox *create_file_combobox(CUST_SL::Canvas *canvas)
{
    SL::ComboBox *file_button = new SL::ComboBox(SL::Vector2d(60, 20), SL::Vector2d(0, 0), SL::Texture(BUTTON_DARK_COLOR));
    file_button->setText("File");
    file_button->setCharacterSize(16);
    file_button->set_box_texture(SL::Texture(BUTTON_DARK_COLOR));


    SL::Button *file_save_button = new SL::Button(SL::Vector2d(50, 30), SL::Vector2d(0, 0), SL::Texture(BUTTON_DARK_COLOR));
    file_save_button->setCharacterSize(16);
    file_save_button->setText("Save");
    file_save_button->setTextColor(TEXT_COLOR);

    CUST_SL::SaveWindow *save_window = create_save_window();
    save_window->set_canvas(canvas);
    file_save_button->setLeftClick((SL::Command<> *) new SL::SimpleCommand<CUST_SL::SaveWindow>(save_window, &CUST_SL::SaveWindow::exec));

    SL::Button *file_open_button = new  SL::Button(SL::Vector2d(50, 30), SL::Vector2d(0, 30), SL::Texture(BUTTON_DARK_COLOR));

    file_open_button->setCharacterSize(16);
    file_open_button->setText("Open");
    file_open_button->setTextColor(TEXT_COLOR);

    CUST_SL::OpenWindow *open_window = create_open_window();
    open_window->set_canvas(canvas);
    file_open_button->setLeftClick((SL::Command<> *) new SL::SimpleCommand<CUST_SL::OpenWindow>(open_window, &CUST_SL::OpenWindow::exec));

    file_button->add(file_save_button);
    file_button->add(file_open_button);

    return file_button;
}
