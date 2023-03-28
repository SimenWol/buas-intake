#pragma once

#include "surface.h"
#include "Location.h"

namespace Tmpl8
{
	class Player
	{
	public:
		void Draw(Surface* screen_in);								// Draw player
		void SetLoc(const Location& loc_in);						// Set player starting position
		void Move(const float& dt_in, const Location& delta_loc);	// Move Player
	private:
		void Death();	// Runs everything necessary on death
		// CheckCollision, etc.
	private:
		Location loc = { 20.0f, 400.0f };	// Location of the player
		Location speed = { 0.0f, 0.0f };	// Speed of the player
		float gravity = 1.0f;				// Level of gravity
		float bounceHeight = 1.0f;			// Level of bounce height
	};

};