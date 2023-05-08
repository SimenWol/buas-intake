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
	void Game::Init()
	{
		// Menu //
		menu = new MenuManager;
	}
	
	void Game::Shutdown()
	{
		// Thanks to MAX in the 3dgep.com discord for sharing this code snippet.
		// https://discord.com/channels/515453022097244160/686661689894240277/1095673953734901761
		SDL_Event user_event;
		user_event.type = SDL_QUIT;
		SDL_PushEvent(&user_event);
	}

	void Game::Tick(float deltaTime)
	{
		// Multiply deltaTime by 0.001 to get deltaTime in seconds, much easier to work with
		// By using std::min, you prevent long frame pauses messing up the physics
		deltaTime = std::min(deltaTime * 0.001f, 0.05f);

		const float screenHeight = static_cast<float>(screen->GetHeight());

		// clear the graphics window
		screen->Clear(0);

		switch (state)
		{
		case MENU:
			// Draw Functions //
			menu->Tick(*this, level, player, timer);
			menu->Draw(screen, *this, level, timer);
			break;
		case PLAYING:
			// Game Logic //
			menu->Tick(*this, level, player, timer);

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

			// Draw Functions //
			level.DrawLevel(screen, deltaTime, camera.GetOffset());
			if (level.GetIsDead()) { player.DeathFX(screen, deltaTime, camera.GetOffset()); }
			if (player.GetBounceFX()) { player.BounceFX(screen, deltaTime, camera.GetOffset()); }
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
	void Game::MouseUp(int button) // Changes mouseDown to false if left mouse button is not being pressed.
	{
		if (button == 1) { Game::mouseDown = false; }
	}

	void Game::MouseDown(int button) // Changes mouseDown to true if left mouse button is being pressed.
	{
		if (button == 1) { Game::mouseDown = true; }
	}

	void Game::MouseMove(int x, int y) { mousex = x, mousey = y; } // Changes mousex and mousey to (current) absolute mouse position.

	// KEYBOARD FUNCTIONS //
	// https://wiki.libsdl.org/SDL2/SDL_Scancode
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