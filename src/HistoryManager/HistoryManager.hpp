#pragma once

#include <iostream>
#include <vector>
#include "Classes/Image.h"
#include <deque>

const int max_backup_ = 32;

class HistoryManager;

class Memento
{
  public:
    Memento(const SL::Image &image):
        state_()
    {
        state_ = image;
    }
  private:
    friend class HistoryManager;
    SL::Image state_;
};


class HistoryManager
{
    HistoryManager()
    {}

    HistoryManager(const HistoryManager &that) = delete;
    HistoryManager &operator=(const HistoryManager &that) = delete;

    HistoryManager(const HistoryManager &&that) = delete;
    HistoryManager &operator=(const HistoryManager &&that) = delete;
public:
    
    struct Node
    {
        Node *parent;
        int numCommands;
        int max_forward;
        std::vector<Node *> next_nodes;
        std::deque<Memento *> mementos;
    };
    
    Node *root_ = nullptr;

    static HistoryManager &getInstance()
    {
        static HistoryManager manager;
        return manager;
    }

    Node *create_root(const SL::Image &image)
    {
        Memento *memento = new Memento(image);
        Node *new_node = new Node({nullptr, 0, 0, {}, {}});
        new_node->mementos.push_back(memento);

        root_ = new_node;
        return new_node;
    }

    void add_state(Node *node, const SL::Image &image)
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

    const SL::Image &undo_state(Node *node)
    {
        if (node->numCommands == 0)
        {
            return node->mementos[0]->state_;
        }

        return node->mementos[--node->numCommands]->state_;
    }

    const SL::Image &redo_state(Node *node)
    {
        if (node->numCommands >= node->max_forward)
        {
            return node->mementos[node->numCommands]->state_;
        }
        
        return node->mementos[++node->numCommands]->state_;

    }

    Node *add_node(Node *parent)
    {
        Memento *new_memento = new Memento(*parent->mementos[parent->numCommands]);
        Node *new_node = new Node({parent, 0, 0, {}, {}});
        new_node->mementos.push_back(new_memento);
        parent->next_nodes.push_back(new_node);
        return new_node;
    }

    void delete_node(Node *node)
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

    void clear_branch(Node *node)
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

    const SL::Image &get_state(Node *node)
    {
        return node->mementos[node->numCommands]->state_;
    }
};
