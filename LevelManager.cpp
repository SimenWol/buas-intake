#include "LevelManager.h"
#include "surface.h"
#include "Player.h"
#include "Finish.h"

#include <iostream>

namespace Tmpl8
{
	Surface tiles("assets/Tilesets/tileset_forest.png");

	LevelManager::LevelManager()
		:arrowSign(new Surface("assets/Objects/sign_arrow.png"), 1)
	{
		finish = new Finish;
		state[0] = LevelState::Open;
	}

	void LevelManager::LoadLevel(const int level, Player& player, Timer& timer)
	{
		if (level > numLevels || level <= 0) { std::cout << "Level cannot be found or does not exist." << std::endl; }
		else
		{
			currentLevel = level;
			Reset(player);

			switch (level)
			{
			case 1:
				player.SetLoc(startLoc1);
				timer.SetTime(time1);
				break;
			case 2:
				player.SetLoc(startLoc2);
				timer.SetTime(time2);
				break;
			default:
				break;
			}
		}
	}

	void LevelManager::DrawLevel(Surface* screen, const float& dt, const Location& drawOffset)
	{
		int loopY = 0, loopX = 0;

		// Set loop values for each level.
		switch (currentLevel)
		{
		case 1:
			loopY = 11;
			loopX = 50;
			break;
		case 2:
			loopY = 11;
			loopX = 20;
			break;
		default:
			break;
		}

		for (int y = 0; y < loopY; y++)
		{
			for (int x = 0; x < loopX; x++)
			{
				// Collision map drawing
				if (!(GetContents(x, y) == TileContents::Empty))
				{
					if (GetContents(x, y) == TileContents::ArrowSign)
					{
						arrowSign.Draw(screen, x * tileSize - static_cast<int>(drawOffset.x),
							y * tileSize - static_cast<int>(drawOffset.y));
					}
					if (GetContents(x, y) == TileContents::Water || GetContents(x, y) == TileContents::FakeWater)
						{ water.Draw(screen, x, y, dt, drawOffset); }
					if (GetContents(x, y) == TileContents::WoodStakes) { woodstakes.Draw(screen, x, y, drawOffset); }
					if (GetContents(x, y) == TileContents::SpikesBig) { spikes.Draw(screen, x, y, Spikes::Type::Big, drawOffset); }
					if (GetContents(x, y) == TileContents::SpikesMedium) { spikes.Draw(screen, x, y, Spikes::Type::Medium, drawOffset); }
					if (GetContents(x, y) == TileContents::SpikesSmall) { spikes.Draw(screen, x, y, Spikes::Type::Small, drawOffset); }
					if (GetContents(x, y) == TileContents::SpikesFloor) { spikes.Draw(screen, x, y, Spikes::Type::Floor, drawOffset); }
					if (GetContents(x, y) == TileContents::Finish) { finish->Draw(screen, x, y, dt, drawOffset); }
				}

				// Tilemap drawing
				switch (currentLevel)
				{
				case 1:
					if (!(levelOne[y][x * 2] == '-') && !(levelOne[y][x * 2 + 1] == '-'))
					{
						float tx = static_cast<float>(levelOne[y][x * 2] - 'a');
						float ty = static_cast<float>(levelOne[y][x * 2 + 1] - 'a');

						DrawTile(screen, { static_cast<float>(x * tileSize - drawOffset.x),
							static_cast<float>(y * tileSize - drawOffset.y) }, { tx, ty });
					}
					break;
				case 2:
					if (!(levelTwo[y][x * 2] == '-') && !(levelTwo[y][x * 2 + 1] == '-'))
					{
						float tx = static_cast<float>(levelTwo[y][x * 2] - 'a');
						float ty = static_cast<float>(levelTwo[y][x * 2 + 1] - 'a');

						DrawTile(screen, { static_cast<float>(x * tileSize - drawOffset.x),
							static_cast<float>(y * tileSize - drawOffset.y) }, { tx, ty });
					}
					break;
				default:
					break;
				}
			}
		}
	}

	void LevelManager::CallTrigger(const TileContents& content, const Location& tile, Player& player, MenuManager& menu)
	{
		switch (content)
		{
		case TileContents::Empty:
			break;
		case TileContents::FakeWater:
		case TileContents::SpikesFloor:
		case TileContents::Obstacle:
			obstacle.Trigger(tile, player);
			break;
		case TileContents::Finish:
			finish->Trigger(menu, *this, player, tile);
			break;
		case TileContents::Water:
			water.Trigger(*this, player, menu, tile);
			break;
		case TileContents::WoodStakes:
			woodstakes.Trigger(*this, player, menu, tile);
			break;
		case TileContents::SpikesBig:
			spikes.Trigger(*this, player, menu, Spikes::Type::Big, tile);
			break;
		case TileContents::SpikesMedium:
			spikes.Trigger(*this, player, menu, Spikes::Type::Medium, tile);
			break;
		case TileContents::SpikesSmall:
			spikes.Trigger(*this, player, menu, Spikes::Type::Small, tile);
			break;
		default:
			break;
		}
	}

