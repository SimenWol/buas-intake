#pragma once

#include "surface.h"
#include "game.h"
#include "Button.h"
#include "Timer.h"

namespace Tmpl8
{
	class MenuManager
	{
	public:
		enum class MenuState
		{
			LevelComplete,	// Menu that pops up after player completes a level
			LevelFailed,	// Menu that pops up after player fails a level
			LevelSelect,	// Level Selection Menu
			Main,			// Main Menu
			Paused,			// Pause Menu
			Playing,		// Playing UI (pause button, etc.)
			HowToPlay,		// How To Play Menu
			Controls,		// Controls Menu
		};
	public:
		// Constructor //
		MenuManager();

		// Setters //
		void SetMenuState(MenuState state_in) { menuState = state_in; };

		// Getters //
		MenuState GetMenuState() const { return menuState; };

		// Main Functions //
		void Draw(Surface* screen_in, Game& game_in, LevelManager& level, Timer& timer);
		void Tick(Game& game_in, LevelManager& level_in, Player& player, Timer& timer);
	private:
		MenuState menuState = MenuState::Main;


		// Sprites //
		Sprite mainMenu;
		Sprite howToPlayMenu;
		Sprite controlsMenu;
		Sprite levelSelectionMenu;
		Sprite levelCompletedMenu;
		Sprite levelFailedMenu;
		Sprite pauseMenu;

		// General
		Sprite backButtonSprite;
		Sprite menuButtonSprite;
		Sprite retryButtonSprite;

		// Main Menu
		Sprite startButtonSprite;
		Sprite howToPlayButtonSprite;
		Sprite quitButtonSprite;

		// How To Play Menu
		Sprite controlsButtonSprite;

		// Level Selection Menu
		Sprite levelOneButtonSprite;
		Sprite levelTwoButtonSprite;
		Sprite levelThreeButtonSprite;

		// Playing UI
		Sprite pauseButtonSprite;

		// Pause Menu
		Sprite continueButtonSprite;
		Sprite restartButtonSprite;

		// Level Completed Menu
		Sprite nextLevelButtonSprite;
		Sprite selectLevelButtonSprite;
		

		// Buttons //
		Button backButton;
		Button menuButton;
		Button retryButton;

		// Main Menu
		Button startButton;
		Button howToPlayButton;
		Button quitButton;

		// How To Play Menu
		Button controlsButton;

		// Level Selection Menu
		Button levelOneButton;
		Button levelTwoButton;
		Button levelThreeButton;

		// Playing UI
		Button pauseButton;

		// Pause Menu
		Button continueButton;
		Button restartButton;

		// Level Completed Menu
		Button nextLevelButton;
		Button selectLevelButton;
	};

};