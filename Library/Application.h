#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include <vector>
#include <iostream>
#include "Widget.h"
#include "EventManager.h"
#include "MainWindow.h"

class Application
{
    public: 
        MainWindow *main_window_ = nullptr;
        Window *window_ = nullptr;

        EventManager event_manager_;

        Application(MainWindow *main_window):
            main_window_(main_window),
            event_manager_()
            {};

        Application (const Application &source):
            main_window_(source.main_window_),
            window_(source.window_),
            event_manager_(source.event_manager_)
        {}
        
        Application &operator=(const Application &source)
        {
            main_window_   = source.main_window_;
            window_        = source.window_;
            event_manager_ = source.event_manager_;

            return *this;
        }
        
        void exec();
        void close();
        void set_main_window(MainWindow *main_window);
        void show(MainWindow *window);        
};