#include "Spikes.h"
#include "LevelManager.h"

#include <iostream>

namespace Tmpl8
{
	Spikes::Spikes()
		:spikesSprite(new Surface("assets/Enemies/spikes.png"), 4)
	{}

	void Spikes::Draw(Surface* screen, const int tilex, const int tiley, const Type type, const Location& drawOffset)
	{
		switch (type)
		{
		case Type::Big:
			spikesSprite.SetFrame(0);
			spikesSprite.Draw(screen, tilex * LevelManager::tileSize - static_cast<int>(drawOffset.x), 
				tiley * LevelManager::tileSize - static_cast<int>(drawOffset.y));
			break;
		case Type::Medium:
			spikesSprite.SetFrame(1);
			spikesSprite.Draw(screen, tilex * LevelManager::tileSize - static_cast<int>(drawOffset.x),
				tiley * LevelManager::tileSize - static_cast<int>(drawOffset.y));
			break;
		case Type::Small:
			spikesSprite.SetFrame(2);
			spikesSprite.Draw(screen, tilex * LevelManager::tileSize - static_cast<int>(drawOffset.x),
				tiley * LevelManager::tileSize - static_cast<int>(drawOffset.y));
			break;
		default:
			std::cout << "Unknown spike type." << std::endl;
			break;
		}
	}

	void Spikes::Trigger(LevelManager& level, Player& player, MenuManager& menu, const Type type)
	{
		level.Death(player, menu);

		std::cout << "Spikes triggered!" << std::endl;
	}
};