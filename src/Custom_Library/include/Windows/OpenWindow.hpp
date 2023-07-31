#pragma once

#include "GraphLib.hpp"


#include "../Widgets/Canvas.hpp"

namespace CUST_SL
{
    class OpenWindow : public SL::MainWindow
    {
    public:
        SL::Application *app_ = nullptr;
        Canvas *canvas_ = nullptr;
        std::string path_;

        SL::Button *open_button_;
        SL::Button *cancel_button_;
        SL::Editor *path_editor_;

        OpenWindow(SL::Vector2d shape, SL::Button *open_button, SL::Button *cancel_button, SL::Editor *path_editor);

        OpenWindow (const OpenWindow &source);

        OpenWindow &operator= (const OpenWindow &source);
        ~OpenWindow();

        void set_canvas(Canvas *canvas);

        void setPath(std::string path);

        void open_image();

        void exec();

        void close();

    };
}