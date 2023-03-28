#include "Player.h"
#include "surface.h"

#include <iostream>

namespace Tmpl8
{
	// Sprites used (only) in this file
	Sprite player(new Surface("assets/Template/ball.png"), 1);

	void Player::Draw(Surface* screen_in)
	{
		player.Draw(screen_in, static_cast<int>(loc.x), static_cast<int>(loc.y));
	}

	void Player::SetLoc(const Location& loc_in)
	{
		loc.x = loc_in.x;
		loc.y = loc_in.y;
	}

	void Player::Move(const float& deltaTime, const Location& delta_loc)
	{
		float screenHeight = 512.0f; // Temp

		// Update player location //
		loc.x += speed.x * deltaTime;
		loc.y += speed.y * deltaTime;
		
		// Calculate new X speed //
		float moveX = 1000.0f * playerSpeed * deltaTime;
		if (delta_loc.x == 0) // Return speed to 0
		{
			if ((speed.x > -10.0f && speed.x < 0) || (speed.x < 10.0f && speed.x > 0)) { speed.x = 0; }
			else if (speed.x > 0) { speed.x -= (moveX); }
			else if (speed.x < 0) { speed.x += (moveX); }
		}
		else if (delta_loc.x == -1) { speed.x -= moveX; }	// Increase speed to the left
		else if (delta_loc.x == 1) { speed.x += moveX; }	// Increase speed to the right

		// Maximum speed
		if (speed.x <= -maxPlayerSpeed) { speed.x = -maxPlayerSpeed; }
		else if (speed.x >= maxPlayerSpeed) { speed.x = maxPlayerSpeed; }

		// Calculate new Y speed //
		speed.y += (gravity * 1000.0f) * deltaTime;

		// Make sure the player bounces on the bottom of the screen
		if (loc.y > (screenHeight - static_cast<float>(player.GetHeight())))
		{
			loc.y = (screenHeight - static_cast<float>(player.GetHeight()));
			speed.y = -(200.0f * bounceHeight);
		}

		/* ======================== DEBUG ======================== */
		//std::cout << "Player Location: " << loc.x << ", " << loc.y << std::endl;	// Player Location
		//std::cout << "speed.x: " << speed.x << " moveX: " << moveX << std::endl;	// SpeedX & MoveX
		//std::cout << "speed.y: " << speed.y << std::endl;							// SpeedY
		/* ======================================================= */
	}

	void Player::Death()
	{

	}

};