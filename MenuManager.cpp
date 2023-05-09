#include "MenuManager.h"
#include "surface.h"
#include "Button.h"
#include "game.h"

namespace Tmpl8
{
	// Initialise all UI.
	MenuManager::MenuManager()
		:mainMenu(new Surface("assets/UI/Menus/title.png"), 1)
		,howToPlayMenu(new Surface("assets/UI/Menus/how_to_play.png"), 1)
		,controlsMenu(new Surface("assets/UI/Menus/controls.png"), 1)
		,levelSelectionMenu(new Surface("assets/UI/Menus/level_select.png"), 1)
		,levelCompletedMenu(new Surface("assets/UI/Menus/level_completed.png"), 1)
		,levelFailedMenu(new Surface("assets/UI/Menus/level_failed.png"), 1)
		,pauseMenu(new Surface("assets/UI/Menus/pause.png"), 1)
		,backButtonSprite(new Surface("assets/UI/Buttons/back.png"), 3)
		,retryButtonSprite(new Surface("assets/UI/Buttons/retry.png"), 3)
		,startButtonSprite(new Surface("assets/UI/Buttons/start.png"), 3)
		,howToPlayButtonSprite(new Surface("assets/UI/Buttons/how_to_play.png"), 3)
		,quitButtonSprite(new Surface("assets/UI/Buttons/quit.png"), 3)
		,controlsButtonSprite(new Surface("assets/UI/Buttons/controls.png"), 3)
		,levelOneButtonSprite(new Surface("assets/UI/Buttons/level_one.png"), 7)
		,levelTwoButtonSprite(new Surface("assets/UI/Buttons/level_two.png"), 7)
		,levelThreeButtonSprite(new Surface("assets/UI/Buttons/level_three.png"), 7)
		,pauseButtonSprite(new Surface("assets/UI/Buttons/pause.png"), 3)
		,continueButtonSprite(new Surface("assets/UI/Buttons/continue.png"), 3)
		,menuButtonSprite(new Surface("assets/UI/Buttons/menu.png"), 3)
		,restartButtonSprite(new Surface("assets/UI/Buttons/restart.png"), 3)
		,nextLevelButtonSprite(new Surface("assets/UI/Buttons/next_level.png"), 3)
		,selectLevelButtonSprite(new Surface("assets/UI/Buttons/level_select.png"), 3)
		,backButton(0, 0, backButtonSprite)
		,menuButton(0, 0, menuButtonSprite)
		,retryButton(0, 0, retryButtonSprite)
		,startButton(35, 312, startButtonSprite)
		,howToPlayButton(35, 402, howToPlayButtonSprite)
		,quitButton(665, 402, quitButtonSprite)
		,controlsButton(306, 408, controlsButtonSprite)
		,levelOneButton(313, 232, levelOneButtonSprite)
		,levelTwoButton(413, 232, levelTwoButtonSprite)
		,levelThreeButton(513, 232, levelThreeButtonSprite)
		,pauseButton(760, 15, pauseButtonSprite)
		,continueButton(473, 281, continueButtonSprite)
		,restartButton(150, 281, restartButtonSprite)
		,nextLevelButton(357, 322, nextLevelButtonSprite)
		,selectLevelButton(267, 232, selectLevelButtonSprite)
	{}

	// Function that draws the required menu (and contents) to the screen.
	void MenuManager::Draw(Surface* screen_in, Game& game_in, LevelManager& level_in, Timer& timer)
	{

		switch (menuState)
		{
		case MenuState::LevelComplete:
			// Set UI Elements
			retryButton.SetLocation(213, 322);
			// Draw UI Elements
			levelCompletedMenu.Draw(screen_in, 0, 0);
			retryButton.Draw(screen_in, game_in);
			nextLevelButton.Draw(screen_in, game_in);
			selectLevelButton.Draw(screen_in, game_in);
			break;
		case MenuState::LevelFailed:
			// Set UI Elements
			menuButton.SetLocation(253, 277);
			retryButton.SetLocation(418, 277);
			// Draw UI Elements
			levelFailedMenu.Draw(screen_in, 0, 0);
			retryButton.Draw(screen_in, game_in);
			menuButton.Draw(screen_in, game_in);
			break;
		case MenuState::LevelSelect:
			// Set UI Elements
			backButton.SetLocation(350, 332);
			// Draw UI Elements
			levelSelectionMenu.Draw(screen_in, 0, 0);
			backButton.Draw(screen_in, game_in);
			levelOneButton.Draw(screen_in, game_in, level_in.GetLevelState(1));
			levelTwoButton.Draw(screen_in, game_in, level_in.GetLevelState(2));
			levelThreeButton.Draw(screen_in, game_in, level_in.GetLevelState(3));
			break;
		case MenuState::Main:
			// Draw UI Elements
			mainMenu.Draw(screen_in, 0, 0);
			startButton.Draw(screen_in, game_in);
			howToPlayButton.Draw(screen_in, game_in);
			quitButton.Draw(screen_in, game_in);
			break;
		case MenuState::Paused:
			// Set UI Elements
			menuButton.SetLocation(342, 281);
			// Draw UI Elements
			pauseMenu.Draw(screen_in, 0, 0);
			continueButton.Draw(screen_in, game_in);
			menuButton.Draw(screen_in, game_in);
			restartButton.Draw(screen_in, game_in);
			break;
		case MenuState::Playing:
			// Draw UI Elements
			pauseButton.Draw(screen_in, game_in);
			timer.Draw(screen_in, screen_in->GetWidth() / 2, 10);
			break;
		case MenuState::HowToPlay:
			// Set UI Elements
			backButton.SetLocation(10, 426);
			// Draw UI Elements
			howToPlayMenu.Draw(screen_in, 0, 0);
			backButton.Draw(screen_in, game_in);
			controlsButton.Draw(screen_in, game_in);
			break;
		case MenuState::Controls:
			// Set UI Elements
			backButton.SetLocation(10, 426);
			// Draw UI Elements
			controlsMenu.Draw(screen_in, 0, 0);
			backButton.Draw(screen_in, game_in);
			break;
		default:
			break;
		}
	}

