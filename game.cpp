#include "game.h"
#include "surface.h"
#include "MenuManager.h"
#include "Player.h"
#include "Location.h"
#include "LevelManager.h"

#include <iostream> 
#include <algorithm>
#include <SDL.h>

namespace Tmpl8
{
	// Constructor //
	Game::Game()
		:background(new Surface("assets/Background/background.png"), 1)
	{}

	// Set all levels to open, only being able to fire once through menumanager.
	void Game::UnLockLevels()
	{
		for (int i = 0; i < level.numLevels; i++)
		{
			if (level.GetLevelState(i + 1) == LevelManager::LevelState::Closed)
				{ level.SetLevelState(i + 1, LevelManager::LevelState::Open); }
		}
		unlockAllLevels = true;
	}

	// Game init
	void Game::Init()
	{
		// Menu //
		menu = new MenuManager;
	}
	
	// Game shutdown
	void Game::Shutdown()
	{
		// Thanks to MAX in the 3dgep.com discord for sharing this code snippet.
		// https://discord.com/channels/515453022097244160/686661689894240277/1095673953734901761
		SDL_Event user_event;
		user_event.type = SDL_QUIT;
		SDL_PushEvent(&user_event);
		/////////////////////////////
	}

	// Main Game Function //
	void Game::Tick(float deltaTime)
	{
		// Multiply deltaTime by 0.001 to get deltaTime in seconds, much easier to work with.
		// By using std::min, you prevent long frame pauses messing up the physics.
		deltaTime = std::min(deltaTime * 0.001f, 0.05f);

		const float screenHeight = static_cast<float>(screen->GetHeight());

		// Reset window for new frame
		screen->Clear(0);
		background.Draw(screen, 0, 0);

		// Update menu
		menu->Tick(*this, level, player, timer);

		switch (state)
		{
		case MENU:
			// Draw Functions //
			menu->Draw(screen, *this, level, timer);
			break;
		case PLAYING:
			// Game Logic //
			if (menu->GetMenuState() == MenuManager::MenuState::Playing)
			{
				// Define moving direction from keyboard inputs
				if (movingLeft && movingRight || (!movingLeft && !movingRight)) { delta_loc = { 0.0f, 0.0f }; }
				else if (movingLeft) { delta_loc = { -1.0f, 0.0f }; }
				else if (movingRight) { delta_loc = { 1.0f, 0.0f }; }
				player.Move(deltaTime, delta_loc, level, *menu);

				// Update Camera Offset
				camera.Tick(screen, player.GetLoc(), level.GetCurrentLevel());

				// Update Timer
				timer.Tick(deltaTime, level, player, *menu);
			}

			// Update tile animations
			if (animations) { level.UpdateAnimations(deltaTime); }

			// Draw Functions //
			level.DrawLevel(screen, camera.GetOffset());
			if (animations && level.GetIsDead()) { player.DeathFX(screen, deltaTime, camera.GetOffset()); }
			if (animations && player.GetBounceFX()) { player.BounceFX(screen, deltaTime, camera.GetOffset()); }
			player.Draw(screen, camera.GetOffset());
			menu->Draw(screen, *this, level, timer);
			break;
		}

		/* ======================== DEBUG ======================== */
		// std::cout << "Frametimer: " << deltaTime << std::endl;						// Frametimer
		// std::cout << "MouseX: " << mousex << " MouseY: " << mousey << std::endl;		// Mouse Position
		// std::cout << "DeltaLoc: " << delta_loc.x << "," << delta_loc.y << std::endl; // Delta Location
		/* ======================================================= */
	}

	// MOUSE FUNCTIONS //
	// Changes mouseDown to false if left mouse button is not being pressed.
	void Game::MouseUp(int button)
	{
		if (button == 1) { Game::mouseDown = false; }
	}

	// Changes mouseDown to true if left mouse button is being pressed.
	void Game::MouseDown(int button) 
	{
		if (button == 1) { Game::mouseDown = true; }
	}

	// Changes mousex and mousey to (current) absolute mouse position.
	void Game::MouseMove(int x, int y) { mousex = x, mousey = y; } 

	// KEYBOARD FUNCTIONS //
	// https://wiki.libsdl.org/SDL2/SDL_Scancode

	// Checks if a key is released to stop moving in that direction.
	void Game::KeyUp(int key)
	{
		switch (key)
		{
		case(SDL_SCANCODE_LEFT):
			movingLeft = false;
			break;
		case(SDL_SCANCODE_A):
			movingLeft = false;
			break;
		case(SDL_SCANCODE_RIGHT):
			movingRight = false;
			break;
		case(SDL_SCANCODE_D):
			movingRight = false;
			break;
		default:
			break;
		}
	}

	// Checks if a key is pressed to start moving in that direction.
	void Game::KeyDown(int key)
	{
		switch (key)
		{
		case(SDL_SCANCODE_LEFT):
			movingLeft = true;
			break;
		case(SDL_SCANCODE_A):
			movingLeft = true;
			break;
		case(SDL_SCANCODE_RIGHT):
			movingRight = true;
			break;
		case(SDL_SCANCODE_D):
			movingRight = true;
			break;
		default:
			break;
		}
	}

};