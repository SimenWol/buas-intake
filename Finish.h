#pragma once

#include "Location.h"
#include "surface.h"
#include "MenuManager.h"

namespace Tmpl8
{
	class Finish
	{
	public:
		// Constructor //
		Finish();

		// Main Functions //
		void Draw(Surface* screen, const int tilex, const int tiley, const Location& drawOffset);
		void UpdateFrame(const float& deltaTime);
		void Trigger(MenuManager& menu, class LevelManager& level, Player& player, const Location& tileLoc);
	private:
		// Animation //
		int frame = 0;
		float timer = 0.1f;
		float frameTime = 0.1f;

		// Sprites //
		Sprite flag;
	};
};