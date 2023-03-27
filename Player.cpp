#include "Player.h"
#include "surface.h"

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

	void Player::Move(const float dt_in, const float screenHeight) // TODO: make sure that the ball ALWAYS bounces the same height.
	{
		loc.y += speedY * dt_in;
		speedY += (gravity * 1000.0f) * dt_in; // CHANGE Y SPEED

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