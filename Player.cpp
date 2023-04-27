#include "Player.h"
#include "surface.h"
#include "template.h"

#include <iostream>

namespace Tmpl8
{
	Player::Player()
		:player(new Surface("assets/Player/Basketball.png"), 1)
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

	void Player::Death()
	{

	}

	void Player::CheckCollision(const LevelManager& levelmanager)
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
			CallType(levelmanager.GetContents({ (loc.x - radius), (loc.y - radius) }), 
				{ leftX, upperY }, levelmanager);
		}

		// BottomLeft
		if (CircleToAABBCollision({ leftX, lowerY }, half))
		{
			CallType(levelmanager.GetContents({ (loc.x - radius), (loc.y + radius) }), 
				{ leftX, lowerY }, levelmanager);
		}

		// TopRight
		if (CircleToAABBCollision({ rightX, upperY }, half))
		{
			CallType(levelmanager.GetContents({ (loc.x + radius), (loc.y - radius) }), 
				{ rightX, upperY }, levelmanager);
		}

		// BottomRight
		if (CircleToAABBCollision({ rightX, lowerY }, half))
		{
			CallType(levelmanager.GetContents({ (loc.x + radius), (loc.y + radius) }), 
				{ rightX, lowerY }, levelmanager);
		}

		/* ======================== DEBUG ======================== */
		//std::cout << "Collision checks: " << leftX << " " << rightX << " " << upperY << " " << lowerY << " " << std::endl;
		/* ======================================================= */
	}

	void Player::CallType(const LevelManager::TileContents& content, const Location& tile, const LevelManager& levelmanager)
	{
		switch (content)
		{
		case LevelManager::TileContents::Empty:
			break;
		case LevelManager::TileContents::Obstacle:
			Obstacle(tile, levelmanager);
			break;
		default:
			break;
		}
	}

	void Player::Obstacle(const Location& tile, const LevelManager& levelmanager)
	{
		float offX = tile.x - loc.x;
		float offY = tile.y - loc.y;

		float offsetX = offX;
		float offsetY = offY;
		if (offsetX < 0) { offsetX += levelmanager.tileSize / 2 + radius; }
		else { offsetX -= levelmanager.tileSize / 2 + radius; }
		if (offsetY < 0) { offsetY += levelmanager.tileSize / 2 + radius; }
		else { offsetY -= levelmanager.tileSize / 2 + radius; }

		if (offX < 0) { offX = -offX; }
		if (offY < 0) { offY = -offY; }

		/* ======================== DEBUG ======================== */
		// std::cout << offX << " " << offY << std::endl;
		// std::cout << "Obstacle called" << std::endl;
		/* ======================================================= */

		if (offY > offX) { DeflectY(offsetY); }
		else if (offX > offY) { DeflectX(offsetX); }
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

		/* ======================== DEBUG ======================== */
		// std::cout << "DeflectY called." << std::endl;
		/* ======================================================= */
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