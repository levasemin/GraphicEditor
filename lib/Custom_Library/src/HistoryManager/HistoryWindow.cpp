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

    void HistoryWindow::close()
    {
        NodeButton::current_button_ = nullptr;
        SL::Application::close();        
    }

    HistoryWindow::HistoryTree::HistoryTree(SL::Vector2d shape, HistoryWindow *history_window, Canvas *canvas) : 
        SL::MainWindow(shape, SL::Texture(SL::Color((uint8_t)69,  (uint8_t)69,  (uint8_t)69,   uint8_t(255)))),
        canvas_(canvas),
        tree_container_(shape * 2, SL::Vector2d(0, 0)),
        delete_button_(SL::Vector2d(50, 30), SL::Vector2d(shape.x_ - 70, 0.f),  SL::Texture(BUTTON_DARK_COLOR)),
        select_button_(SL::Vector2d(50, 30), SL::Vector2d(shape.x_ - 70, 60.f), SL::Texture(BUTTON_DARK_COLOR)),
        history_window_(history_window)
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
            current_layer_buttons_.clear();
            
            auto root_button_ = new NodeButton(getShape() / 5, 
                                    SL::Vector2d(10, 10));
            root_button_->layer_ = 0;
            root_button_->setLeftClick(new SL::SimpleCommand<HistoryTree, NodeButton *>(this, &HistoryTree::selectNode));   
            root_button_->set_node(HistoryManager::getInstance().getCurrentNode());

            current_node_button_ = root_button_;

            tree_container_.add(root_button_);
            current_layer_buttons_.push_back(root_button_);

            auto add_button = new NodeButton(current_node_button_->getShape(), 
            SL::Vector2d(current_node_button_->get_node()->getChildren().size(), size_t(current_node_button_->layer_ + 1)) * (current_node_button_->getShape().x_ + 10.f) + 10);
            
            add_button->layer_ = 1;
            add_button->setText("add");
            add_button->setTextColor(TEXT_COLOR);
        
            add_button->setLeftClick(new SL::SimpleCommand<HistoryTree, NodeButton *>(this, &HistoryTree::addNode));
            tree_container_.add(add_button);

            current_layer_buttons_.push_back(add_button);

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

            if (child_button->layer_ > node_button->layer_)
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
            auto new_node_button = new NodeButton(current_node_button_->getShape(), 
                                              SL::Vector2d(i, (current_node_button_->layer_ + 1)) * (current_node_button_->getShape().x_ + 10) + 10);
            new_node_button->layer_ = node_button->layer_ + 1;
            new_node_button->set_node(current_node_button_->get_node()->getChildren()[i]);
            new_node_button->setLeftClick(new SL::SimpleCommand<HistoryTree, NodeButton *>(this, &HistoryTree::selectNode));   

            tree_container_.add(new_node_button);
            current_layer_buttons_.push_back(new_node_button);
        }

        auto add_button = new NodeButton(current_node_button_->getShape(), 
                                                SL::Vector2d(current_node_button_->get_node()->getChildren().size(), size_t(current_node_button_->layer_ + 1)) * (current_node_button_->getShape().x_ + 10) + 10);
        add_button->layer_ = node_button->layer_ + 1;
        add_button->setText("add");
        add_button->setTextColor(TEXT_COLOR);
        add_button->setLeftClick(new SL::SimpleCommand<HistoryTree, NodeButton *>(this, &HistoryTree::addNode));
        
        tree_container_.add(add_button);
        current_layer_buttons_.push_back(add_button);
    }

    void HistoryWindow::HistoryTree::addNode(NodeButton *node_button)
    {
        auto add_button = new NodeButton(current_node_button_->getShape(), 
                                          SL::Vector2d(current_node_button_->get_node()->getChildren().size() + 1, size_t(node_button->layer_)) * (current_node_button_->getShape().x_ + 10) + 10);
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
        HistoryManager::getInstance().deleteNode(current_node_button_->get_node());
        tree_container_.remove(current_node_button_);
        
        for (auto curr_button = std::find(current_layer_buttons_.begin(), current_layer_buttons_.end(), current_node_button_); curr_button < current_layer_buttons_.end(); curr_button++)
        {
            if ((*curr_button)->layer_ == current_node_button_->layer_)
            {
                (*curr_button)->setPosition((*curr_button)->getPosition());
            }
        }

        delete current_node_button_;
    }

    void HistoryWindow::HistoryTree::clickSelect()
    {
        HistoryManager::getInstance().setCurrentNode(current_node_button_->get_node());
        canvas_->setNode(current_node_button_->get_node());
        history_window_->close();
    }
}