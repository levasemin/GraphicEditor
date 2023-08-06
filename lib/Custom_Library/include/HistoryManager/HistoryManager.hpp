#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include "GraphLib.hpp"

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
    
    class Node
    {
    public:
        Node(const SL::Image &);

        const SL::Image &getState();
        const std::vector<Node *> &getChildren();
        
        friend class HistoryManager;
    private:
        int numCommands = 0;
        int max_forward = 0;

        Node *parent = nullptr;
        std::vector<Node *> next_nodes;
        std::deque<Memento *> mementos;
    };

    static HistoryManager &getInstance();

    Node *create_root(const SL::Image &image);
    void add_state(Node *node, const SL::Image &image);

    const SL::Image &undo_state(Node *node);
    const SL::Image &redo_state(Node *node);
    
    Node *add_node(Node *parent);
    void delete_node(Node *node);
    
    void clear_branch(Node *node);

private:
    Node *root_ = nullptr;
};