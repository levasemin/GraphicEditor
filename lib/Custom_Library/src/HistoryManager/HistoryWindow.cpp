#include "HistoryWindow.hpp"

namespace CUST_SL
{
    class Canvas;
    
    HistoryWindow::HistoryWindow(SL::Vector2d shape, CUST_SL::Canvas *canvas) : SL::Application(nullptr),
        history_tree_(shape, this, canvas)
    {
        setMainWindow(&history_tree_);
    }

    void HistoryWindow::exec()
    {
        history_tree_.update();
        SL::Application::exec();
    }

    HistoryWindow::HistoryTree::HistoryTree(SL::Vector2d shape, HistoryWindow *history_window, Canvas *canvas) : 
        SL::MainWindow(shape, SL::Texture(SL::Color(static_cast<uint8_t>(69),  static_cast<uint8_t>(69),  static_cast<uint8_t>(69),   static_cast<uint8_t>(255)))),
        canvas_(canvas),
        tree_container_(shape * 2, SL::Vector2d(0, 0)),
        delete_button_(SL::Vector2d(50, 30), SL::Vector2d(shape.x_ - 70, 0.f),  SL::Texture(BUTTON_DARK_COLOR)),
        select_button_(SL::Vector2d(50, 30), SL::Vector2d(shape.x_ - 70, 60.f), SL::Texture(BUTTON_DARK_COLOR)),
        history_window_(history_window),
        node_button_shape_(shape / 5)
    {
        auto scroll_bar_history_window = new SL::DecoratorScrollBar(&tree_container_, shape - 100, SL::Vector2d(0, 0));

        delete_button_.setLeftClick(new SL::SimpleCommand<HistoryTree>(this, &HistoryTree::clickDelete));

        delete_button_.setText("delete");
        delete_button_.setTextColor(TEXT_COLOR);

        select_button_.setLeftClick(new SL::SimpleCommand<HistoryTree>(this, &HistoryTree::clickSelect));

        select_button_.setText("select");
        select_button_.setTextColor(TEXT_COLOR);

        add(scroll_bar_history_window);
        add(&delete_button_);
        add(&select_button_);
    }

    void HistoryWindow::HistoryTree::update()
    {
        if (HistoryManager::getInstance().getCurrentNode() == nullptr)
        {
            return;
        }
        
        bool flag = false;

        for (auto button : current_layer_buttons_)
        {
            if (button->get_node() == HistoryManager::getInstance().getCurrentNode())
            {
                flag = true;
                break;
            }
        }

        if (!flag)
        {
            for (auto button : current_layer_buttons_)
            {
                remove(button);
            }
            
            current_layer_buttons_.clear();
            
            auto root_button_ = new NodeButton(node_button_shape_,
                                    SL::Vector2d(10, 10));
            root_button_->layer_ = 0;
            root_button_->setLeftClick(new SL::SimpleCommand<HistoryTree, NodeButton *>(this, &HistoryTree::selectNode));   
            root_button_->set_node(HistoryManager::getInstance().getCurrentNode());

            tree_container_.add(root_button_);
            current_layer_buttons_.push_back(root_button_);
        }
        
        else
        {
            auto current_button = current_node_button_;
            current_button->setTexture(SL::Texture(current_button->get_node()->getState().getTexture()));
        }
    }

    void HistoryWindow::HistoryTree::selectNode(NodeButton *node_button)
    {
        for (int i = 0; i < current_layer_buttons_.size(); i++)
        {
            auto child_button = current_layer_buttons_[i];

            if (child_button->layer_ > node_button->layer_ || (child_button->layer_ == node_button->layer_ && child_button->get_node() == nullptr))
            {
                tree_container_.remove(child_button);
                delete child_button;
                current_layer_buttons_.erase(current_layer_buttons_.begin() + i);
                i--;
            }

        }

        current_node_button_ = node_button;
        
        for (int i = 0; i < current_node_button_->get_node()->getChildren().size(); i++)
        {
            auto new_node_button = new NodeButton(node_button_shape_, 
                                              SL::Vector2d(i, (current_node_button_->layer_ + 1)) * (node_button_shape_.x_ + 10) + 10);
            new_node_button->layer_ = node_button->layer_ + 1;
            new_node_button->set_node(current_node_button_->get_node()->getChildren()[i]);
            new_node_button->setLeftClick(new SL::SimpleCommand<HistoryTree, NodeButton *>(this, &HistoryTree::selectNode));   

            tree_container_.add(new_node_button);
            current_layer_buttons_.push_back(new_node_button);
        }

        auto add_button = new NodeButton(node_button_shape_, 
                                                SL::Vector2d(current_node_button_->get_node()->getChildren().size(), static_cast<size_t>(current_node_button_->layer_ + 1)) * (node_button_shape_.x_ + 10) + 10);
        add_button->layer_ = node_button->layer_ + 1;
        add_button->setText("add");
        add_button->setTextColor(TEXT_COLOR);
        add_button->setLeftClick(new SL::SimpleCommand<HistoryTree, NodeButton *>(this, &HistoryTree::addNode));
        
        tree_container_.add(add_button);
        current_layer_buttons_.push_back(add_button);
    }

    void HistoryWindow::HistoryTree::addNode(NodeButton *node_button)
    {
        auto add_button = new NodeButton(node_button_shape_, 
                                          SL::Vector2d(current_node_button_->get_node()->getChildren().size() + 1, static_cast<size_t>(node_button->layer_)) * (node_button_shape_.x_ + 10) + 10);
        add_button->layer_ = node_button->layer_;
        add_button->setText("add");
        add_button->setTextColor(TEXT_COLOR);
        add_button->setLeftClick(new SL::SimpleCommand<HistoryTree, NodeButton *>(this, &HistoryTree::addNode));
        
        tree_container_.add(add_button);
        current_layer_buttons_.push_back(add_button);

        auto new_node = HistoryManager::getInstance().addNode(current_node_button_->get_node());
        node_button->setLeftClick(new SL::SimpleCommand<HistoryTree, NodeButton *>(this, &HistoryTree::selectNode));   
        node_button->set_node(new_node);
    }

    void HistoryWindow::HistoryTree::clickDelete()
    {
        if (!current_node_button_)
        {
            return;
        }

        HistoryManager::getInstance().deleteNode(current_node_button_->get_node());
        int layer = current_node_button_->layer_;
        current_node_button_ = nullptr;

        for (int i = 0; i < current_layer_buttons_.size(); i++)
        {
            if (current_layer_buttons_[i]->layer_ == layer || current_layer_buttons_[i]->layer_ - 1 == layer)
            {
                tree_container_.remove(current_layer_buttons_[i]);
                auto butt =  current_layer_buttons_[i];
                current_layer_buttons_.erase(current_layer_buttons_.begin() + i);
                i--;
                delete butt;
            }
        }
    }

    void HistoryWindow::HistoryTree::clickSelect()
    {
        HistoryManager::getInstance().setCurrentNode(current_node_button_->get_node());
        canvas_->setNode(current_node_button_->get_node());
        history_window_->close();
    }
}