	void LevelManager::Death(Player& player, MenuManager& menu)
	{
		isDead = true;
		menu.SetMenuState(MenuManager::MenuState::LevelFailed);
	}

	// Sends the state of the specified level
	LevelManager::LevelState LevelManager::GetLevelState(const int level) const { return state[level - 1]; }

	void LevelManager::SetLevelState(const int level, const LevelState state_in) { state[level - 1] = state_in; }

	// Returns contents from the cell.
	LevelManager::TileContents LevelManager::GetContents(const Location& loc) const
	{
		char content = 'o';

		switch (currentLevel)
		{
		case 1:
			if ((static_cast<int>(loc.x) > 50 * tileSize) || (static_cast<int>(loc.y) > 11 * tileSize)) { return TileContents::Empty; }
			content = levelOneColl[static_cast<int>(loc.y) / tileSize][static_cast<int>(loc.x) / tileSize];
			break;
		case 2:
			if ((static_cast<int>(loc.x) > 20 * tileSize) || (static_cast<int>(loc.y) > 11 * tileSize)) { return TileContents::Empty; }
			content = levelTwoColl[static_cast<int>(loc.y) / tileSize][static_cast<int>(loc.x) / tileSize];
			break;
		default:
			break;
		}
		
		//std::cout << "TileContent: " << content << std::endl;

		switch (content)
		{
		case 'o':
			return TileContents::Empty;
			break;
		case 'A':
			return TileContents::ArrowSign;
			break;
		case '-':
			return TileContents::Obstacle;
			break;
		case 'F':
			return TileContents::Finish;
			break;
		case 'W':
			return TileContents::Water;
			break;
		case 'w':
			return TileContents::FakeWater;
			break;
		case 'X':
			return TileContents::WoodStakes;
			break;
		case 'S':
			return TileContents::SpikesBig;
			break;
		case 's':
			return TileContents::SpikesMedium;
			break;
		case 'c':
			return TileContents::SpikesSmall;
			break;
		case 'C':
			return TileContents::SpikesFloor;
			break;
		default:
			std::cout << "Unknown content declaration, returned empty." << std::endl;
			return TileContents::Empty;
			break;
		}
	}

	LevelManager::TileContents LevelManager::GetContents(const int x, const int y) const
	{
		char content = 'o';

		switch (currentLevel)
		{
		case 1:
			if (x > 50 || x < 0 || y > 10 || y < 0) { return TileContents::Empty; }
			else { content = levelOneColl[y][x]; }
			break;
		case 2:
			if (x > 20 || x < 0 || y > 10 || y < 0) { return TileContents::Empty; }
			else { content = levelTwoColl[y][x]; }
			break;
		default:
			break;
		}

		// std::cout << "TileContent: " << content << std::endl;

		switch (content)
		{
		case 'o':
			return TileContents::Empty;
			break;
		case 'A':
			return TileContents::ArrowSign;
			break;
		case '-':
			return TileContents::Obstacle;
			break;
		case 'F':
			return TileContents::Finish;
			break;
		case 'W':
			return TileContents::Water;
			break;
		case 'w':
			return TileContents::FakeWater;
			break;
		case 'X':
			return TileContents::WoodStakes;
			break;
		case 'S':
			return TileContents::SpikesBig;
			break;
		case 's':
			return TileContents::SpikesMedium;
			break;
		case 'c':
			return TileContents::SpikesSmall;
			break;
		case 'C':
			return TileContents::SpikesFloor;
			break;
		default:
			std::cout << "Unknown content declaration, returned empty." << std::endl;
			return TileContents::Empty;
			break;
		}
	}

	int LevelManager::GetCurrentLevel() const { return currentLevel; }

	bool LevelManager::GetIsDead() const { return isDead; }

	void LevelManager::DrawTile(Surface* screen, const Location& loc, const Location& tile)
	{
		if (loc.x > screen->GetWidth()) { return; }
		if (loc.y > screen->GetHeight()) { return; }

		Pixel* src = tiles.GetBuffer() + static_cast<int>(tile.x) * tileSize + (static_cast<int>(tile.y) * tileSize) * tiles.GetWidth();
		Pixel* dst = screen->GetBuffer() + static_cast<int>(loc.x) + static_cast<int>(loc.y) * screen->GetWidth();

		for (int i = 0; i < tileSize; i++, src += tiles.GetWidth(), dst += screen->GetWidth()) // y
		{
			if (loc.y + i + 1 <= screen->GetHeight() && loc.y + i >= 0) // Stop drawing offscreen.
			{
				for (int j = 0; j < tileSize; j++) // x
				{
					if ((loc.x + j + 1) <= screen->GetWidth() && loc.x + j >= 0) // Stop drawing offscreen.
					{
						// Check for black parts & remove these from drawing.
						// Found in Sprite::Draw() code in Tmpl8.
						const Pixel c1 = *(src + j);
						if (c1 & 0xffffff) { dst[j] = src[j]; }
					}
				}
			}
		}
	}

	void LevelManager::Reset(Player& player)
	{
			player.Reset();

			isDead = false;
	}

};
