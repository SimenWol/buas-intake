#pragma once

#include "Location.h"
#include "surface.h"

namespace Tmpl8
{
	class Camera
	{
	public:
		// Camera();
		void Tick(Surface* screen, const Location& playerLoc, const int level);
	public:
		Location GetOffset();
	private:
		Location offset = { 0.0f, 0.0f };
	};
};