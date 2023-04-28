#include "Camera.h"

#include <iostream>

namespace Tmpl8
{
	void Camera::Tick(Surface* screen, const Location& playerLoc)
	{
		if (playerLoc.x > (screen->GetWidth() / 2.0f))
		{
			offset.x = playerLoc.x - screen->GetWidth() / 2.0f;
		}
		else
		{
			offset.x = 0.0f;
		}


		std::cout << "Offset: " << offset.x << ", " << offset.y << std::endl;
	}

	Location Camera::GetOffset() { return offset; }
};
