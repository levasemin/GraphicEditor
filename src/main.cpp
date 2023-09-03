#include "GraphEditor/GraphEditor.hpp"

const std::string path_mountain = "../kot.jpg";

CUST_SL::Canvas *canvas;

void func_save()
{
    CUST_SL::HistoryManager::getInstance().save("saved_history");
}

void func_open()
{
    CUST_SL::HistoryManager::getInstance().load("saved_history", canvas);
}

int main()
{
    SL::MainWindow main_window(SL::Vector2d(SL::WIDTH, SL::HEIGHT), SL::Texture(back_ground_color));

    SL::TextureManager &texture_manager = SL::TextureManager::getInstance();
    TOOL_SL::ToolManager::getInstance().loadPlugins("../Plugins_so/");

    SL::Image image(path_mountain);
    TOOL_SL::ToolPalette tool_palette(SL::Vector2d(300, 300), SL::Vector2d(10, 23), SL::Texture(tool_color));
    SL::Container setting_container(SL::Vector2d(300, 568), SL::Vector2d(10, 430), SL::Texture(tool_color));
    TOOL_SL::ToolManager::getInstance().setToolPalette(&tool_palette);
    TOOL_SL::ToolManager::getInstance().setSettingsField(&setting_container);
    
    canvas = new CUST_SL::Canvas(SL::Vector2d(0, 0), SL::Vector2d(0, 0), SL::Texture(back_ground_color));
    canvas->setImage(image);
    
    SL::DecoratorScrollBar scroll_bar_canvas(canvas, SL::Vector2d(1400, 970), SL::Vector2d(320, 20));

    CUST_SL::HSVwindow *hsv_window = create_hsv_window();

    CUST_SL::ColorPicker color_picker(SL::Vector2d(80, 80), SL::Vector2d(120, 335), SL::Texture(back_ground_color));
    color_picker.setHSVwindow(hsv_window);

    main_window.add(&color_picker);

    SL::Application app(&main_window);

    CUST_SL::HistoryWindow history_window(SL::Vector2d(1000, 1000), canvas);
    
    SL::Button open_history(SL::Vector2d(100, 100), SL::Vector2d(200, 200));
    open_history.setLeftClick(dynamic_cast<SL::Command<> *>(new SL::SimpleCommand<CUST_SL::HistoryWindow>(&history_window, &CUST_SL::HistoryWindow::exec)));
    
    SL::Button save_button(SL::Vector2d(100, 40), SL::Vector2d(200, 320));
    save_button.setLeftClick(dynamic_cast<SL::Command<> *>(new SL::FunctorCommand<>(&func_save)));
    save_button.setText("save");

    SL::Button open_button(SL::Vector2d(100, 40), SL::Vector2d(200, 370));
    open_button.setLeftClick(dynamic_cast<SL::Command<> *>(new SL::FunctorCommand<>(&func_open)));
    open_button.setText("open");

    main_window.add(&scroll_bar_canvas);
    main_window.add(&tool_palette);
    main_window.add(&setting_container);
    main_window.add(&open_history);
    main_window.add(&open_button);
    main_window.add(&save_button);
    
    app.exec();
}