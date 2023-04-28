#include "Timer.h"

#include <iostream>

namespace Tmpl8
{
	void Timer::Tick(const float& deltaTime)
	{
		time -= deltaTime;
		if (time <= 0.0f)
		{
			time = 0.0f;
			TimeUp();
		}

		std::cout << "Timer: " << time << std::endl;
	}

	void Timer::TimeUp()
	{
	}
};