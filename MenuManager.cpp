#include "MenuManager.h"
#include "surface.h"
#include "Button.h"
#include "game.h"

namespace Tmpl8
{
	MenuManager::MenuManager()
		:mainMenu(new Surface("assets/Temp/GAME TITLE SCREEN.png"), 1)
		,levelSelection(new Surface("assets/Temp/LEVEL SELECTION SCREEN.png"), 1)
		,startButton(128, 373, 127, 71)
		,levelOneButton(176, 227, 55, 57)
	{}

	void MenuManager::Draw(Surface* screen_in, Game& game_in) // Function that draws the required menu to the screen.
	{

		switch (menuState)
		{
		case Main:
			// Draw UI Elements
			mainMenu.Draw(screen_in, 0, 0);

			// Button Logic
			if (startButton.isPressed(game_in)) { SetMenuState(LevelSelect); }

			/* ======================== DEBUG ======================== */
			// startButton.Draw(screen_in);
			/* ======================================================= */
			break;
		case LevelSelect:
			// Draw UI Elements
			levelSelection.Draw(screen_in, 0, 0);

			// Button Logic
			if (levelOneButton.isPressed(game_in)) { game_in.SetState(game_in.PLAYING); }

			/* ======================== DEBUG ======================== */
			// levelOneButton.Draw(screen_in);
			/* ======================================================= */
			break;
		}
	}

	void MenuManager::SetMenuState(MenuState state_in) { menuState = state_in; } // Function MenuState setter.

};