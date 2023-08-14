#pragma once
#include "HistoryManager.hpp"

namespace CUST_SL
{
    class HistoryManager::Node
    {
    public:
        const SL::Image &getState() const;
        void addState(const SL::Image &image);

        const SL::Image &redoState();
        const SL::Image &undoState();

        const std::vector<Node *> &getChildren() const;
        
        void save(boost::archive::binary_oarchive & ar, const unsigned int version) const;

        void load(boost::archive::binary_iarchive & ar, const unsigned int version);
    
        BOOST_SERIALIZATION_SPLIT_MEMBER()

        friend class HistoryManager;
        friend class Memento;
        friend class boost::serialization::access;
        friend struct boost::archive::detail::heap_allocation<Node>;
    
    private:
        int max_backup_ = 32;

        int numCommands = 0;
        int max_forward = 0;

        Node *parent = nullptr;

        std::vector<Node *> next_nodes_;
        std::deque<Memento *> mementos_;

        Node ();
        
        Node(const SL::Image &);

        ~Node();
    };
}