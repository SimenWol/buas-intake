#include "Camera.h"
#include "LevelManager.h"

#include <iostream>

namespace Tmpl8
{
	void Camera::Tick(Surface* screen, const Location& playerLoc)
	{
		if (playerLoc.x > (screen->GetWidth() / 2.0f))
		{
			offset.x = playerLoc.x - screen->GetWidth() / 2.0f;
			if (offset.x > 40 * LevelManager::tileSize - screen->GetWidth())
			{
				offset.x = static_cast<float>(40 * LevelManager::tileSize - screen->GetWidth());
			}
		}
		else
		{
			offset.x = 0.0f;
		}

		if (playerLoc.y > (screen->GetHeight() / 2.0f))
		{
			offset.y = playerLoc.y - screen->GetHeight() / 2.0f;
			if (offset.y > 11 * LevelManager::tileSize - screen->GetHeight())
			{
				offset.y = static_cast<float>(11 * LevelManager::tileSize - screen->GetHeight());
			}
		}
		else
		{
			offset.y = 0.0f;
		}

		//if (playerLoc.y > (screen->GetHeight() / 2.0f))
		//{
		//	offset.y = playerLoc.x - screen->GetHeight() / 2.0f;
		//}
		//else
		//{
		//	offset.y = 0.0f;
		//}

		//std::cout << "Offset: " << offset.x << ", " << offset.y << std::endl;
	}

	Location Camera::GetOffset() { return offset; }
};
