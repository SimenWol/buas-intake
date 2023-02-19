#include "LevelManager.h"

// Sends the state of the specified level
LevelManager::LevelState LevelManager::GetLevelState(const int level) const { return state[level]; }
