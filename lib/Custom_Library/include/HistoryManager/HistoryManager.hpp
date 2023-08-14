#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/deque.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "Memento.hpp"

#include "GraphLib.hpp"

namespace CUST_SL
{
    class Canvas;

    class HistoryManager
    {
    public:
        class Node;

        static HistoryManager &getInstance();

        Node *createHistory(const SL::Image &image);
        void deleteHistory();

        void setCurrentNode(Node *node);
        Node *getCurrentNode();

        void addState(Node *node, const SL::Image &image);
        
        Node *addNode(Node *parent);
        void deleteNode(Node *node);
        
        void deleteBranch(Node *node);

        void save(std::string filename, Node *node = nullptr) const;
        void load(std::string filename, Canvas *canvas);

        BOOST_SERIALIZATION_SPLIT_MEMBER()

        friend class boost::serialization::access;

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

        void save(boost::archive::binary_oarchive &ar, const unsigned int version, Node *curr_node = nullptr) const;
        void load(boost::archive::binary_iarchive &ar, const unsigned int version, Node *curr_node = nullptr);
    };
}