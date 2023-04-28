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
		void Tick(Game& game_in, LevelManager& level_in, Player& player);
		void SetMenuState(MenuState state_in);
		MenuState GetMenuState();
	private:
		MenuState menuState = MenuState::Main;


		// Sprites //
		Sprite mainMenu;
		Sprite settingsMenu;
		Sprite levelSelectionMenu;
		Sprite levelCompletedMenu;
		Sprite levelFailedMenu;
		Sprite pauseMenu;
		// General
		Sprite backButtonSprite;
		Sprite retryButtonSprite;
		// Main Menu
		Sprite startButtonSprite;
		Sprite settingsButtonSprite;
		Sprite quitButtonSprite;
		// Level Selection Menu
		Sprite levelOneButtonSprite;
		// Playing UI
		Sprite pauseButtonSprite;
		// Pause Menu
		Sprite continueButtonSprite;
		Sprite menuButtonSprite;
		Sprite restartButtonSprite;
		// Level Completed Menu
		Sprite nextLevelButtonSprite;
		Sprite selectLevelButtonSprite;
		// Level Failed Menu
		Sprite menuSmallButtonSprite;

		// Buttons //
		Button backButton;
		Button retryButton;
		// Main Menu
		Button startButton;
		Button settingsButton;
		Button quitButton;
		// Level Selection Menu
		Button levelOneButton;
		// Playing UI
		Button pauseButton;
		// Pause Menu
		Button continueButton;
		Button menuButton;
		Button restartButton;
		// Level Completed Menu
		Button nextLevelButton;
		Button selectLevelButton;
		// Level Failed Menu
		Button menuSmallButton;
	};

};