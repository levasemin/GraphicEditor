#include "ToolManager.hpp"

int ToolManager::numCommands_(-1);
int ToolManager::max_forward_(0);

HistoryManager::Node *ToolManager::current_node = nullptr;