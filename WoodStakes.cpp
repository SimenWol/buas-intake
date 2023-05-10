#include "WoodStakes.h"
#include "LevelManager.h"

#include <iostream>

namespace Tmpl8
{
	// Constructor //
	WoodStakes::WoodStakes()
		:stakes(new Surface("assets/Enemies/wood_stakes.png"), 1)
	{}

	// Draw function
	void WoodStakes::Draw(Surface* screen, const int tilex, const int tiley, const Location& drawOffset)
	{
		stakes.Draw(screen, tilex * LevelManager::tileSize - static_cast<int>(drawOffset.x), 
			tiley * LevelManager::tileSize - static_cast<int>(drawOffset.y));
	}

	// Function that checks more precise collision & then calls level death if there is collision.
	void WoodStakes::Trigger(LevelManager& level, Player& player, MenuManager& menu, const Location& tileLoc)
	{
		// Get/Set location of wood stakes hitbox.
		Location topLeft = { 0.0f, 0.0f };
		Location bottomRight = { 0.0f, 0.0f };

		bottomRight.x = tileLoc.x + static_cast<float>(level.tileSize) / 2;
		bottomRight.y = tileLoc.y + static_cast<float>(level.tileSize) / 2;
		topLeft.x = tileLoc.x - static_cast<float>(level.tileSize) / 2;
		topLeft.y = tileLoc.y + 18 - static_cast<float>(level.tileSize) / 2;
		
		// Check collision & call functions.
		if (player.CheckCollision(topLeft, bottomRight))
		{
			level.Death(player, menu);
			std::cout << "WoodStakes triggered!" << std::endl;
		}
	}
};