#include "HistoryManager.hpp"
HistoryManager::Node::Node(const SL::Image &image)
{
    mementos.push_back(new Memento(image));
}

const SL::Image &HistoryManager::Node::getState()
{
    return mementos[numCommands]->state_;
}

const std::vector<HistoryManager::Node *> &HistoryManager::Node::getChildren()
{
    return next_nodes;
}

HistoryManager &HistoryManager::getInstance()
{
    static HistoryManager manager;
    return manager;
}

HistoryManager::Node *HistoryManager::create_root(const SL::Image &image)
{
    Node *new_node   = new Node(image);

    root_ = new_node;
    return new_node;
}

void HistoryManager::add_state(HistoryManager::Node *node, const SL::Image &image)
{
    if (node->mementos.size() == max_backup_ - 1)
    {
        node->mementos.pop_front();
        node->mementos.push_back(nullptr);
        node->numCommands --;
    }

    node->numCommands++;

    Memento *new_memento = new Memento(image);
    node->mementos[node->numCommands] = new_memento;
    node->max_forward = node->numCommands;
}

const SL::Image &HistoryManager::undo_state(HistoryManager::Node *node)
{
    if (node->numCommands == 0)
    {
        return node->mementos[0]->state_;
    }

    return node->mementos[--node->numCommands]->state_;
}

const SL::Image &HistoryManager::redo_state(Node *node)
{
    if (node->numCommands >= node->max_forward)
    {
        return node->mementos[node->numCommands]->state_;
    }
    
    return node->mementos[++node->numCommands]->state_;

}

HistoryManager::Node *HistoryManager::add_node(HistoryManager::Node *parent)
{
    Node *new_node = new Node(parent->getState());
    new_node->parent = parent;
    parent->next_nodes.push_back(new_node);
    return new_node;
}

void HistoryManager::delete_node(HistoryManager::Node *node)
{
    auto &parent_nodes = node->parent->next_nodes;
    auto iter_node = std::find(parent_nodes.begin(), parent_nodes.end(), node);
    parent_nodes.erase(iter_node);

    for (auto child : node->next_nodes)
    {
        child->parent = node->parent;

        parent_nodes.insert(iter_node, child);
    }

    for (auto memento : node->mementos)
    {
        delete memento;
    }

    delete node;
}

void HistoryManager::clear_branch(HistoryManager::Node *node)
{
    if (node == nullptr)
    {
        return ;
    }

    for (auto child: node->next_nodes)
    {
        clear_branch(child);
        delete_node(node);
    }
}