#pragma once

#include "Location.h"
#include "surface.h"
#include "Player.h"

namespace Tmpl8
{
	class WoodStakes
	{
	public:
		WoodStakes();
		void Draw(Surface* screen, const int tilex, const int tiley);
		void Trigger(class LevelManager& level, Player& player, class MenuManager& menu);
	private:
		Sprite stakes;
	};
};