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
	"oooooooooo",
	"ooo-oooooo",
	};


	void LevelManager::DrawLevel(Surface* screen, const int level)
	{
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				float tx = static_cast<float>(map[y][x * 2] - 'a');
				float ty = static_cast<float>(map[y][x * 2 + 1] - 'a');
				DrawTile(screen, { static_cast<float>(x * 64), static_cast<float>(y * 64) }, {tx, ty});
			}
		}
	}

	// Sends the state of the specified level
	LevelManager::LevelState LevelManager::GetLevelState(const int level) const { return state[level]; }

	LevelManager::TileContents LevelManager::GetContents(const Location& loc) const
	{
		char content = collisionMap[int(loc.y) / 64][int(loc.x) / 64];
		std::cout << "TileContent: " << content << std::endl;

		switch (content)
		{
		case'-':
			return TileContents::Obstacle;
			break;
		case 'o':
			return TileContents::Empty;
			break;
		default:
			std::cout << "Unknown content declaration, returned empty." << std::endl;
			return TileContents::Empty;
			break;
		}

		return TileContents::Empty;
	}

	void LevelManager::DrawTile(Surface* screen, const Location& loc, const Location& tile)
	{
		Pixel* src = tiles.GetBuffer() + static_cast<int>(tile.x) * 64 + (static_cast<int>(tile.y) * 64) * 768;
		Pixel* dst = screen->GetBuffer() + static_cast<int>(loc.x) + static_cast<int>(loc.y) * 800;

		for (int i = 0; i < 64; i++, src += 768, dst += 800)
		{
			for (int j = 0; j < 64; j++)
			{
				dst[j] = src[j];
			}
		}
	}

};
