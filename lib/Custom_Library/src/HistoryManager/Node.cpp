#include "Node.hpp"

namespace CUST_SL
{
    HistoryManager::Node::Node () 
    {
    }

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
    
    void HistoryManager::Node::addState(const SL::Image &image)
    {
        if (numCommands == max_backup_ - 1)
        {
            mementos_.pop_front();
            numCommands --;
        }

        numCommands++;

        Memento *new_memento = new Memento(image);
        
        for (auto iter = mementos_.end() - 1; iter >= mementos_.begin() + numCommands; iter--)
        {
            delete *iter;
            mementos_.pop_back();
        }

        mementos_.push_back(new_memento);

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

    void HistoryManager::Node::save(boost::archive::binary_oarchive & ar, const unsigned int version) const
    {
        ar & max_backup_;
        ar & numCommands;
        ar & max_forward;
        ar & parent;
        ar & next_nodes_;
        ar & mementos_;
    }

    void HistoryManager::Node::load(boost::archive::binary_iarchive & ar, const unsigned int version)
    {
        ar & max_backup_;
        ar & numCommands;
        ar & max_forward;
        ar & parent;
        ar & next_nodes_;
        ar & mementos_;
    }
}