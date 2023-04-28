#pragma once

#include "Player.h"
#include "surface.h"

namespace Tmpl8
{
	class Timer
	{
	public:
		Timer();
		void Draw(Surface* screen, const int center_x, const int center_y);
		void Tick(const float& deltaTime, class LevelManager& level, Player& player, class MenuManager& menu);
	public:
		void SetTime(const float& time_in) { time = time_in; };
	private:
		void TimeUp(class LevelManager& level, Player& player, class MenuManager& menu);
	private:
		float time = 10.0f;
		int firstDigit = 0, lastDigit = 0;
		int x = 0;

		Sprite numbers;
	};
};