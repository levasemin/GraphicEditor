#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "Application.h"

void Application::set_main_window(MainWindow *main_window)
{
    main_window_ = main_window;
}

void Application::exec()
{    
    if (!window_)
    {
        window_ = new Window (main_window_->get_shape(), main_window_->style_);
    }
    
    window_->create(main_window_->get_shape(), "", main_window_->style_);

    while(window_->isOpen() && window_->getVisible())
    {
        Event event;

        while (window_->pollEvent(event))
        {
            event_manager_.distribute_event(main_window_, event);
        }

        show(main_window_);
    }
}

void Application::close()
{
    if (window_)
    {
        window_->close();
    }
}

void Application::show(MainWindow *window)
{
    window_->clear();
    main_window_->draw();   
    main_window_->display(window_);
}