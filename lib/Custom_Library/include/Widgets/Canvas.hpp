#pragma once

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wswitch-enum"

#include <filesystem>
#include <dlfcn.h>
#include <vector>
#include <memory>

#include "HistoryManager.hpp"
#include "GraphLib.hpp"
#include "Surface.hpp"

namespace CUST_SL
{
    class Canvas : public SL::CompositeObject
    {
    public:
        Canvas(SL::Vector2d shape, SL::Vector2d position, const SL::Texture &texture = SL::Texture(SL::Color::White));

        Canvas(const Canvas &source);
        Canvas &operator=(const Canvas &source);
        ~Canvas();

        SL::Image *getImage();
        SL::Image *getHiddenImage();
        
        void setImage(const SL::Image &new_image, bool is_new_project = true);
        void setNode(HistoryManager::Node *node);

        void set_current_node(HistoryManager::Node *node);

        void recoverySecondLayer();
            
    protected:
        void moveMouseEvent(const SL::Event &event) override;

        void clickLeftEvent(const SL::Event &event) override;
        void releaseLeftEvent(const SL::Event &event) override;

        void clickRightEvent(const SL::Event &event) override;
        void releaseRightEvent(const SL::Event &event) override;

        void pressKeyEvent(const SL::Event &event) override;

    private:
        Surface *main_layer_   = nullptr;
        Surface *hidden_layer_ = nullptr;

        float zoom_;
        
        bool image_changed_ = false;

        HistoryManager::Node *current_node_ = nullptr;
        void set_zoom(float value);

        void ConfigureSurface(Surface *surface);
        void apply(const SL::Event &event);
    };
}