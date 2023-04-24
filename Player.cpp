#include "Player.h"
#include "surface.h"
#include "template.h"

#include <iostream>

namespace Tmpl8
{
	Player::Player()
		:player(new Surface("assets/Temp/Ball.png"), 1)
	{
		radius = static_cast<float>(player.GetWidth()) / 2.0f;
	}

	void Player::Draw(Surface* screen_in)
	{
		player.Draw(screen_in, static_cast<int>(loc.x - radius), static_cast<int>(loc.y - radius));

		/* ======================== DEBUG ======================== */
		for (int i = 0; i < 64; i++)
		{
			float r1 = static_cast<float>(i) * PI / 32, r2 = static_cast<float>(i + 1) * PI / 32;
			screen_in->Line(loc.x - radius * sinf(r1), loc.y - radius * cosf(r1),
				loc.x - radius * sinf(r2), loc.y - radius * cosf(r2), 0xff0000);
		}
		/* ======================================================= */
	}

	void Player::SetLoc(const Location& loc_in)
	{
		loc.x = loc_in.x;
		loc.y = loc_in.y;
	}

	void Player::Move(const float& deltaTime, const Location& delta_loc, const LevelManager& levelmanager)
	{
		// Update player location //
		loc.x += speed.x * deltaTime;
		loc.y += speed.y * deltaTime;
		
		// Calculate new X speed //
		float moveX = 1000.0f * playerSpeed * deltaTime;
		if (delta_loc.x == 0) // Return speed to 0
		{
			if ((speed.x > -10.0f && speed.x < 0) || (speed.x < 10.0f && speed.x > 0)) { speed.x = 0; }
			else if (speed.x > 0.0f) { speed.x -= (moveX); }
			else if (speed.x < 0.0f) { speed.x += (moveX); }
		}
		else if (delta_loc.x == -1.0f) { speed.x -= moveX; }	// Increase speed to the left
		else if (delta_loc.x == 1.0f) { speed.x += moveX; }		// Increase speed to the right

		// Maximum speed
		if (speed.x <= -maxPlayerSpeed) { speed.x = -maxPlayerSpeed; }
		else if (speed.x >= maxPlayerSpeed) { speed.x = maxPlayerSpeed; }

		// Calculate new Y speed //
		speed.y += (gravity * 1000.0f) * deltaTime;

		//// Make sure the player bounces on the bottom of the screen
		//if (loc.y > (screenHeight - static_cast<float>(player.GetHeight())))
		//{
		//	loc.y = (screenHeight - static_cast<float>(player.GetHeight()));
		//	speed.y = -(200.0f * bounceHeight);
		//}

		CheckCollision(levelmanager);

		/* ======================== DEBUG ======================== */
		//std::cout << "Player Location: " << loc.x << ", " << loc.y << std::endl;	// Player Location
		//std::cout << "speed.x: " << speed.x << " moveX: " << moveX << std::endl;	// SpeedX & MoveX
		//std::cout << "speed.y: " << speed.y << std::endl;							// SpeedY
		/* ======================================================= */
	}

	void Player::Death()
	{

	}

	void Player::CheckCollision(const LevelManager& levelmanager)
	{
		float screenHeight = 512.0f; // Temp

		//int leftX = static_cast<int>(loc.x);
		//int rightX = leftX + radius * 2 + 1;
		//int upperY = static_cast<int>(loc.y);
		//int lowerY = upperY + radius * 2 + 1;
		//
		//std::cout << "Collision checks: " << leftX << " " << rightX << " " << upperY << " " << lowerY << " " << std::endl;

		// Make sure the player bounces on the bottom of the screen
		if (loc.y > (screenHeight - radius))
		{
			loc.y = (screenHeight - radius);
			speed.y = -(200.0f * bounceHeight);
		}

		// levelmanager.GetContents(loc);
	}

};

//for (int i = 0; i < 64; i++)
//{
//	float r1 = (float)i * PI / 32, r2 = (float)(i + 1) * PI / 32;
//	screen_in->Line((loc.x + radius) - radius * sinf(r1), (loc.y + radius) - radius * cosf(r1),
//		(loc.x + radius) - radius * sinf(r2), (loc.y + radius) - radius * cosf(r2), 0xff0000);
//}