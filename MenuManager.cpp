#include "MenuManager.h"
#include "surface.h"
#include "Button.h"

// Sprites used (only) in this file
Tmpl8::Sprite mainMenu(new Tmpl8::Surface("assets/Temp/GAME TITLE SCREEN.png"), 1);

// Buttons used (only) in this file
Button startButton(128, 373, 127, 71);

void MenuManager::Draw(Tmpl8::Surface* screen_in) // Function that draws the required menu to the screen.
{

	switch (state)
	{
	case Main:
		mainMenu.Draw(screen_in, 0, 0);
		if (startButton.isPressed()) { SetMenuState(LevelSelect); }

		/* ======================== DEBUG ======================== */
		// startButton.Draw(screen_in);
		/* ======================================================= */
		break;
	case LevelSelect:
		// Draw & call actions that are needed
		break;
	}
}

void MenuManager::SetMenuState(MenuState state_in) { state = state_in; }