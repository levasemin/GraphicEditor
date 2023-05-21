#pragma once

#include "Application/Application.h"
#include "Application/MainWindow.h"
#include "Classes/Texture.h"
#include "Classes/Vector2d.h"
#include "Color.h"
#include "GraphLib.h"
#include "GraphLib.h"
#include "HistoryManager.hpp"
#include "NodeButton.hpp"
#include "Canvas.h"

class HistoryWindow : SL::MainWindow
{
public:
    class HistoryTree: public SL::CompositeObject
    {
    public:
        NodeButton *current_nodebutton = nullptr;
        HistoryWindow *history_window_ = nullptr;
        SL::Container abstract_container_;
        NodeButton *root_button_ = nullptr;
        HistoryTree(SL::Vector2d shape, SL::Vector2d position, HistoryWindow *history_window);
        
        void ChooseNode(const SL::Event &event);
        void ClickSelect(const SL::Event &event);
        void remove_branch(NodeButton *nodebutton);
        void ClickDelete(const SL::Event &event);
        void ClickAdd(const SL::Event &event);
        void redraw_buttons();
        void redraw_button(NodeButton *button);
    }; 

    SL::Application *app_ = nullptr;
    HistoryTree history_tree;
    SL::Button select_button_;
    SL::Button add_button_;
    SL::Button delete_button_;

    HistoryWindow(SL::Vector2d shape) : SL::MainWindow(shape, SL::Texture(CUST_SL::Color::Grey)),
        select_button_({60, 30}, {0, 0}, SL::Texture(CUST_SL::Color::BUTTON_DARK)),
        add_button_({60, 30}, {70, 0}, SL::Texture(CUST_SL::Color::BUTTON_DARK)),
        delete_button_({60, 30}, {140, 0}, SL::Texture(CUST_SL::Color::BUTTON_DARK)), 
        history_tree(SL::Vector2d(shape.x_ - 200, shape.y_ - 200), SL::Vector2d(50, 50), this)
    {
        select_button_.setString("select");
        select_button_.setTextColor(CUST_SL::Color::TEXT);
        add_button_.setString("add");
        add_button_.setTextColor(CUST_SL::Color::TEXT);
        delete_button_.setString("delete");
        delete_button_.setTextColor(CUST_SL::Color::TEXT);

        app_ = new SL::Application(this);
        SL::DecoratorScrollBar *scroll_bar_history_window = new SL::DecoratorScrollBar(&history_tree);

        add(scroll_bar_history_window);
        add(&select_button_);
        add(&add_button_);
        add(&delete_button_);

        select_button_.set_left_click(new SL::SimpleCommand<HistoryTree, const SL::Event &>(&history_tree, &HistoryTree::ClickSelect));
        add_button_.set_left_click   (new SL::SimpleCommand<HistoryTree, const SL::Event &>(&history_tree, &HistoryTree::ClickAdd));
        delete_button_.set_left_click(new SL::SimpleCommand<HistoryTree, const SL::Event &>(&history_tree, &HistoryTree::ClickDelete));
    }

    void exec(const SL::Event &)
    {
        history_tree.redraw_buttons();

        app_->exec();
    }

    void close(const SL::Event &)
    {
        app_->close();        
    }
};


inline HistoryWindow::HistoryTree::HistoryTree(SL::Vector2d shape, SL::Vector2d position, HistoryWindow *history_window) : SL::CompositeObject(shape, position),
    abstract_container_(shape * 2, SL::Vector2d(0, 0)),
    history_window_(history_window)
{

    root_button_ = new NodeButton({abstract_container_.get_shape().x_ / 27, abstract_container_.get_shape().x_ / 27}, 
                                                {abstract_container_.get_shape().x_ / 2 - abstract_container_.get_shape().x_ / 27, 0.0});
    root_button_->layer_ = 0;
    root_button_->set_left_click(new SL::SimpleCommand<HistoryTree, const SL::Event &>(this, &HistoryTree::ChooseNode));   
    root_button_->set_node(ToolManager::getInstance().get_node());

    abstract_container_.add(root_button_);
    root_button_->set_pressed(true);
    add(&abstract_container_);
}

inline void HistoryWindow::HistoryTree::ChooseNode(const SL::Event &event)
{
    current_nodebutton = (NodeButton *)event.Oleg_.bcedata.id;
}

inline void HistoryWindow::HistoryTree::ClickSelect(const SL::Event &event)
{
    Canvas::getInstance()->set_image(HistoryManager::getInstance().get_state(current_nodebutton->get_node()));
    ToolManager::getInstance().set_node(current_nodebutton->get_node());
    history_window_->close(event);   
}

inline void HistoryWindow::HistoryTree::remove_branch(NodeButton *nodebutton)
{
    if (nodebutton == nullptr)
    {
        return;
    }

    for (auto child : nodebutton->nodes_)
    {
        
    }
}

inline void HistoryWindow::HistoryTree::ClickDelete(const SL::Event &event)
{
    HistoryManager::getInstance().delete_node(current_nodebutton->get_node());
}

inline void HistoryWindow::HistoryTree::redraw_buttons()
{
    redraw_button(root_button_);
}

inline void HistoryWindow::HistoryTree::redraw_button(NodeButton *button)
{
    if (button == nullptr)
    {
        return;
    }

    button->set_texture(HistoryManager::getInstance().get_state(button->get_node()).getTexture());
    
    for (auto button : button->nodes_)
    {
        redraw_button(button);
    }
}

inline void HistoryWindow::HistoryTree::ClickAdd(const SL::Event &event)
{
    int block_size = abstract_container_.get_shape().x_ / 27 * pow(3, 3 - current_nodebutton->layer_ - 1); 
    int offset_x = current_nodebutton->get_position().x_ + (int(current_nodebutton->nodes_.size()) - 1) * block_size;
    int offset_y = current_nodebutton->get_position().y_ + abstract_container_.get_shape().y_ / 27;

    NodeButton * new_node_button = new NodeButton(current_nodebutton->get_shape(),SL::Vector2d(offset_x, offset_y));
     HistoryManager::Node *new_node =  HistoryManager::getInstance().add_node(current_nodebutton->get_node());
    new_node_button->set_node(new_node);
    new_node_button->set_pressed(true);
    new_node_button->set_left_click(new SL::SimpleCommand<HistoryTree, const SL::Event &>(this, &HistoryTree::ChooseNode));
    
    new_node_button->layer_ = current_nodebutton->layer_ + 1;
    
    current_nodebutton->nodes_.push_back(new_node_button);
    abstract_container_.add(new_node_button);
}