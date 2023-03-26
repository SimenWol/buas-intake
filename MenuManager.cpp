#include "MenuManager.h"
#include "surface.h"

// Sprites used (only) in this file
Tmpl8::Sprite mainMenu(new Tmpl8::Surface("assets/Temp/GAME TITLE SCREEN.png"), 1);


void MenuManager::Draw(Tmpl8::Surface* screen_in) const // Function that draws the required menu to the screen.
{

	switch (state)
	{
	case Main:
		mainMenu.Draw(screen_in, 0, 0);
		break;
	case LevelSelect:
		// Draw & call actions that are needed
		break;
	}
}
