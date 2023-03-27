#pragma once

#include "surface.h"

namespace Tmpl8
{
	class Player
	{
	public:
		void Draw(Surface* screen_in);
		void SetLoc();	// Set starting position (only used when a level is (re)loaded)
		void Move();	// Move Player (only active when level is active)
	private:
		void Death();	// Runs everything necessary on death
		// CheckCollision, etc.
	private:
		int x = 20, y = 20;
	};

};