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
		case Type::Floor:
			spikesSprite.SetFrame(3);
			spikesSprite.Draw(screen, tilex * LevelManager::tileSize - static_cast<int>(drawOffset.x),
				tiley * LevelManager::tileSize - static_cast<int>(drawOffset.y));
			break;
		default:
			std::cout << "Unknown spike type." << std::endl;
			break;
		}
	}

	void Spikes::Trigger(LevelManager& level, Player& player, MenuManager& menu, const Type type, const Location& tileLoc)
	{
		Location topLeft = { 0.0f, 0.0f };
		Location bottomRight = { 0.0f, 0.0f };

		bottomRight.x = tileLoc.x + static_cast<float>(level.tileSize) / 2;
		bottomRight.y = tileLoc.y + static_cast<float>(level.tileSize) / 2;
		topLeft.x = tileLoc.x - static_cast<float>(level.tileSize) / 2;

		if (type == Type::Floor) { return; }
		if (type == Type::Small) { topLeft.y = tileLoc.y + 30 - static_cast<float>(level.tileSize) / 2; }
		if (type == Type::Medium) { topLeft.y = tileLoc.y + 18 - static_cast<float>(level.tileSize) / 2; }
		if (type == Type::Big) { topLeft.y = tileLoc.y + 9 - static_cast<float>(level.tileSize) / 2; }

		if (player.CheckCollision(topLeft, bottomRight))
		{
			level.Death(player, menu);
			std::cout << "Spikes triggered!" << std::endl;
		}
	}
};