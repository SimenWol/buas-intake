#pragma once

#include "Location.h"
#include "surface.h"
#include "Player.h"

namespace Tmpl8
{
	class Spikes
	{
	public:
		enum class Type
		{
			Big,
			Medium,
			Small,
			Floor,
		};
	public:
		Spikes();
		void Draw(Surface* screen, const int tilex, const int tiley, const Type type, const Location& drawOffset);
		void Trigger(class LevelManager& level, Player& player, class MenuManager& menu, const Type type, const Location& tileLoc);
	private:
		Sprite spikesSprite;
	};
};