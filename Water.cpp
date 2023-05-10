#include "Water.h"
#include "LevelManager.h"

#include <iostream>

namespace Tmpl8
{
	// Constructor //
	Water::Water()
		:water(new Surface("assets/Enemies/water.png"), 8)
	{}

	// Draw function
	void Water::Draw(Surface* screen, const int tilex, const int tiley, const Location& drawOffset)
	{
		water.Draw(screen, tilex * LevelManager::tileSize - static_cast<int>(drawOffset.x), 
			tiley * LevelManager::tileSize - static_cast<int>(drawOffset.y));
	}

	// Function that checks more precise collision & then calls level death if there is collision.
	void Water::Trigger(LevelManager& level, Player& player, MenuManager& menu, const Location& tileLoc)
	{
		// Get/Set location of water hitbox.
		Location topLeft = { 0.0f, 0.0f };
		Location bottomRight = { 0.0f, 0.0f };

		bottomRight.x = tileLoc.x + static_cast<float>(level.tileSize) / 2;
		bottomRight.y = tileLoc.y + static_cast<float>(level.tileSize) / 2;
		topLeft.x = tileLoc.x - static_cast<float>(level.tileSize) / 2;
		topLeft.y = tileLoc.y + 7 - static_cast<float>(level.tileSize) / 2;

		// Check collision & call functions.
		if (player.CheckCollision(topLeft, bottomRight))
		{
			level.Death(player, menu);
			std::cout << "Water triggered!" << std::endl;
		}
	}

	// Function that updates the animation frame.
	void Water::UpdateFrame(const float& deltaTime)
	{
		timer -= deltaTime;
		if (timer < 0) {
			timer += frameTime;
			if (++frame > 7) { frame = 0; }
			water.SetFrame(frame);
		}

		/* ======================== DEBUG ======================== */
		//std::cout << "Frame: " << frame << std::endl;
		//std::cout << "FrameTimer: " << timer << std::endl;
		/* ======================================================= */
	}
};