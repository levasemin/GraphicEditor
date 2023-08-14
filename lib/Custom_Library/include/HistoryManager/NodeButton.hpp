#pragma once

#include "GraphLib.hpp"
#include "HistoryManager.hpp"
#include "Node.hpp"

namespace CUST_SL
{
    class NodeButton : public SL::Button
    {
    public:
        int layer_ = 0;

        NodeButton(SL::Vector2d shape, SL::Vector2d position, SL::Texture texture = SL::Texture(SL::Color::White));

        void set_node(HistoryManager::Node *node);

        HistoryManager::Node *get_node();

        void setLeftClick(SL::Command<NodeButton *> *command);

        SL::Command<NodeButton *> *getLeftClick();
        
    private:
        bool was_clicked_ = false;
        static NodeButton *current_button_;

        HistoryManager::Node *node_ = nullptr;
        SL::Command<NodeButton *> *command_ = nullptr;

        void clickLeftEvent();
        void moveMouseEvent    (const SL::Event &event) override;
        void scrollEvent       (const SL::Event &event) override;
    };
}