#pragma once

#include "Location.h"
#include "surface.h"

namespace Tmpl8
{
	class Camera
	{
	public:
		// Getter //
		Location GetOffset() const { return offset; };

		// Main Functions //
		void Tick(Surface* screen, const Location& playerLoc, const int level);
	private:
		Location offset = { 0.0f, 0.0f };
	};
};