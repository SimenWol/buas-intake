#include "WoodStakes.h"
#include "LevelManager.h"

#include <iostream>

namespace Tmpl8
{
	WoodStakes::WoodStakes()
		:stakes(new Surface("assets/Enemies/wood_stakes.png"), 1)
	{}

	void WoodStakes::Draw(Surface* screen, const int tilex, const int tiley, const Location& drawOffset)
	{
		stakes.Draw(screen, tilex * LevelManager::tileSize - static_cast<int>(drawOffset.x), 
			tiley * LevelManager::tileSize - static_cast<int>(drawOffset.y));
	}

	void WoodStakes::Trigger(LevelManager& level, Player& player, MenuManager& menu)
	{
		level.Death(player, menu);

		std::cout << "WoodStakes triggered!" << std::endl;
	}
};