#include "game.h"
#include "surface.h"
#include "MenuManager.h"
#include "Player.h"

#include <iostream> 
#include <algorithm>

namespace Tmpl8
{
	int Game::mousex = 0;
	int Game::mousey = 0;
	bool Game::mouseDown = 0;

	void Game::Init() {}
	
	void Game::Shutdown() {}

	void Game::Tick(float deltaTime)
	{
		// Multiply deltaTime by 0.001 to get deltaTime in seconds, much easier to work with
		// By using std::min, you prevent long pauses messing up the physics
		deltaTime = std::min(deltaTime * 0.001f, 0.05f);

		// clear the graphics window
		screen->Clear(0);

		menu.Draw(screen);
		player.Draw(screen);


		/* ======================== DEBUG ======================== */
		// std::cout << "Frametimer: " << deltaTime << std::endl;						// Frametimer
		// std::cout << "MouseX: " << mousex << " MouseY: " << mousey << std::endl;		// Mouse Position
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

};