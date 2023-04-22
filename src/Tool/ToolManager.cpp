#include "ToolManager.h"

int ToolManager::numCommands_(-1);
int ToolManager::max_forward_(0);

std::deque<Memento *> ToolManager:: mementoList_(MAX_BACKUP);