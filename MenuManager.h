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
			Main,			// Main Menu
			LevelSelect,	// Level Selection Menu
			Playing,		// Playing UI (pause button, etc.)
			Paused,			// Pause menu
			LevelFailed,	// Menu that pops up after player fails a level
			LevelComplete	// Menu that pops up after player completes a level
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

		// Buttons //
		Button startButton;
		Button levelOneButton;
	};

};