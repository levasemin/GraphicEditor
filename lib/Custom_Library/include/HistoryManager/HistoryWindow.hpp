#pragma once

#include "Color.hpp"
#include "GraphLib.hpp"
#include "HistoryManager.hpp"
#include "NodeButton.hpp"
#include "Canvas.hpp"
#include "ToolLibrary.hpp"

namespace CUST_SL
{
    class HistoryWindow : SL::Application
    {
    public:
        class HistoryTree: public SL::MainWindow
        {
        public:
            HistoryTree(SL::Vector2d shape, HistoryWindow *history_window, CUST_SL::Canvas *canvas);

            void selectNode(NodeButton *node_button);
            void addNode(NodeButton *node_button);

            void clickDelete();
            void clickSelect();

            void update();            
            friend class HistoryWindow;
        private:
            Canvas *canvas_;
            SL::Container tree_container_;
            SL::Button delete_button_;
            SL::Button select_button_;
            NodeButton *current_node_button_ = nullptr;
            std::vector<NodeButton *> current_layer_buttons_;
            HistoryWindow *history_window_;
        }; 

        HistoryWindow(SL::Vector2d shape, CUST_SL::Canvas *canvas);

        void exec();
        void close();
        
        private:
            HistoryTree history_tree_;
    };
}