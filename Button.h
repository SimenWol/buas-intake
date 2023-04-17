#pragma once

#include "game.h"
#include "surface.h"
#include <iostream>

namespace Tmpl8 // TODO: REMOVE LOGIC FROM ISPRESSED AND ADD PROPER FUNCTIONS FOR EACH CHECK --> UPDATE SPRITES
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

		bool isPressed(Game& game) const
		{
			if (game.GetMouseDown() != true) { return false; }								// Check if left mouse button is used
			if (game.GetMouseX() < x || game.GetMouseX() > (x + width)) { return false; }	// Check if mousex is in boundaries
			if (game.GetMouseY() < y || game.GetMouseY() > (y + height)) { return false; }	// Check if mousey is in boundaries

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