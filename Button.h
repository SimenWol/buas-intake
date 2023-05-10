#pragma once

#include "game.h"
#include "surface.h"
#include "LevelManager.h"

#include <iostream>

namespace Tmpl8
{
	class Button
	{
	public:
		// Constructor //
		Button(int x_in, int y_in, Sprite& sprite_in)
			:
			x(x_in)
			,y(y_in)
			,sprite(sprite_in)
		{
			height = sprite.GetHeight();
			width = sprite.GetWidth();
		};

		// Setters //
		void SetLocation(int x_in, int y_in)
		{
			x = x_in;
			y = y_in;
		}

		// Main Functions //
		// Function that checks if a button has been pressed.
		bool IsPressed(Game& game)
		{
			if (CheckMousePos(game) == false) // Check mouse pos
			{
				prevMouseDown = false;
				return false;
			}
			if (CheckMouseDown(game) == false) { return false; } // Check mouse down

			/* ======================== DEBUG ======================== */
			std::cout << "Button has been pressed at " << x << "," << y << std::endl;
			/* ======================================================= */

			return true; // Returns true if all of the above checks out
		};

		// Draw Functions //
		// Draw function for 'normal' buttons.
		void Draw(Surface* screen, Game& game) 
		{
			if (sprite.Frames() == 3)
			{
				if (CheckMousePos(game) && prevMouseDown) { sprite.SetFrame(2); }
				else if (CheckMousePos(game)) { sprite.SetFrame(1); }
				else { sprite.SetFrame(0); }
			}

			sprite.Draw(screen, x, y);

			/* ======================== DEBUG ======================== */
			//screen->Box(x, y, x + width, y + height, 0x00ff00);
			/* ======================================================= */
		}

		// Draw function for Level Buttons.
		void Draw(Surface* screen, Game& game, LevelManager::LevelState state)
		{
			if (sprite.Frames() == 7) // Level Buttons
			{
				if (state == LevelManager::LevelState::Closed)
				{
					sprite.SetFrame(0);
				}
				else if (state == LevelManager::LevelState::Open)
				{
					if (CheckMousePos(game) && prevMouseDown) { sprite.SetFrame(3); }
					else if (CheckMousePos(game)) { sprite.SetFrame(2); }
					else { sprite.SetFrame(1); }
				}
				else if (state == LevelManager::LevelState::Completed)
				{
					if (CheckMousePos(game) && prevMouseDown) { sprite.SetFrame(6); }
					else if (CheckMousePos(game)) { sprite.SetFrame(5); }
					else { sprite.SetFrame(4); }
				}
			}

			sprite.Draw(screen, x, y);

			/* ======================== DEBUG ======================== */
			//screen->Box(x, y, x + width, y + height, 0x00ff00);
			/* ======================================================= */
		}

		// Draw function for settings buttons.
		void Draw(Surface* screen, Game& game, bool turnedOn) 
		{
			if (sprite.Frames() == 2) // Level Buttons
			{
				if (turnedOn)
				{ sprite.SetFrame(0); }
				else { sprite.SetFrame(1); }
			}

			sprite.Draw(screen, x, y);

			/* ======================== DEBUG ======================== */
			//screen->Box(x, y, x + width, y + height, 0x00ff00);
			/* ======================================================= */
		}

	private:
		// Function that checks if the mouse is in boundaries of the button.
		bool CheckMousePos(Game& game) const
		{
			if (game.GetMouseX() < x || game.GetMouseX() > (x + width)) { return false; }
			if (game.GetMouseY() < y || game.GetMouseY() > (y + height)) { return false; }

			return true;
		}

		// Function that checks if a button is released after being pressed, then returns true.
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