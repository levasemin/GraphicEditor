#include "HistoryManager.hpp"
HistoryManager::Node::Node(const SL::Image &image)
{
    mementos_.push_back(new Memento(image));
}

HistoryManager::Node::~Node()
{
    for (auto memento : mementos_)
    {
        delete memento;
    }
}

const SL::Image &HistoryManager::Node::getState() const
{
    return mementos_[numCommands]->state_;
}

const std::vector<HistoryManager::Node *> &HistoryManager::Node::getChildren() const
{
    return next_nodes_;
}

HistoryManager::~HistoryManager()
{
    deleteBranch(root_);
}

HistoryManager &HistoryManager::getInstance()
{
    static HistoryManager manager;
    return manager;
}

HistoryManager::Node *HistoryManager::createHistory(const SL::Image &image)
{
    Node *new_node   = new Node(image);

    root_ = new_node;
    current_node_ = new_node;
    
    return new_node;
}

void HistoryManager::deleteHistory()
{
    root_ = nullptr;
    current_node_ = nullptr;

    deleteBranch(root_);
}

void HistoryManager::setCurrentNode(Node *node)
{
    current_node_ = node;
}

HistoryManager::Node *HistoryManager::getCurrentNode()
{
    return current_node_;
}


void HistoryManager::Node::addState(const SL::Image &image)
{
    if (mementos_.size() == max_backup_ - 1)
    {
        mementos_.pop_front();
        mementos_.push_back(nullptr);
        numCommands --;
    }

    numCommands++;

    Memento *new_memento = new Memento(image);
    mementos_[numCommands] = new_memento;
    max_forward = numCommands;
}

const SL::Image &HistoryManager::Node::undoState()
{
    if (numCommands == 0)
    {
        return mementos_[0]->state_;
    }

    return mementos_[--numCommands]->state_;
}

const SL::Image &HistoryManager::Node::redoState()
{
    if (numCommands >= max_forward)
    {
        return mementos_[numCommands]->state_;
    }
    
    return mementos_[++numCommands]->state_;

}

HistoryManager::Node *HistoryManager::addNode(HistoryManager::Node *parent)
{
    if (parent == nullptr)
    {
        return nullptr;
    }

    Node *new_node = new Node(parent->getState());
    new_node->parent = parent;
    parent->next_nodes_.push_back(new_node);
    return new_node;
}

void HistoryManager::deleteNode(HistoryManager::Node *node)
{
    if (node == nullptr)
    {
        return;
    }

    if (node == root_)
    {
        deleteHistory();
        return;
    }

    auto &parent_nodes = node->parent->next_nodes_;
    auto iter_node = std::find(parent_nodes.begin(), parent_nodes.end(), node);
    
    parent_nodes.erase(iter_node);
    
    for (auto child : node->next_nodes_)
    {
        child->parent = node->parent;

        parent_nodes.push_back(child);
    }

    delete node;
}

void HistoryManager::deleteBranch(HistoryManager::Node *node)
{
    if (node == nullptr)
    {
        return;
    }

    for (auto child: node->next_nodes_)
    {
        deleteBranch(child);
        deleteNode(node);
    }
}