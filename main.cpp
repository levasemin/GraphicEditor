#include "GraphEditor/GraphEditor.hpp"

#include <iostream>
#include <vector>
#include <string>

const std::string path_mountain = "../src/british.png";

booba::ApplicationContext* booba::APPCONTEXT = nullptr;

int main()
{
    booba::APPCONTEXT = new booba::ApplicationContext();
    booba::APPCONTEXT->fgColor = 0xFF000000;
    booba::APPCONTEXT->bgColor = 0xFF000000;

    SL::MainWindow main_window(SL::Vector2d(SL::WIDTH, SL::HEIGHT), SL::Texture(back_ground_color));

    SL::TextureManager &texture_manager = SL::TextureManager::getInstance();
    texture_manager.load_textures("../src/Textures");
    TOOL_SL::ToolManager::loadPlugins("../Plugins_so");
    
    SL::Image image(path_mountain);
    ToolPalette tool_palette(SL::Vector2d(300, 300), SL::Vector2d(10, 23), SL::Texture(tool_color));
    SL::Container setting_container(SL::Vector2d(300, 568), SL::Vector2d(10, 430), SL::Texture(tool_color));
    //TODO order
// 1
    ToolManager::getInstance().set_setting_field(&setting_container);
// 2
    Canvas *canvas = Canvas::Create(SL::Vector2d(1400, 970), SL::Vector2d(320, 20), &tool_palette);
    canvas->SetImage(image);

    SL::DecoratorScrollBar scroll_bar_canvas(canvas, SL::Vector2d(1400, 970), SL::Vector2d(320, 20));

    SL::ComboBox *file_button = create_file_combobox(canvas);

    ColorPicker *color_picker = create_color_picker();

    // HistoryWindow history_window(SL::Vector2d(1000, 1000));

    // SL::Button open_history(SL::Vector2d(100, 100), SL::Vector2d(200, 200));
    // open_history.setLeftClick(new SL::SimpleCommand<HistoryWindow, const SL::Event &>(&history_window, &HistoryWindow::exec));
    main_window.add(&scroll_bar_canvas);
    main_window.add(&tool_palette);
    main_window.add(&setting_container);
    main_window.add(file_button);
    main_window.add(color_picker);
    main_window.add(&open_history);
    SL::Application app(&main_window);

    app.exec();
}
