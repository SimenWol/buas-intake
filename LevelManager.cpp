#include "LevelManager.h"
#include "surface.h"

#include <iostream>

namespace Tmpl8
{
	Surface tiles("assets/Temp/tileset_forest.png");

	// TODO: https://github.com/nlohmann/json JSON LEVEL LOADING --> level definitions --> Data Driven!!
	// ASEPRITE? -> SPRITE DRAWIN

	char map[8][21] = {
		"cbcbcbcbcbcbcbcbcbcb",
		"cbcbcbcbcbcbcbcbcbcb",
		"cbcbcbcbcbcbcbcbcbcb",
		"cbcbcbcbcbcbcbcbcbcb",
		"cbcbcbcbcbcbcbcbcbcb",
		"cbcbcbcbcbcbcbcbcbcb",
		"cbcbcbcbcbcbcbcbcbcb",
		"cbcbcbcbcbcbcbcbcbcb",
	};

	char collisionMap[8][11] = {
	"oooooooooo",
	"oooooooooo",
	"oooooooooo",
	"oooooooooo",
	"oooooooooo",
	"oooooooooo",
	"-oooo-oooo",
	"----------",
	};


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
	LevelManager::LevelState LevelManager::GetLevelState(const int level) const { return state[level]; }

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
			// std::cout << "Unknown content declaration, returned empty." << std::endl;
			return TileContents::Empty;
			break;
		}
	}

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

};