	// Function that checks for button presses and calls the required function upon button release.
	void MenuManager::Tick(Game& game_in, LevelManager& level_in, Player& player, Timer& timer)
	{
		switch (menuState)
		{
		case MenuState::LevelComplete:
			// Button Logic
			if (retryButton.IsPressed(game_in))
			{
				level_in.LoadLevel(level_in.GetCurrentLevel(), player, timer);
				SetMenuState(MenuState::Playing);
			}
			if (nextLevelButton.IsPressed(game_in))
			{
				if (level_in.GetCurrentLevel() == LevelManager::numLevels) { SetMenuState(MenuState::LevelSelect); }
				else
				{
					level_in.LoadLevel(level_in.GetCurrentLevel() + 1, player, timer);
					SetMenuState(MenuState::Playing);
				}
			}
			if (selectLevelButton.IsPressed(game_in))
			{
				SetMenuState(MenuState::LevelSelect);
				game_in.SetState(Game::GameState::MENU);
			}
			break;
		case MenuState::LevelFailed:
			// Button Logic
			if (retryButton.IsPressed(game_in))
			{
				level_in.LoadLevel(level_in.GetCurrentLevel(), player, timer);
				SetMenuState(MenuState::Playing);
			}
			if (menuButton.IsPressed(game_in))
			{
				SetMenuState(MenuState::Main);
				game_in.SetState(Game::GameState::MENU);
			}
			break;
		case MenuState::LevelSelect:
			// Button Logic
			if (backButton.IsPressed(game_in))
			{
				if (game_in.GetGameState() == Game::GameState::PLAYING) { SetMenuState(MenuState::LevelComplete); }
				else { SetMenuState(MenuState::Main); }
			}
			if (level_in.GetLevelState(1) != LevelManager::LevelState::Closed
				&& levelOneButton.IsPressed(game_in))
			{
				level_in.LoadLevel(1, player, timer);
				game_in.SetState(game_in.PLAYING);
				SetMenuState(MenuState::Playing);
			}
			if (level_in.GetLevelState(2) != LevelManager::LevelState::Closed
				&& levelTwoButton.IsPressed(game_in))
			{
				level_in.LoadLevel(2, player, timer);
				game_in.SetState(game_in.PLAYING);
				SetMenuState(MenuState::Playing);
			}
			if (level_in.GetLevelState(3) != LevelManager::LevelState::Closed
				&& levelThreeButton.IsPressed(game_in))
			{
				level_in.LoadLevel(3, player, timer);
				game_in.SetState(game_in.PLAYING);
				SetMenuState(MenuState::Playing);
			}
			break;
		case MenuState::Main:
			// Button Logic
			if (startButton.IsPressed(game_in)) { SetMenuState(MenuState::LevelSelect); }
			if (howToPlayButton.IsPressed(game_in)) { SetMenuState(MenuState::HowToPlay); }
			if (quitButton.IsPressed(game_in)) { game_in.Shutdown(); }
			break;
		case MenuState::Paused:
			// Button Logic
			if (continueButton.IsPressed(game_in)) { SetMenuState(MenuState::Playing); }
			if (menuButton.IsPressed(game_in))
			{
				SetMenuState(MenuState::Main);
				game_in.SetState(Game::GameState::MENU);
			}
			if (restartButton.IsPressed(game_in))
			{
				level_in.LoadLevel(level_in.GetCurrentLevel(), player, timer);
				SetMenuState(MenuState::Playing);
			}
			break;
		case MenuState::Playing:
			// Button Logic
			if (pauseButton.IsPressed(game_in)) { SetMenuState(MenuState::Paused); }
			break;
		case MenuState::HowToPlay:
			// Button Logic
			if (backButton.IsPressed(game_in)) { SetMenuState(MenuState::Main); }
			if (controlsButton.IsPressed(game_in)) { SetMenuState(MenuState::Controls); }
			break;
		case MenuState::Controls:
			// Button Logic
			if (backButton.IsPressed(game_in)) { SetMenuState(MenuState::HowToPlay); }
			break;
		default:
			break;
		}
	}
};