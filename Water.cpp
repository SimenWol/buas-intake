#include "Water.h"
#include "LevelManager.h"

#include <iostream>

namespace Tmpl8
{
	Water::Water()
		:water(new Surface("assets/Enemies/water.png"), 8)
	{}

	void Water::Draw(Surface* screen, const int tilex, const int tiley, const Location& drawOffset)
	{
		water.Draw(screen, tilex * LevelManager::tileSize - static_cast<int>(drawOffset.x), 
			tiley * LevelManager::tileSize - static_cast<int>(drawOffset.y));
	}

	void Water::Trigger(LevelManager& level, Player& player, MenuManager& menu, const Location& tileLoc)
	{
		Location topLeft = { 0.0f, 0.0f };
		Location bottomRight = { 0.0f, 0.0f };

		bottomRight.x = tileLoc.x + static_cast<float>(level.tileSize) / 2;
		bottomRight.y = tileLoc.y + static_cast<float>(level.tileSize) / 2;
		topLeft.x = tileLoc.x - static_cast<float>(level.tileSize) / 2;
		topLeft.y = tileLoc.y + 7 - static_cast<float>(level.tileSize) / 2;

		if (player.CheckCollision(topLeft, bottomRight))
		{
			level.Death(player, menu);
			std::cout << "Water triggered!" << std::endl;
		}
	}

	void Water::UpdateFrame(const float& deltaTime)
	{
		timer -= deltaTime;
		if (timer < 0) {
			timer += frameTime;
			if (++frame > 7) { frame = 0; }
			water.SetFrame(frame);
		}

		//std::cout << "Frame: " << frame << std::endl;
		//std::cout << "FrameTimer: " << timer << std::endl;
	}
};