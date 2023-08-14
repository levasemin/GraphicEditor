#include "HistoryManager.hpp"
#include "Node.hpp"
#include "Canvas.hpp"

namespace CUST_SL
{
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


    void HistoryManager::save(std::string filename, Node *node) const
    {
        if (node == nullptr)
        {
            node = root_;
        }

        std::ofstream ofs(filename, std::ios::out);
        boost::archive::binary_oarchive oa(ofs, boost::archive::no_header |
                                                boost::archive::no_tracking |
                                                boost::archive::no_codecvt |
                                                boost::archive::no_xml_tag_checking);

        oa & node;

        save(oa, 1, node);
    }


    void HistoryManager::save(boost::archive::binary_oarchive &ar, const unsigned int version, Node *curr_node) const
    {
        if (curr_node == nullptr)
        {
            return;
        }

        for(auto node : curr_node->getChildren())
        {
            ar & node;
            
            save(ar, version, node);
        }
    }


    void HistoryManager::load(std::string filename, CUST_SL::Canvas *canvas)
    {
        std::ifstream ifs(filename);
        boost::archive::binary_iarchive ia(ifs, boost::archive::no_header |
                                                boost::archive::no_tracking |
                                                boost::archive::no_codecvt |
                                                boost::archive::no_xml_tag_checking);
        
        deleteBranch(root_);

        ia & root_;
        
        current_node_ = root_;
                
        load(ia, 1, root_);

        canvas->setNode(root_);
    }


    void HistoryManager::load(boost::archive::binary_iarchive &ar, const unsigned int version, Node *curr_node)
    {
        if (curr_node == nullptr)
        {
            return;
        }

        for(auto node : curr_node->getChildren())
        {
            ar & node;
            
            load(ar, version, node);
        }
    }
}