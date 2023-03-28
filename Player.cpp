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

	void Player::SetLoc()
	{
		// Set starting Location
	}

	void Player::Move(const float& deltaTime, const Location& delta_loc)
	{
		float screenHeight = 512.0f; // Temp

		loc.x += speedX * deltaTime;
		float moveX = 1000.0f * deltaTime;
		if (delta_loc.x == 0)
		{
			if ((speedX > -10.0f && speedX < 0) || (speedX < 10.0f && speedX > 0)) { speedX = 0; }
			else if (speedX > 0) { speedX -= (moveX); }
			else if (speedX < 0) { speedX += (moveX); }
		}
		else if (delta_loc.x == -1) { speedX -= moveX; }
		else if (delta_loc.x == 1) { speedX += moveX; }

		if (speedX <= -5000.0f) { speedX = -5000.0f; }
		else if (speedX >= 5000.0f) { speedX = 5000.0f; }

		std::cout << "speedX: " << speedX << "moveX: " << moveX << std::endl;

		loc.y += speedY * deltaTime;
		speedY += (gravity * 1000.0f) * deltaTime; // CHANGE Y SPEED

		if (loc.y > (screenHeight - static_cast<float>(player.GetHeight())))
		{
			loc.y = (screenHeight - static_cast<float>(player.GetHeight()));
			speedY = -(200.0f * bounceHeight);
		}
	}

	void Player::Death()
	{

	}

};