#pragma once

#include "surface.h"
#include "game.h"
#include "Button.h"

namespace Tmpl8
{
	class MenuManager
	{
	public:
		enum MenuState
		{
			LevelComplete,	// Menu that pops up after player completes a level
			LevelFailed,	// Menu that pops up after player fails a level
			LevelSelect,	// Level Selection Menu
			Main,			// Main Menu
			Paused,			// Pause menu
			Playing,		// Playing UI (pause button, etc.)
		};
	public:
		MenuManager();
		void Draw(Surface* screen_in, Game& game_in);
		void SetMenuState(MenuState state_in);
	private:
		MenuState menuState = MenuState::Main;


		// Sprites //
		Sprite mainMenu;
		Sprite levelSelection;

		Sprite startButtonSprite;
		Sprite settingsButtonSprite;
		Sprite quitButtonSprite;

		// Buttons //
		Button startButton;
		Button settingsButton;
		Button quitButton;

		Button levelOneButton;
	};

};