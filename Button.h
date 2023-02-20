#pragma once

#include "game.h"
#include "surface.h"

class Button
{
public:
	Button(int x_in, int y_in, int width_in, int height_in, Tmpl8::Surface* screen_in) // Button Constructor
		:
		x(x_in),
		y(y_in),
		width(width_in),
		height(height_in),
		screen(screen_in) {};

	bool isPressed() const
	{
		screen->Box(x, y, x + width - 1, y + height - 1, 0x00ff00);
		if (Tmpl8::Game::mouseDown != true) { return false; }									// Check if left mouse button is used
		if (Tmpl8::Game::mousex < x || Tmpl8::Game::mousex > (x + width)) { return false; }		// Check if mousex is in boundaries
		if (Tmpl8::Game::mousey < y || Tmpl8::Game::mousey > (y + height)) { return false; }	// Check if mousey is in boundaries
		
		return true; // Returns true if all of the above checks out
	};

	// Draw() --> Draw button outlines for debugging purposes.
private:
	int x, y;
	int width, height;
	Tmpl8::Surface* screen;
};