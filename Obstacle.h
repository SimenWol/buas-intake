#pragma once

#include "Location.h"
#include "Player.h"

namespace Tmpl8
{
	class Obstacle
	{
	public:
		void Trigger(const Location& tile, Player& player);
	};
}