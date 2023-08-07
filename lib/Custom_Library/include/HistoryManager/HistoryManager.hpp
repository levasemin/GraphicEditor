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

        const SL::Image &getState() const;
        void addState(const SL::Image &image);

        const SL::Image &redoState();
        const SL::Image &undoState();

        const std::vector<Node *> &getChildren() const;
        
        friend class HistoryManager;
    private:
        ~Node();

        int numCommands = 0;
        int max_forward = 0;

        Node *parent = nullptr;
        std::vector<Node *> next_nodes_;
        std::deque<Memento *> mementos_;
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
};