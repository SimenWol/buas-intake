#include "game.h"
#include "surface.h"
#include "MenuManager.h"
#include "Player.h"
#include "Location.h"
#include "LevelManager.h"

#include <iostream> 
#include <algorithm>
#include <SDL_scancode.h>

namespace Tmpl8
{
	// Initialise static variables //
	int Game::mousex = 0;
	int Game::mousey = 0;
	bool Game::mouseDown = false;

	bool Game::movingLeft = false;
	bool Game::movingRight = false;

	void Game::Init()
	{
		menu = new MenuManager;
	}
	
	void Game::Shutdown() {}

	void Game::Tick(float deltaTime)
	{
		// Multiply deltaTime by 0.001 to get deltaTime in seconds, much easier to work with
		// By using std::min, you prevent long frame pauses messing up the physics
		deltaTime = std::min(deltaTime * 0.001f, 0.05f);

		const float screenHeight = static_cast<float>(screen->GetHeight());

		// clear the graphics window
		screen->Clear(200);

		switch (state)
		{
		case MENU:
			// Draw Functions //
			menu->Draw(screen, *this);
			break;
		case PLAYING:
			// Game Logic //
			// Define moving direction from keyboard inputs
			if (movingLeft && movingRight || (!movingLeft && !movingRight)) { delta_loc = { 0, 0 }; }
			else if (movingLeft) { delta_loc = { -1, 0 }; }
			else if (movingRight) { delta_loc = { 1,0 }; }
			player.Move(deltaTime, delta_loc);

			// Draw Functions //
			level.DrawLevel(screen, 1);
			player.Draw(screen);

			break;
		case GAMEOVER:
			// Draw Functions //
			player.Draw(screen);
			menu->Draw(screen, *this);
			
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