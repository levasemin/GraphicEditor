#include "NodeButton.hpp"

namespace CUST_SL
{
    NodeButton *NodeButton::current_button_ = nullptr;

    NodeButton::NodeButton(SL::Vector2d shape, SL::Vector2d position, SL::Texture texture) : SL::Button(shape, position, texture)
    {
        SL::Button::setLeftClick((SL::Command<> *)new SL::SimpleCommand<NodeButton>(this, &NodeButton::pressEvent));
    }

    void NodeButton::set_node(HistoryManager::Node *node)
    {
        setTexture(node->getState().getTexture());
        node_ = node;
    }

    HistoryManager::Node *NodeButton::get_node()
    {
        return node_;
    }

    void NodeButton::setLeftClick(SL::Command<NodeButton *> *command)
    {
        command_ = command;
    }

    SL::Command<NodeButton *> *NodeButton::getLeftClick()
    {
        return command_;
    }

    void NodeButton::pressEvent()
    {
        if (node_)
        {
            current_button_ = this;

            was_clicked_ = !was_clicked_;
        }

        if (command_)
        {
            command_->Execute(this);
        }
    }

    void NodeButton::moveMouseEvent (const SL::Event &event)
    {
        if (current_button_ != this)
        {
            was_clicked_ = false;
        }

        if (!was_clicked_)
        {
            Button::moveMouseEvent(event);
        }
    }

    void NodeButton::scrollEvent (const SL::Event &event)
    {
        if (current_button_ != this)
        {
            was_clicked_ = false;
        }

        if (!was_clicked_)
        {
            Button::scrollEvent(event);
        }
    }
}