#include "WoodStakes.h"
#include "LevelManager.h"

#include <iostream>

namespace Tmpl8
{
	WoodStakes::WoodStakes()
		:stakes(new Surface("assets/Enemies/wood_stakes.png"), 1)
	{}

	void WoodStakes::Draw(Surface* screen, const int tilex, const int tiley)
	{
		stakes.Draw(screen, tilex * LevelManager::tileSize, tiley * LevelManager::tileSize);
	}

	void WoodStakes::Trigger(LevelManager& level, Player& player, MenuManager& menu)
	{
		level.Death(player, menu);
		// End Timer

		std::cout << "WoodStakes triggered!" << std::endl;
	}
};