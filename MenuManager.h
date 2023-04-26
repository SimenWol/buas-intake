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
			Paused,			// Pause Menu
			Playing,		// Playing UI (pause button, etc.)
			Settings		// Settings Menu
		};
	public:
		MenuManager();
		void Draw(Surface* screen_in, Game& game_in, LevelManager& level);
		void SetMenuState(MenuState state_in);
		MenuState GetMenuState();
	private:
		MenuState menuState = MenuState::Main;


		// Sprites //
		Sprite mainMenu;
		Sprite levelSelectionMenu;
		Sprite pauseMenu;

		Sprite startButtonSprite;
		Sprite settingsButtonSprite;
		Sprite quitButtonSprite;

		Sprite backButtonSprite;
		Sprite levelOneButtonSprite;

		Sprite pauseButtonSprite;

		Sprite continueButtonSprite;
		Sprite menuButtonSprite;
		Sprite restartButtonSprite;

		// Buttons //
		Button startButton;
		Button settingsButton;
		Button quitButton;

		Button backButton;
		Button levelOneButton;

		Button pauseButton;

		Button continueButton;
		Button menuButton;
		Button restartButton;
	};

};