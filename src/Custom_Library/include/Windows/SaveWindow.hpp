#pragma once

#include "GraphLib.hpp"
#include "../Widgets/Canvas.hpp"

namespace CUST_SL
{
    class SaveWindow : public SL::MainWindow
    {
    public:
        SL::Application *app_ = nullptr;
        Canvas *canvas_ = nullptr;
        std::string path_;

        SL::Button *save_button_;
        SL::Button *cancel_button_;
        SL::Editor *path_editor_;

        SaveWindow(SL::Vector2d shape, SL::Button *save_button, SL::Button *cancel_button, SL::Editor *path_editor);

        SaveWindow (const SaveWindow &source);

        SaveWindow &operator= (const SaveWindow &source);

        void set_canvas(Canvas *canvas);

        void change_path();

        void setPath(std::string path);
        void setPath();
        
        void save_image();

        void exec();

        void close();

        ~SaveWindow();
    };
}