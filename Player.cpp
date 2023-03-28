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

		loc.x += speed.x * deltaTime;
		float moveX = 1000.0f * deltaTime;

		if (delta_loc.x == 0)
		{
			if ((speed.x > -10.0f && speed.x < 0) || (speed.x < 10.0f && speed.x > 0)) { speed.x = 0; }
			else if (speed.x > 0) { speed.x -= (moveX); }
			else if (speed.x < 0) { speed.x += (moveX); }
		}
		else if (delta_loc.x == -1) { speed.x -= moveX; }
		else if (delta_loc.x == 1) { speed.x += moveX; }

		if (speed.x <= -5000.0f) { speed.x = -5000.0f; }
		else if (speed.x >= 5000.0f) { speed.x = 5000.0f; }

		std::cout << "speed.x: " << speed.x << "moveX: " << moveX << std::endl;

		loc.y += speed.y * deltaTime;
		speed.y += (gravity * 1000.0f) * deltaTime; // CHANGE Y SPEED

		if (loc.y > (screenHeight - static_cast<float>(player.GetHeight())))
		{
			loc.y = (screenHeight - static_cast<float>(player.GetHeight()));
			speed.y = -(200.0f * bounceHeight);
		}
	}

	void Player::Death()
	{

	}

};