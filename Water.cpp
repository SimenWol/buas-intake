#include "Water.h"
#include "LevelManager.h"

#include <iostream>

namespace Tmpl8
{
	Water::Water()
		:water(new Surface("assets/Enemies/water.png"), 8)
	{}

	void Water::Draw(Surface* screen, const int tilex, const int tiley, const float& deltaTime, const Location& drawOffset)
	{
		UpdateFrame(deltaTime);
		water.Draw(screen, tilex * LevelManager::tileSize - static_cast<int>(drawOffset.x), 
			tiley * LevelManager::tileSize - static_cast<int>(drawOffset.y));
	}

	void Water::Trigger(LevelManager& level, Player& player, MenuManager& menu)
	{
		level.Death(player, menu);

		std::cout << "Water triggered!" << std::endl;
	}

	void Water::UpdateFrame(const float& deltaTime)
	{
		timer -= deltaTime;
		if (timer < 0) {
			timer += frameTime;
			if (++frame > 7) { frame = 0; }
			water.SetFrame(frame);
		}

		//std::cout << "Frame: " << frame << std::endl;
		//std::cout << "FrameTimer: " << timer << std::endl;
	}
};