#include "Timer.h"
#include "LevelManager.h"

#include <iostream>

namespace Tmpl8
{
	// Constructor //
	Timer::Timer()
		:numbers(new Surface("assets/UI/numbers.png"), 10)
	{}

	// Function that calculates each individual digit and then draws it to the screen.
	void Timer::Draw(Surface* screen, const int center_x, const int y)
	{
		if (time == 0)
		{
			firstDigit = 0;
			lastDigit = 0;
		}
		else if (time < 100)
		{
			lastDigit = static_cast<int>(time) % 10 + 1;
			if (lastDigit == 10) { lastDigit = 0; }
			firstDigit = (static_cast<int>(time) + 1 - lastDigit) / 10;
		}

		if (firstDigit == 0)
		{
			x = center_x - numbers.GetWidth() / 2;
			numbers.SetFrame(lastDigit);
			numbers.Draw(screen, x, y);
		}
		else
		{
			x = center_x - numbers.GetWidth();
			numbers.SetFrame(firstDigit);
			numbers.Draw(screen, x - 1, y);
			numbers.SetFrame(lastDigit);
			numbers.Draw(screen, center_x + 1, y);
		}

		/* ======================== DEBUG ======================== */
		// std::cout << "Time left: " << firstDigit << lastDigit << std::endl;
		/* ======================================================= */
	}

	// Function that updates the time.
	void Timer::Tick(const float& deltaTime, LevelManager& level, Player& player, MenuManager& menu)
	{
		time -= deltaTime;
		if (time <= 0.0f)
		{
			time = 0.0f;
			TimeUp(level, player, menu);
		}

		/* ======================== DEBUG ======================== */
		// std::cout << "Timer: " << time << std::endl;
		/* ======================================================= */
	}

	// Function that triggers upon the timer reaching zero.
	void Timer::TimeUp(LevelManager& level, Player& player, MenuManager& menu)
	{
		level.Death(player, menu);

		/* ======================== DEBUG ======================== */
		std::cout << "Time's up!" << std::endl;
		/* ======================================================= */
	}
};