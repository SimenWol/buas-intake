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

	void Finish::Trigger(MenuManager& menu, LevelManager& level)
	{
		level.SetLevelState(level.GetCurrentLevel(), LevelManager::LevelState::Completed);
		menu.SetMenuState(MenuManager::MenuState::LevelComplete);
		// End Timer
		
		//std::cout << "Finish triggered!" << std::endl;
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
