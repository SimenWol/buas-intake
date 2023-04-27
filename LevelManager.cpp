#include "LevelManager.h"
#include "surface.h"
#include "Player.h"

#include <iostream>

namespace Tmpl8
{
	Surface tiles("assets/Temp/tileset_forest.png");

	// TODO: https://github.com/nlohmann/json JSON LEVEL LOADING --> level definitions --> Data Driven!!
	// ASEPRITE? -> SPRITE DRAWIN

	LevelManager::LevelManager()
	{
		state[0] = LevelState::Open;
	}

	void LevelManager::LoadLevel(const int level, Player& player)
	{
		currentLevel = level;
		std::cout << level << " " << numLevels << std::endl;

		if (level > numLevels || level <= 0) { std::cout << "Level cannot be found or does not exist." << std::endl; }
		else
		{
			Reset(level, player);
		}
	}

	void LevelManager::DrawLevel(Surface* screen, const int level)
	{
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				float tx = static_cast<float>(map[y][x * 2] - 'a');
				float ty = static_cast<float>(map[y][x * 2 + 1] - 'a');
				DrawTile(screen, { static_cast<float>(x * tileSize), static_cast<float>(y * tileSize) }, {tx, ty});
			}
		}
	}

	// Sends the state of the specified level
	LevelManager::LevelState LevelManager::GetLevelState(const int level) const { return state[level - 1]; }

	// Returns contents from the cell.
	LevelManager::TileContents LevelManager::GetContents(const Location& loc) const
	{
		if ((int(loc.x) > 10 * tileSize) || (int(loc.y) > 8 * tileSize)) { return TileContents::Empty; }

		char content = collisionMap[int(loc.y) / tileSize][int(loc.x) / tileSize];
		// std::cout << "TileContent: " << content << std::endl;

		switch (content)
		{
		case 'o':
			return TileContents::Empty;
			break;
		case'-':
			return TileContents::Obstacle;
			break;
		default:
			std::cout << "Unknown content declaration, returned empty." << std::endl;
			return TileContents::Empty;
			break;
		}
	}

	int LevelManager::GetCurrentLevel() const { return currentLevel; }

	void LevelManager::DrawTile(Surface* screen, const Location& loc, const Location& tile)
	{
		Pixel* src = tiles.GetBuffer() + static_cast<int>(tile.x) * tileSize + (static_cast<int>(tile.y) * tileSize) * 768;
		Pixel* dst = screen->GetBuffer() + static_cast<int>(loc.x) + static_cast<int>(loc.y) * 800;

		for (int i = 0; i < tileSize; i++, src += 768, dst += 800)
		{
			for (int j = 0; j < tileSize; j++)
			{
				dst[j] = src[j];
			}
		}
	}

	void LevelManager::Reset(const int level, Player& player)
	{
		switch (level)
		{
		case 1:
			player.Reset();
			player.SetLoc(startLoc1);
			break;
		default:
			std::cout << "Cannot reset specified level." << std::endl;
			break;
		}
		// Reset Timer
		// Reset whatever else needed
	}

};
