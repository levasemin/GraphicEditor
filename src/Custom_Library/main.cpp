// #include "GraphLib.hpp"
#include "class/class.hpp"

// #include "ToolButton.hpp"


int main()
{
    SL::MainWindow window(SL::Vector2d(200, 200));
    SL::Application app(&window);
    SL::Color color;
    Class class1(1);
    // ToolButton button(SL::Vector2d(10, 10));
    app.exec();
}