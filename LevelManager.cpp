#include "LevelManager.h"

namespace Tmpl8
{
	// void LevelManager::LoadLevel(const int level) const {}
// void LevelManager::DrawLevel(const int level) const {}

// Sends the state of the specified level
	LevelManager::LevelState LevelManager::GetLevelState(const int level) const { return state[level]; }

};
