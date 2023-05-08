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

	void WoodStakes::Trigger(LevelManager& level, Player& player, MenuManager& menu, const Location& tileLoc)
	{
		Location topLeft = { 0.0f, 0.0f };
		Location bottomRight = { 0.0f, 0.0f };

		bottomRight.x = tileLoc.x + static_cast<float>(level.tileSize) / 2;
		bottomRight.y = tileLoc.y + static_cast<float>(level.tileSize) / 2;
		topLeft.x = tileLoc.x - static_cast<float>(level.tileSize) / 2;
		topLeft.y = tileLoc.y + 18 - static_cast<float>(level.tileSize) / 2;

		if (player.CheckCollision(topLeft, bottomRight))
		{
			level.Death(player, menu);
			std::cout << "WoodStakes triggered!" << std::endl;
		}
	}
};