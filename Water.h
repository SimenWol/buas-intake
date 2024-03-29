#pragma once

#include "Location.h"
#include "surface.h"
#include "Player.h"

namespace Tmpl8
{
	class Water
	{
	public:
		// Constructor //
		Water();

		// Main Functions //
		void Draw(Surface* screen, const int tilex, const int tiley, const Location& drawOffset);
		void UpdateFrame(const float& deltaTime);
		void Trigger(class LevelManager& level, Player& player, class MenuManager& menu, const Location& tileLoc);
	private:
		// Animation //
		int frame = 0;
		float timer = 0.2f;
		float frameTime = 0.2f;

		// Sprites //
		Sprite water;
	};
};