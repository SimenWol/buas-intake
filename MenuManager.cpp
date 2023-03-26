#include "MenuManager.h"
#include "surface.h"
#include "Button.h"

// Sprites used (only) in this file
Tmpl8::Sprite mainMenu(new Tmpl8::Surface("assets/Temp/GAME TITLE SCREEN.png"), 1);
Tmpl8::Sprite levelSelection(new Tmpl8::Surface("assets/Temp/LEVEL SELECTION SCREEN.png"), 1);

// Buttons used (only) in this file
Button startButton(128, 373, 127, 71);
Button levelOneButton(176, 227, 55, 57);

void MenuManager::Draw(Tmpl8::Surface* screen_in) // Function that draws the required menu to the screen.
{

	switch (state)
	{
	case Main:
		// Draw UI Elements
		mainMenu.Draw(screen_in, 0, 0);

		// Button Logic
		if (startButton.isPressed()) { SetMenuState(LevelSelect); }

		/* ======================== DEBUG ======================== */
		// startButton.Draw(screen_in);
		/* ======================================================= */
		break;
	case LevelSelect:
		// Draw UI Elements
		levelSelection.Draw(screen_in, 0, 0);

		// Button Logic
		if (levelOneButton.isPressed()) { /* Set Level-/GameState to Level/Playing */ }

		/* ======================== DEBUG ======================== */
		// levelOneButton.Draw(screen_in);
		/* ======================================================= */
		break;
	}
}

void MenuManager::SetMenuState(MenuState state_in) { state = state_in; } // Function MenuState setter.