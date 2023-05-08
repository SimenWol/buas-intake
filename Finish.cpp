#include "Finish.h"
#include "LevelManager.h"

#include <iostream>

namespace Tmpl8
{
	Finish::Finish()
		:flag(new Surface("assets/Objects/flag.png"), 9)
	{}

	void Finish::Draw(Surface* screen, const int tilex, const int tiley, const float& dt, const Location& drawOffset)
	{
		UpdateFrame(dt);
		flag.Draw(screen, tilex * LevelManager::tileSize - static_cast<int>(drawOffset.x),
			tiley * LevelManager::tileSize - static_cast<int>(drawOffset.y));
	}

	void Finish::Trigger(MenuManager& menu, LevelManager& level, Player& player, const Location& tileLoc)
	{
		Location topLeft = { 0.0f, 0.0f };
		Location bottomRight = { 0.0f, 0.0f };

		bottomRight.x = tileLoc.x - 27 + static_cast<float>(level.tileSize) / 2;
		bottomRight.y = tileLoc.y + static_cast<float>(level.tileSize) / 2;
		topLeft.x = tileLoc.x + 9 - static_cast<float>(level.tileSize) / 2;
		topLeft.y = tileLoc.y + 15 - static_cast<float>(level.tileSize) / 2;

		if (player.CheckCollision(topLeft, bottomRight))
		{
			level.SetLevelState(level.GetCurrentLevel(), LevelManager::LevelState::Completed);
			level.SetLevelState(level.GetCurrentLevel() + 1, LevelManager::LevelState::Open);
			menu.SetMenuState(MenuManager::MenuState::LevelComplete);
			std::cout << "Finish triggered!" << std::endl;
		}
	}

	void Finish::UpdateFrame(const float& deltaTime)
	{
		timer -= deltaTime;
		if (timer < 0) {
			timer += frameTime;
			if (++frame > 8) { frame = 0; }
			flag.SetFrame(frame);
		}

		//std::cout << "Frame: " << frame << std::endl;
		//std::cout << "FrameTimer: " << timer << std::endl;
	}
};
