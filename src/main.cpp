#include "GraphEditor/GraphEditor.hpp"

const std::string path_mountain = "../kot.jpg";

booba::ApplicationContext* booba::APPCONTEXT = nullptr;

int main()
{
    booba::APPCONTEXT = new booba::ApplicationContext();
    booba::APPCONTEXT->fgColor = booba::Color(255, 255, 255);
    booba::APPCONTEXT->bgColor = booba::Color();

    SL::MainWindow main_window(SL::Vector2d(SL::WIDTH, SL::HEIGHT), SL::Texture(back_ground_color));

    SL::TextureManager &texture_manager = SL::TextureManager::getInstance();
    texture_manager.load_textures("../src/Textures");

    SL::Image image(path_mountain);
    TOOL_SL::ToolPalette tool_palette(SL::Vector2d(300, 300), SL::Vector2d(10, 23), SL::Texture(tool_color));
    SL::Container setting_container(SL::Vector2d(300, 568), SL::Vector2d(10, 430), SL::Texture(tool_color));

    CUST_SL::Canvas canvas(SL::Vector2d(0, 0), SL::Vector2d(0, 0), SL::Texture(back_ground_color));
    canvas.setImage(image);
    
    SL::DecoratorScrollBar scroll_bar_canvas(&canvas, SL::Vector2d(1400, 970), SL::Vector2d(320, 20));

    // main_window.add(&scroll_bar_canvas);
    // main_window.add(&tool_palette);
    // main_window.add(&setting_container);

    CUST_SL::HSVwindow *hsv_window = create_hsv_window();

    CUST_SL::ColorPicker color_picker(SL::Vector2d(80, 80), SL::Vector2d(120, 335), SL::Texture(back_ground_color));
    color_picker.setHSVwindow(hsv_window);

    main_window.add(&color_picker);

    SL::Application app(&main_window);

    app.exec();
}