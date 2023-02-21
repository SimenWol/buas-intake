#pragma once

#include "surface.h"

class MenuManager
{
public:
	enum MenuState
	{
		Main,			// Main Menu
		LevelSelect,	// Level Selection Menu
		LevelFailed,	// Menu that pops up after player fails a level
		LevelComplete	// Menu that pops up after player completes a level
	};
public:
	MenuManager(Tmpl8::Surface* screen_in);
	void Draw() const;
	// LoadMenu?
private:
	MenuState state = { MenuState::Main }; // <-- Is this needed?
	Tmpl8::Surface* screen;
};