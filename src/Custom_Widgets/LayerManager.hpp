#include "GraphLib.h"
#include "Canvas.h"

class LayerManager
{
    Canvas *canvas_;

    SL::Container *layer_palette_ = nullptr;
    SL::Container *layers_field_  = nullptr;
    SL::Button *add_button_ = nullptr;

    SL::Vector2d button_shape_;

public:
    LayerManager(Canvas *canvas, SL::Container *layer_palette, SL::Container *layers_field, SL::Button *add_button) :
        canvas_(canvas),
        layer_palette_(layer_palette),
        add_button_(add_button),
        layers_field_(layers_field),
        button_shape_(layers_field_->get_shape().x_, layers_field_->get_shape().y_ / 5)
    {
        add_button->set_left_click ((SL::Command<const SL::Event &> *) new SL::SimpleCommand<LayerManager, const SL::Event &>(this, &LayerManager::add_layer));
        for (int i = 0; i < canvas->getCountMainlayer(); i++)
        {
            std::cout << "add layer\n";
            auto surface = canvas->getLayer(i);
            SL::Button *button_layer = new SL::Button(button_shape_, SL::Vector2d(0.f, button_shape_.y_ * i), SL::Texture(surface->get_image()->getTexture()));
            button_layer->set_left_click ((SL::Command<const SL::Event &> *) new SL::SimpleCommand<LayerManager, const SL::Event &>(this, &LayerManager::set_current_layer));
            button_layer->set_right_click((SL::Command<const SL::Event &> *) new SL::SimpleCommand<LayerManager, const SL::Event &>(this, &LayerManager::set_visible_layer));
            layers_field_->add(button_layer);
        }
    }

    void set_current_layer(const SL::Event &event)
    {
        std::vector<SL::Widget *> buttons = layer_palette_->get_children();
        for (int i = 0; i < buttons.size(); i++)
        {
            if (event.Oleg_.bcedata.id == uint64_t(buttons[i]))
            {
                canvas_->setCurrentLayer(i);
            }
        }
    }

    void set_visible_layer(const SL::Event &event)
    {
        std::vector<SL::Widget *> buttons = layer_palette_->get_children();
        for (int i = 0; i < buttons.size(); i++)
        {
            if (event.Oleg_.bcedata.id == uint64_t(buttons[i]))
            {
                canvas_->setVisibleLayer(i);
            }
        }
    }

    void set_layer_palette(SL::Container *layer_palette)
    {
        layer_palette_ = layer_palette;
    }

    void add_layer(const SL::Event &event)
    {
        auto surface = canvas_->createLayer(canvas_->getCountMainlayer());
        // surface = canvas_->getLayer(0);
        // std::cout << (surface == nullptr) << std::endl;
        // SL::Button *button_layer = new SL::Button(button_shape_, SL::Vector2d(0.f, button_shape_.y_ * canvas_->getCountMainlayer()), );
        // button_layer->set_left_click ((SL::Command<const SL::Event &> *) new SL::SimpleCommand<LayerManager, const SL::Event &>(this, &LayerManager::set_current_layer));
        // button_layer->set_right_click((SL::Command<const SL::Event &> *) new SL::SimpleCommand<LayerManager, const SL::Event &>(this, &LayerManager::set_visible_layer));
        // layers_field_->add(button_layer);
    }
};
