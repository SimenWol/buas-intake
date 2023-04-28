#include "Timer.h"
#include "LevelManager.h"

#include <iostream>

namespace Tmpl8
{
	void Timer::Draw()
	{
		std::cout << "Drawing Timer!" << std::endl;
	}

	void Timer::Tick(const float& deltaTime, LevelManager& level, Player& player, MenuManager& menu)
	{
		time -= deltaTime;
		if (time <= 0.0f)
		{
			time = 0.0f;
			TimeUp(level, player, menu);
		}

		std::cout << "Timer: " << time << std::endl;
	}

	void Timer::TimeUp(LevelManager& level, Player& player, MenuManager& menu)
	{
		level.Death(player, menu);
	}
};