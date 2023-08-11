#pragma once

#include "GraphLib.hpp"


#include "../Widgets/Canvas.hpp"

namespace CUST_SL
{
    class OpenWindow : public SL::MainWindow
    {
    public:
        OpenWindow(SL::Vector2d shape, SL::Button *open_button, SL::Button *cancel_button, SL::Editor *path_editor);

        OpenWindow (const OpenWindow &source);

        OpenWindow &operator= (const OpenWindow &source);
        ~OpenWindow();

        void set_canvas(Canvas *canvas);

        void setPath(std::string path);

        void open_image();

        void exec();

        void close();

    private:
        SL::Application *app_ = nullptr;
        Canvas *canvas_ = nullptr;
        std::string path_;

        SL::Button *open_button_ = nullptr;
        SL::Button *cancel_button_ = nullptr;
        SL::Editor *path_editor_ = nullptr;

    };
}