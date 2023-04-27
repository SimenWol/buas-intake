#include "Finish.h"
#include "LevelManager.h"

#include <iostream>

namespace Tmpl8
{
	Finish::Finish()
		:finishSprite(new Surface("assets/Objects/flag.png"), 9)
	{}

	void Finish::Draw(Surface* screen, const int tilex, const int tiley, const float& dt)
	{
		UpdateFrame(dt);
		finishSprite.Draw(screen, tilex * LevelManager::tileSize, tiley * LevelManager::tileSize);
	}

	void Tmpl8::Finish::Trigger(MenuManager& menu, LevelManager& level)
	{
		level.SetLevelState(level.GetCurrentLevel(), LevelManager::LevelState::Completed);
		menu.SetMenuState(MenuManager::MenuState::LevelComplete);
		// End Timer
		
		//std::cout << "Finish triggered!" << std::endl;
	}

	void Finish::UpdateFrame(const float& dt)
	{
		timer -= dt;
		if (timer < 0) {
			timer += frameTime;
			if (++frame > 8) { frame = 0; }
			finishSprite.SetFrame(frame);
		}

		//std::cout << "Frame: " << frame << std::endl;
		//std::cout << "FrameTimer: " << timer << std::endl;
	}
};
