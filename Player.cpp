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

		CheckCollision(levelmanager);
		DeflectY();

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
		// Calculate center of which tiles to check
		float half = 0.5 * levelmanager.tileSize;

		float leftX = (static_cast<int>(loc.x - radius) / levelmanager.tileSize) * half * 2 + 32;
		float rightX = ((static_cast<int>(loc.x + radius) + 1) / levelmanager.tileSize) * half * 2 + 32;
		float upperY = (static_cast<int>(loc.y - radius) / levelmanager.tileSize) * half * 2 + 32;
		float lowerY = ((static_cast<int>(loc.y + radius) + 1) / levelmanager.tileSize) * half * 2 + 32;

		// TopLeft
		if (CircleToAABBCollision({ leftX, upperY }, half))
		{
			CallType(levelmanager.GetContents({ (loc.x - radius), (loc.y - radius) }), 
				{ (loc.x - radius), (loc.y - radius) });
		}

		// BottomLeft
		if (CircleToAABBCollision({ leftX, lowerY }, half))
		{
			CallType(levelmanager.GetContents({ (loc.x - radius), (loc.y + radius) }), 
				{ (loc.x - radius), (loc.y + radius) });
		}

		// TopRight
		if (CircleToAABBCollision({ rightX, upperY }, half))
		{
			CallType(levelmanager.GetContents({ (loc.x + radius), (loc.y - radius) }), 
				{ (loc.x + radius), (loc.y - radius) });
		}

		// BottomRight
		if (CircleToAABBCollision({ rightX, lowerY }, half))
		{
			CallType(levelmanager.GetContents({ (loc.x + radius), (loc.y + radius) }), 
				{ (loc.x + radius), (loc.y + radius) });
		}

		//std::cout << "Collision checks: " << leftX << " " << rightX << " " << upperY << " " << lowerY << " " << std::endl;
	}

	void Player::CallType(const LevelManager::TileContents& content, const Location& tile)
	{
		switch (content)
		{
		case LevelManager::TileContents::Empty:
			break;
		case LevelManager::TileContents::Obstacle:
			Obstacle(tile);
			break;
		default:
			break;
		}
	}

	void Player::Obstacle(const Location& tile)
	{
		std::cout << "Obstacle called" << std::endl;
	}

	void Player::DeflectX()
	{
	}

	void Player::DeflectY()
	{
		float screenHeight = 512.0f; // Temp
		// Make sure the player bounces on the bottom of the screen
		if (loc.y > (screenHeight - radius))
		{
			loc.y = (screenHeight - radius);
			speed.y = -(200.0f * bounceHeight);
		}
	}

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