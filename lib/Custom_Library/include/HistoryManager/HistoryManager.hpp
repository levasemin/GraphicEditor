#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include "GraphLib.hpp"

class HistoryManager;

class Memento
{
public:
    Memento(const SL::Image &image):
        state_()
    {
        state_ = image;
    }
    friend class HistoryManager;

private:
    SL::Image state_;
};


class HistoryManager
{
public:
    
    class Node
    {
    public:
        Node(const SL::Image &);

        const SL::Image &getState() const;
        void addState(const SL::Image &image);

        const SL::Image &redoState();
        const SL::Image &undoState();

        const std::vector<Node *> &getChildren() const;
        
        friend class HistoryManager;
    private:
        const int max_backup_ = 32;

        int numCommands = 0;
        int max_forward = 0;

        Node *parent = nullptr;

        std::vector<Node *> next_nodes_;
        std::deque<Memento *> mementos_;

        ~Node();
    };

    static HistoryManager &getInstance();

    Node *createHistory(const SL::Image &image);
    void deleteHistory();

    void setCurrentNode(Node *node);
    Node *getCurrentNode();

    void addState(Node *node, const SL::Image &image);
    
    Node *addNode(Node *parent);
    void deleteNode(Node *node);
    
    void deleteBranch(Node *node);

private:
    Node *root_ = nullptr;
    Node *current_node_ = nullptr;

    HistoryManager()
    {}

    HistoryManager(const HistoryManager &that) = delete;
    HistoryManager &operator=(const HistoryManager &that) = delete;

    HistoryManager(const HistoryManager &&that) = delete;
    HistoryManager &operator=(const HistoryManager &&that) = delete;

    ~HistoryManager();
};