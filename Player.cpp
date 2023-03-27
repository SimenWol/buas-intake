#include "Player.h"
#include "surface.h"

namespace Tmpl8
{
	// Sprites used (only) in this file
	Sprite player(new Surface("assets/Template/ball.png"), 1);

	void Player::Draw(Surface* screen_in)
	{
		player.Draw(screen_in, x, y);
	}

	void Player::SetLoc()
	{
		// Set starting Location
	}

	void Player::Move()
	{
		// Move function
	}

	void Player::Death()
	{

	}

};