#include "GraphEditor/GraphEditor.hpp"

const std::string path_mountain = "../kot.jpg";


int main()
{
    SL::MainWindow main_window(SL::Vector2d(SL::WIDTH, SL::HEIGHT), SL::Texture(back_ground_color));

    SL::TextureManager &texture_manager = SL::TextureManager::getInstance();
    texture_manager.load_textures("../src/Textures");
    TOOL_SL::ToolManager::getInstance().loadPlugins("../Plugins_so/");

    SL::Image image(path_mountain);
    TOOL_SL::ToolPalette tool_palette(SL::Vector2d(300, 300), SL::Vector2d(10, 23), SL::Texture(tool_color));
    SL::Container setting_container(SL::Vector2d(300, 568), SL::Vector2d(10, 430), SL::Texture(tool_color));
    TOOL_SL::ToolManager::getInstance().setToolPalette(&tool_palette);
    TOOL_SL::ToolManager::getInstance().setSettingsField(&setting_container);
    
    CUST_SL::Canvas canvas(SL::Vector2d(0, 0), SL::Vector2d(0, 0), SL::Texture(back_ground_color));
    canvas.setImage(image);
    
    SL::DecoratorScrollBar scroll_bar_canvas(&canvas, SL::Vector2d(1400, 970), SL::Vector2d(320, 20));

    CUST_SL::HSVwindow *hsv_window = create_hsv_window();

    CUST_SL::ColorPicker color_picker(SL::Vector2d(80, 80), SL::Vector2d(120, 335), SL::Texture(back_ground_color));
    color_picker.setHSVwindow(hsv_window);

    main_window.add(&color_picker);

    SL::Application app(&main_window);

    CUST_SL::HistoryWindow history_window(SL::Vector2d(1000, 1000), &canvas);
    
    SL::Button open_history(SL::Vector2d(100, 100), SL::Vector2d(200, 200));
    open_history.setLeftClick(new SL::SimpleCommand<CUST_SL::HistoryWindow>(&history_window, &CUST_SL::HistoryWindow::exec));
    
    main_window.add(&scroll_bar_canvas);
    main_window.add(&tool_palette);
    main_window.add(&setting_container);
    main_window.add(&open_history);

    app.exec();
}