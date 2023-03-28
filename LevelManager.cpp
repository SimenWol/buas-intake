#include "LevelManager.h"
#include "surface.h"

namespace Tmpl8
{
	Surface tiles("assets/Temp/tileset_forest.png");

	char map[5][21] = {
		"abbbcbabbbcbdbbbabcb",
		"cbbbabcbbbabcbabbbdb",
		"ababababcbcbcbdbdbdb",
		"bbbbbbbbbbbbbbabbbbb",
		"cbabcbabcbabcbbbabdb",
	};

	void LevelManager::DrawLevel(Surface* screen, const int level)
	{
		for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				float tx = static_cast<float>(map[y][x * 2] - 'a');
				float ty = static_cast<float>(map[y][x * 2 + 1] - 'a');
				DrawTile(screen, { 0.0f, 0.0f }, { tx,ty });
			}
		}
	}

	// Sends the state of the specified level
	LevelManager::LevelState LevelManager::GetLevelState(const int level) const { return state[level]; }

	void LevelManager::DrawTile(Surface* screen, const Location& loc, const Location& tile)
	{
		Pixel* src = tiles.GetBuffer() + 16 + static_cast<int>(tile.x) * 16 + (16 + static_cast<int>(tile.y) * 16) * 595;
		Pixel* dst = screen->GetBuffer() + static_cast<int>(loc.x) + static_cast<int>(loc.y) * 800;

		for (int i = 0; i < 16; i++, src += 595, dst += 800)
		{
			for (int j = 0; j < 16; j++) { dst[j] = src[j]; }
		}
	}

};
