#include "MenuManager.h"
#include "surface.h"
#include "Button.h"
#include "game.h"

namespace Tmpl8
{
	MenuManager::MenuManager()
		:mainMenu(new Surface("assets/Menus/Title Screen.png"), 1)
		,levelSelection(new Surface("assets/Temp/LEVEL SELECTION SCREEN.png"), 1)
		,startButtonSprite(new Surface("assets/Buttons/StartButton.png"), 3)
		,settingsButtonSprite(new Surface("assets/Buttons/SettingsButton.png"), 3)
		,quitButtonSprite(new Surface("assets/Buttons/QuitButton.png"), 3)
		,startButton(35, 312, startButtonSprite)
		,settingsButton(35, 402, settingsButtonSprite)
		,quitButton(665, 402, quitButtonSprite)
		,levelOneButton(176, 227, startButtonSprite)
	{}

	void MenuManager::Draw(Surface* screen_in, Game& game_in) // Function that draws the required menu to the screen.
	{

		switch (menuState)
		{
		case LevelComplete:
			// Retry
			// Next Level
			// Level Select
			break;
		case LevelFailed:
			// Retry
			// Level Select
			break;
		case LevelSelect:
			// Draw UI Elements
			levelSelection.Draw(screen_in, 0, 0);

			// Button Logic
			if (levelOneButton.IsPressed(game_in)) { game_in.SetState(game_in.PLAYING); }

			/* ======================== DEBUG ======================== */
			// levelOneButton.Draw(screen_in);
			/* ======================================================= */
			break;
		case Main:
			// Draw UI Elements
			mainMenu.Draw(screen_in, 0, 0);
			startButton.Draw(screen_in, game_in);
			settingsButton.Draw(screen_in, game_in);
			quitButton.Draw(screen_in, game_in);

			// Button Logic
			if (startButton.IsPressed(game_in)) { SetMenuState(LevelSelect); }
			if (settingsButton.IsPressed(game_in)) { std::cout << "Settings Button" << std::endl; }
			if (quitButton.IsPressed(game_in)) { game_in.Shutdown(); }
			break;
		case Paused:
			// Quit Level
			// Continue
			break;
		case Playing:
			// Timer
			// Pause Button
			// Anything else UI
			break;
		}
	}

	void MenuManager::SetMenuState(MenuState state_in) { menuState = state_in; } // Function MenuState setter.
};