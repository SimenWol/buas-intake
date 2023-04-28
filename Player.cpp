#include "Player.h"
#include "surface.h"
#include "template.h"
#include "LevelManager.h"
#include "MenuManager.h"

#include <iostream>

namespace Tmpl8
{
	Player::Player()
		:player(new Surface("assets/Player/Basketball.png"), 1)
		,deathFX(new Surface("assets/FX/hit.png"), 5)
		,bounceFX(new Surface("assets/FX/dust.png"), 8)
	{
		radius = static_cast<float>(player.GetWidth()) / 2.0f;
	}

	void Player::Draw(Surface* screen_in, const Location& drawOffset)
	{
		player.Draw(screen_in, static_cast<int>(loc.x - drawOffset.x - radius), 
			static_cast<int>(loc.y - drawOffset.y - radius));

		/* ======================== DEBUG ======================== */
		for (int i = 0; i < 64; i++)
		{
			float r1 = static_cast<float>(i) * PI / 32, r2 = static_cast<float>(i + 1) * PI / 32;
			screen_in->Line(loc.x - drawOffset.x - radius * sinf(r1), loc.y - drawOffset.y - radius * cosf(r1),
				loc.x - drawOffset.x - radius * sinf(r2), loc.y - drawOffset.y - radius * cosf(r2), 0xff0000);
		}
		/* ======================================================= */
	}

	void Player::SetLoc(const Location& loc_in)
	{
		loc.x = loc_in.x;
		loc.y = loc_in.y;
	}

	void Player::Move(const float& deltaTime, const Location& delta_loc, LevelManager& levelmanager, MenuManager& menu)
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

		CheckCollision(levelmanager, menu);

		/* ======================== DEBUG ======================== */
		//std::cout << "Player Location: " << loc.x << ", " << loc.y << std::endl;	// Player Location
		//std::cout << "speed.x: " << speed.x << " moveX: " << moveX << std::endl;	// SpeedX & MoveX
		//std::cout << "speed.y: " << speed.y << std::endl;							// SpeedY
		/* ======================================================= */
	}

	void Player::Reset()
	{
		speed = { 0.0f, 0.0f };
	}

	void Player::BounceFX(Surface* screen, const float& deltaTime, const Location& drawOffset)
	{
		bounceTimer -= deltaTime;
		if (bounceTimer < 0)
		{
			bounceTimer += frameTime;
			bounceFX.SetFrame(bounceFrame);
			if (++bounceFrame == 8) { bounceFrame = 0; playBounceFX = false; }
		}
		bounceFX.Draw(screen, static_cast<int>(bounceLoc.x - drawOffset.x), 
			static_cast<int>(bounceLoc.y - drawOffset.y));
	}

	void Player::DeathFX(Surface* screen, const float& deltaTime, const Location& drawOffset)
	{
			deathTimer -= deltaTime;
			if (deathTimer < 0)
			{
				deathTimer += frameTime;
				if (++deathFrame > 4) { deathFrame = 0; deathTimer += 1; }
				deathFX.SetFrame(deathFrame);
			}
		deathFX.Draw(screen, static_cast<int>(loc.x - drawOffset.x - radius - 13.5f),
			static_cast<int>(loc.y - drawOffset.y - radius - 13.5f));
	}

	void Player::CheckCollision(LevelManager& levelmanager, MenuManager& menu)
	{
		// Calculate center of which tiles to check
		float half = 0.5 * levelmanager.tileSize;

		float leftX = (static_cast<int>(loc.x - radius) / levelmanager.tileSize) * half * 2 + half;
		float rightX = ((static_cast<int>(loc.x + radius) + 1) / levelmanager.tileSize) * half * 2 + half;
		float upperY = (static_cast<int>(loc.y - radius) / levelmanager.tileSize) * half * 2 + half;
		float lowerY = ((static_cast<int>(loc.y + radius) + 1) / levelmanager.tileSize) * half * 2 + half;

		// TopLeft
		if (CircleToAABBCollision({ leftX, upperY }, half))
		{
			levelmanager.CallTrigger(levelmanager.GetContents({ (loc.x - radius), (loc.y - radius) }), 
				{ leftX, upperY }, *this, menu);
		}

		// BottomLeft
		if (CircleToAABBCollision({ leftX, lowerY }, half))
		{
			levelmanager.CallTrigger(levelmanager.GetContents({ (loc.x - radius), (loc.y + radius) }),
				{ leftX, lowerY }, *this, menu);
		}

		// TopRight
		if (CircleToAABBCollision({ rightX, upperY }, half))
		{
			levelmanager.CallTrigger(levelmanager.GetContents({ (loc.x + radius), (loc.y - radius) }),
				{ rightX, upperY }, *this, menu);
		}

		// BottomRight
		if (CircleToAABBCollision({ rightX, lowerY }, half))
		{
			levelmanager.CallTrigger(levelmanager.GetContents({ (loc.x + radius), (loc.y + radius) }),
				{ rightX, lowerY }, *this, menu);
		}

		/* ======================== DEBUG ======================== */
		//std::cout << "Collision checks: " << leftX << " " << rightX << " " << upperY << " " << lowerY << " " << std::endl;
		/* ======================================================= */
	}

	void Player::DeflectX(const float offset)
	{
		loc.x = (loc.x + offset);
		speed.x = -(speed.x * bounceHeight);

		/* ======================== DEBUG ======================== */
		// std::cout << "DeflectX called." << std::endl;
		/* ======================================================= */
	}

	void Player::DeflectY(const float offset)
	{
		loc.y = (loc.y + offset);
		speed.y = -(200.0f * bounceHeight);

		playBounceFX = true;
		bounceLoc = { loc.x - bounceFX.GetWidth() / 2, loc.y - bounceFX.GetHeight() / 2 };

		/* ======================== DEBUG ======================== */
		// std::cout << "DeflectY called." << std::endl;
		/* ======================================================= */
	}

	Location Player::GetLoc() { return loc; }

	float Player::GetRadius() { return radius; }

	bool Player::GetBounceFX() { return playBounceFX; }

	// Collision check from: https://www.gamedevelopment.blog/collision-detection-circles-rectangles-and-polygons/
	bool Player::CircleToAABBCollision(const Location& tile, const float half)
	{
		// Get distance vector between both centers
		Location distance = { (loc.x - tile.x), (loc.y - tile.y) };

		if (distance.x > (half + radius)) { return false; }
		if (distance.y > (half + radius)) { return false; }

		if (distance.x <= half) { return true; }
		if (distance.y <= half) { return true; }

		float cDist_sq = (distance.x - half) * (distance.x - half) + (distance.y - half) * (distance.y - half);

		return (cDist_sq <= (radius * radius));
	}
};