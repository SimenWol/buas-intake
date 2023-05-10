#pragma once

#include "Location.h"
#include "Player.h"

namespace Tmpl8
{
	class Obstacle
	{
	public:
		// Main Functions //
		void Trigger(const Location& tile, Player& player);
	};
};