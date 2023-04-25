#pragma once

#include "game.h"
#include "surface.h"
#include <iostream>

namespace Tmpl8 // TODO: REMOVE LOGIC FROM ISPRESSED AND ADD PROPER FUNCTIONS FOR EACH CHECK --> UPDATE SPRITES
{
	class Button
	{
	public:
		Button(int x_in, int y_in, Sprite& sprite_in) // Button Constructor
			:
			x(x_in)
			,y(y_in)
			,sprite(sprite_in)
		{
			height = sprite.GetHeight();
			width = sprite.GetWidth();
		};

		bool IsPressed(Game& game)
		{
			if (CheckMousePos(game) == false)
			{
				prevMouseDown = false;
				return false;
			}
			if (CheckMouseDown(game) == false) { return false; }

			/* ======================== DEBUG ======================== */
			std::cout << "Button has been pressed at " << x << "," << y << std::endl;
			/* ======================================================= */

			return true; // Returns true if all of the above checks out
		};

		void Draw(Surface* screen, Game& game) // Draw button outlines (for debugging purposes). TODO: Draw correct button depending on mousehover state
		{
			if (CheckMousePos(game) && prevMouseDown) { sprite.SetFrame(2); }
			else if (CheckMousePos(game)) { sprite.SetFrame(1); }
			else { sprite.SetFrame(0); }

			sprite.Draw(screen, x, y);

			/* ======================== DEBUG ======================== */
			//screen->Box(x, y, x + width, y + height, 0x00ff00);
			/* ======================================================= */
		}

	private:
		bool CheckMousePos(Game& game) const // Checks if mouse is in boundaries
		{
			if (game.GetMouseX() < x || game.GetMouseX() > (x + width)) { return false; }
			if (game.GetMouseY() < y || game.GetMouseY() > (y + height)) { return false; }

			return true;
		}

		bool CheckMouseDown(Game& game)
		{
			if (game.GetMouseDown() == true)
			{
				prevMouseDown = true;
				return false;
			}
			else if (game.GetMouseDown() == false)
			{
				if (prevMouseDown == true)
				{
					prevMouseDown = false;
					return true;
				}
				else
				{
					prevMouseDown = false;
					return false;
				}
			}
			
			return false;
		}

	private:
		int x, y;
		int width, height;
		bool prevMouseDown = false;
		Sprite& sprite;
	};

};