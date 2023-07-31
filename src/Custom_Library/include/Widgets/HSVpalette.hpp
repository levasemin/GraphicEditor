#pragma once

#include "GraphLib.hpp"

namespace CUST_SL
{
    class HSVpalette : public SL::CompositeObject
    {
    public:
        HSVpalette(SL::Vector2d shape, SL::Vector2d position);

        HSVpalette(const HSVpalette &source) = default;
        HSVpalette &operator=(const HSVpalette &source) = default;
        ~HSVpalette();

        void setColor(const SL::Color &color);
        SL::Color getColor();

        SL::Command<const SL::Color&> *getCommand();
        void setCommand(SL::Command<const SL::Color&> *command);

    private:
        class HSVfield : public SL::Button
        {
        public:
            HSVfield(SL::Vector2d shape, SL::Vector2d position);
            HSVfield(const HSVfield &field) = default;
            HSVfield &operator=(const HSVfield &field) = default;
            ~HSVfield() = default;

            void setColor(const SL::Color &color);
            SL::Color getColor();

            void change_H(float);
            
            void setCommand(SL::Command<const SL::Color &> *command);
            SL::Command<const SL::Color &> *getCommand();
            
        protected:
            void moveMouseEvent(const SL::Event &event) override;
            void clickLeftEvent(const SL::Event &event) override;
            void releaseLeftEvent(const SL::Event &event) override;
        
        private:
            SL::Command<const SL::Color&> *palette_command_ = nullptr;

            bool clicked_ = false;
            SL::Color color_;
            SL::Color old_color_;
            SL::Image image_;

            void updateTexture();
            void updateCross();
        };

        HSVfield palette_;
        SL::VerticalScrollBar scroll_bar_;
    };
}