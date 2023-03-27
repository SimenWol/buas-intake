#pragma once

#include "game.h"
#include "surface.h"
#include <iostream>

namespace Tmpl8
{
	class Button
	{
	public:
		Button(int x_in, int y_in, int width_in, int height_in) // Button Constructor
			:
			x(x_in),
			y(y_in),
			width(width_in),
			height(height_in) {};

		bool isPressed() const
		{
			if (Game::GetMouseDown() != true) { return false; }									// Check if left mouse button is used
			if (Game::GetMouseX() < x || Game::GetMouseX() > (x + width)) { return false; }		// Check if mousex is in boundaries
			if (Game::GetMouseY() < y || Game::GetMouseY() > (y + height)) { return false; }	// Check if mousey is in boundaries

			/* ======================== DEBUG ======================== */
			std::cout << "Button has been pressed at " << x << "," << y << std::endl;
			/* ======================================================= */

			return true; // Returns true if all of the above checks out
		};

		void Draw(Surface* screen) // Draw button outlines (for debugging purposes). TODO: Draw correct button depending on mousehover state
		{
			screen->Box(x, y, x + width, y + height, 0x00ff00);
		}

	private:
		int x, y;
		int width, height;
	};

};