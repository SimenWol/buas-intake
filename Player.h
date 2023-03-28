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
		Location loc = { 20.0f, 400.0f };			// Current location of the player
		Location speed = { 0.0f, 0.0f };			// Current speed of the player

		static constexpr float gravity = 1.0f;			// Level of gravity
		static constexpr float bounceHeight = 1.0f;		// Level of bounce height
		static constexpr float playerSpeed = 1.0f;		// Level of player speed
		static constexpr float maxPlayerSpeed = 500.0f;	// Maximum allowed player speed (X direction only)
	};

};