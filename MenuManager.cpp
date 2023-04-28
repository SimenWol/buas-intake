#include "MenuManager.h"
#include "surface.h"
#include "Button.h"
#include "game.h"

namespace Tmpl8
{
	MenuManager::MenuManager()
		:mainMenu(new Surface("assets/Menus/Title Screen.png"), 1)
		,settingsMenu(new Surface("assets/Menus/Settings Screen.png"), 1)
		,levelSelectionMenu(new Surface("assets/Menus/Level Selection Screen.png"), 1)
		,levelCompletedMenu(new Surface("assets/Menus/Level Completed Screen.png"), 1)
		,levelFailedMenu(new Surface("assets/Menus/Level Failed Screen.png"), 1)
		,pauseMenu(new Surface("assets/Menus/Pause Screen.png"), 1)
		,backButtonSprite(new Surface("assets/Buttons/BackButton.png"), 3)
		,retryButtonSprite(new Surface("assets/Buttons/RetryButton.png"), 3)
		,startButtonSprite(new Surface("assets/Buttons/StartButton.png"), 3)
		,settingsButtonSprite(new Surface("assets/Buttons/SettingsButton.png"), 3)
		,quitButtonSprite(new Surface("assets/Buttons/QuitButton.png"), 3)
		,levelOneButtonSprite(new Surface("assets/Buttons/LevelOneButton.png"), 7)
		,pauseButtonSprite(new Surface("assets/Buttons/PauseButton.png"), 3)
		,continueButtonSprite(new Surface("assets/Buttons/ContinueButton.png"), 3)
		,menuButtonSprite(new Surface("assets/Buttons/MenuButton.png"), 3)
		,restartButtonSprite(new Surface("assets/Buttons/RestartButton.png"), 3)
		,nextLevelButtonSprite(new Surface("assets/Buttons/NextLevelButton.png"), 3)
		,selectLevelButtonSprite(new Surface("assets/Buttons/SelectLevelButton.png"), 3)
		,menuSmallButtonSprite(new Surface("assets/Buttons/MenuButtonSmall.png"), 3)
		,backButton(0, 0, backButtonSprite)
		,retryButton(0, 0, retryButtonSprite)
		,startButton(35, 312, startButtonSprite)
		,settingsButton(35, 402, settingsButtonSprite)
		,quitButton(665, 402, quitButtonSprite)
		,levelOneButton(362, 218, levelOneButtonSprite)
		,pauseButton(760, 15, pauseButtonSprite)
		,continueButton(312, 181, continueButtonSprite)
		,menuButton(312, 385, menuButtonSprite)
		,restartButton(312, 283, restartButtonSprite)
		,nextLevelButton(15, 332, nextLevelButtonSprite)
		,selectLevelButton(15, 422, selectLevelButtonSprite)
		,menuSmallButton(225, 219, menuSmallButtonSprite)
	{}

	void MenuManager::Draw(Surface* screen_in, Game& game_in, LevelManager& level_in, Timer& timer) // Function that draws the required menu to the screen.
	{

		switch (menuState)
		{
		case LevelComplete:
			// Set UI Elements
			retryButton.SetLocation(660, 422);
			// Draw UI Elements
			levelCompletedMenu.Draw(screen_in, 0, 0);
			retryButton.Draw(screen_in, game_in);
			nextLevelButton.Draw(screen_in, game_in);
			selectLevelButton.Draw(screen_in, game_in);
			break;
		case LevelFailed:
			// Set UI Elements
			retryButton.SetLocation(450, 219);
			// Draw UI Elements
			levelFailedMenu.Draw(screen_in, 0, 0);
			retryButton.Draw(screen_in, game_in);
			menuSmallButton.Draw(screen_in, game_in);
			break;
		case LevelSelect:
			// Set UI Elements
			backButton.SetLocation(25, 412);
			// Draw UI Elements
			levelSelectionMenu.Draw(screen_in, 0, 0);
			backButton.Draw(screen_in, game_in);
			levelOneButton.Draw(screen_in, game_in, level_in.GetLevelState(1));
			// More Level Buttons
			break;
		case Main:
			// Draw UI Elements
			mainMenu.Draw(screen_in, 0, 0);
			startButton.Draw(screen_in, game_in);
			settingsButton.Draw(screen_in, game_in);
			quitButton.Draw(screen_in, game_in);
			break;
		case Paused:
			// Draw UI Elements
			pauseMenu.Draw(screen_in, 0, 0);
			continueButton.Draw(screen_in, game_in);
			menuButton.Draw(screen_in, game_in);
			restartButton.Draw(screen_in, game_in);
			break;
		case Playing:
			// Draw UI Elements
			pauseButton.Draw(screen_in, game_in);
			timer.Draw(screen_in, screen_in->GetWidth() / 2, 10);
			// Anything else UI
			break;
		case Settings:
			// Set UI Elements
			backButton.SetLocation(25, 412);
			// Draw UI Elements
			settingsMenu.Draw(screen_in, 0, 0);
			backButton.Draw(screen_in, game_in);
			// Options
			break;
		default:
			break;
		}
	}

