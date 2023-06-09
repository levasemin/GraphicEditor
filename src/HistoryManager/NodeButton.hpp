#include "Classes/Texture.h"
#include "Classes/Vector2d.h"
#include "GraphLib.h"
#include "HistoryManager.hpp"
#include "Widget/Button.h"

class NodeButton : public SL::Button
{
    HistoryManager::Node *node_;
public:
    std::vector<NodeButton *> nodes_;
    int layer_ = 0;
    
    NodeButton(SL::Vector2d shape, SL::Vector2d position, SL::Texture texture = SL::Texture(SL::Color::White)) : SL::Button(shape, position, texture)
    {}

    void set_node(HistoryManager::Node *node)
    {
        set_texture(HistoryManager::getInstance().get_state(node).getTexture());
        node_ = node;
    }

    HistoryManager::Node *get_node()
    {
        return node_;
    }
};