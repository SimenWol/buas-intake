#pragma once

#include "Player.h"

namespace Tmpl8
{
	class Timer
	{
	public:
		void Draw();
		void Tick(const float& deltaTime, class LevelManager& level, Player& player, class MenuManager& menu);
	public:
		void SetTime(const float& time_in) { time = time_in; };
	private:
		void TimeUp(class LevelManager& level, Player& player, class MenuManager& menu);
	private:
		float time = 10.0f;
	};
};