	void MenuManager::Tick(Game& game_in, LevelManager& level_in, Player& player, Timer& timer)
	{
		switch (menuState)
		{
		case Tmpl8::MenuManager::LevelComplete:
			// Button Logic
			if (retryButton.IsPressed(game_in))
			{
				level_in.LoadLevel(level_in.GetCurrentLevel(), player, timer);
				SetMenuState(Playing);
			}
			if (nextLevelButton.IsPressed(game_in)) { std::cout << "Next Level!" << std::endl; } // TODO: NEXT LEVEL!
			if (selectLevelButton.IsPressed(game_in))
			{
				SetMenuState(LevelSelect);
				game_in.SetState(Game::GameState::MENU);
			}
			break;
		case Tmpl8::MenuManager::LevelFailed:
			// Button Logic
			if (retryButton.IsPressed(game_in))
			{
				level_in.LoadLevel(level_in.GetCurrentLevel(), player, timer);
				SetMenuState(Playing);
			}
			if (menuSmallButton.IsPressed(game_in))
			{
				SetMenuState(Main);
				game_in.SetState(Game::GameState::MENU);
			}
			break;
		case Tmpl8::MenuManager::LevelSelect:
			// Button Logic
			if (backButton.IsPressed(game_in)) { SetMenuState(Main); }
			if (level_in.GetLevelState(1) != LevelManager::LevelState::Closed
				&& levelOneButton.IsPressed(game_in))
			{
				level_in.LoadLevel(1, player, timer);
				game_in.SetState(game_in.PLAYING);
				SetMenuState(Playing);
			}
			break;
		case Tmpl8::MenuManager::Main:
			// Button Logic
			if (startButton.IsPressed(game_in)) { SetMenuState(LevelSelect); }
			if (settingsButton.IsPressed(game_in)) { SetMenuState(Settings); }
			if (quitButton.IsPressed(game_in)) { game_in.Shutdown(); }
			break;
		case Tmpl8::MenuManager::Paused:
			// Button Logic
			if (continueButton.IsPressed(game_in)) { SetMenuState(Playing); }
			if (menuButton.IsPressed(game_in))
			{
				SetMenuState(Main);
				game_in.SetState(Game::GameState::MENU);
			}
			if (restartButton.IsPressed(game_in))
			{
				level_in.LoadLevel(level_in.GetCurrentLevel(), player, timer);
				SetMenuState(Playing);
			}
			if (restartButton.IsPressed(game_in)) { level_in.LoadLevel(level_in.GetCurrentLevel(), player, timer); }
			break;
		case Tmpl8::MenuManager::Playing:
			// Button Logic
			if (pauseButton.IsPressed(game_in)) { SetMenuState(Paused); }
			break;
		case Tmpl8::MenuManager::Settings:
			// Button Logic
			if (backButton.IsPressed(game_in)) { SetMenuState(Main); }
			break;
		default:
			break;
		}
	}

	void MenuManager::SetMenuState(MenuState state_in) { menuState = state_in; } // Function MenuState setter.

	MenuManager::MenuState MenuManager::GetMenuState() { return menuState; }
};