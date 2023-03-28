#pragma once

#include "surface.h"
#include "Location.h"

namespace Tmpl8
{
	class Player
	{
	public:
		void Draw(Surface* screen_in);
		void SetLoc();												// Set player starting position
		void Move(const float& dt_in, const Location& delta_loc);	// Move Player
	private:
		void Death();	// Runs everything necessary on death
		// CheckCollision, etc.
	private:
		Location loc = { 20.0f, 400.0f };	// Location of the player/ball
		float gravity = 1.0f;				// Current level Gravity
		float bounceHeight = 1.0f;			// Current level of bounce height
		float speedY = 0.0f;				// Current speed of the ball in the Y direction
		float speedX = 0.0f;				// Current speed of the ball in the X direction

		//bool movingRight = false; // Something like this?
		//bool movingLeft = false;
	};

};