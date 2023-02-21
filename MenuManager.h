#pragma once

#include "surface.h"

class MenuManager
{
public:
	enum MenuState
	{
		Main,			// Main Menu
		LevelSelect		// Level Selection Menu
	};
public:
	MenuManager(Tmpl8::Surface* screen_in);
	void Draw() const;
	// LoadMenu?
private:
	MenuState state = { MenuState::Main };
	Tmpl8::Surface* screen;
};