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
				timer.SetTime(10.0f);
			default:
				break;
			}
		}
	}

	void LevelManager::DrawLevel(Surface* screen, const int level, const float& dt, const Location& drawOffset)
	{
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 40; x++)
			{
				if (!(map[y][x * 2] == '-') || !(map[y][x * 2 + 1] == '-'))
				{
					float tx = static_cast<float>(map[y][x * 2] - 'a');
					float ty = static_cast<float>(map[y][x * 2 + 1] - 'a');

					DrawTile(screen, { static_cast<float>(x * tileSize - drawOffset.x), 
						static_cast<float>(y * tileSize - drawOffset.y) }, { tx, ty });
				}
			}

			for (int x = 0; x < 40; x++)
			{
				if (!(GetContents(x, y) == TileContents::Empty))
				{
					if (GetContents(x, y) == TileContents::ArrowSign) 
					{ 
						arrowSign.Draw(screen, x * tileSize - static_cast<int>(drawOffset.x), 
							y * tileSize - static_cast<int>(drawOffset.y)); 
					}
					if (GetContents(x, y) == TileContents::Water) { water.Draw(screen, x, y, dt, drawOffset); }
					if (GetContents(x, y) == TileContents::WoodStakes) { woodstakes.Draw(screen, x, y, drawOffset); }
					if (GetContents(x, y) == TileContents::SpikesBig) { spikes.Draw(screen, x, y, Spikes::Type::Big, drawOffset); }
					if (GetContents(x, y) == TileContents::SpikesMedium) { spikes.Draw(screen, x, y, Spikes::Type::Medium, drawOffset); }
					if (GetContents(x, y) == TileContents::SpikesSmall) { spikes.Draw(screen, x, y, Spikes::Type::Small, drawOffset); }
					if (GetContents(x, y) == TileContents::Finish) { finish->Draw(screen, x, y, dt, drawOffset); }
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
		case TileContents::Obstacle:
			obstacle.Trigger(tile, player);
			break;
		case TileContents::Finish:
			finish->Trigger(menu, *this);
			break;
		case TileContents::Water:
			water.Trigger(*this, player, menu);
			break;
		case TileContents::WoodStakes:
			woodstakes.Trigger(*this, player, menu);
			break;
		case TileContents::SpikesBig:
			spikes.Trigger(*this, player, menu, Spikes::Type::Big);
			break;
		case TileContents::SpikesMedium:
			spikes.Trigger(*this, player, menu, Spikes::Type::Medium);
			break;
		case TileContents::SpikesSmall:
			spikes.Trigger(*this, player, menu, Spikes::Type::Small);
			break;
		default:
			break;
		}
	}

	void LevelManager::Death(Player& player, MenuManager& menu)
	{
		isDead = true;
		menu.SetMenuState(MenuManager::MenuState::LevelFailed);
		// Stop Timer
	}

	// Sends the state of the specified level
	LevelManager::LevelState LevelManager::GetLevelState(const int level) const { return state[level - 1]; }

	void LevelManager::SetLevelState(const int level, const LevelState state_in) { state[level - 1] = state_in; }

	// Returns contents from the cell.
	LevelManager::TileContents LevelManager::GetContents(const Location& loc) const
	{
		if ((int(loc.x) > 40 * tileSize) || (int(loc.y) > 8 * tileSize)) { return TileContents::Empty; }

		char content = collisionMap[int(loc.y) / tileSize][int(loc.x) / tileSize];
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
		default:
			std::cout << "Unknown content declaration, returned empty." << std::endl;
			return TileContents::Empty;
			break;
		}
	}

	LevelManager::TileContents LevelManager::GetContents(const int x, const int y) const
	{
		if ((x > 40) || (y > 8)) { return TileContents::Empty; }

		char content = collisionMap[y][x];
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
						dst[j] = src[j];
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
