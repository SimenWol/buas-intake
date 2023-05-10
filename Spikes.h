#pragma once

#include "Location.h"
#include "surface.h"
#include "Player.h"

namespace Tmpl8
{
	class Spikes
	{
	public:
		// All Possible Spike Types //
		enum class Type
		{
			Big,
			Medium,
			Small,
			Floor, // DOes not do damage.
		};
	public:
		// Constructor //
		Spikes();

		// Main Functions //
		void Draw(Surface* screen, const int tilex, const int tiley, const Type type, const Location& drawOffset);
		void Trigger(class LevelManager& level, Player& player, class MenuManager& menu, const Type type, const Location& tileLoc);
	private:
		// Sprites //
		Sprite spikesSprite;
	};
};