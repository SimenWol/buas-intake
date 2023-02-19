#include "game.h"
#include "surface.h"

#include <iostream> 
#include <algorithm>

namespace Tmpl8
{
	void Game::Init() {}
	
	void Game::Shutdown() {}


	void Game::Tick(float deltaTime)
	{
		// Multiply deltaTime by 0.001 to get deltaTime in seconds, much easier to work with
		// By using std::min, you prevent long pauses messing up the physics
		deltaTime = std::min(deltaTime * 0.001f, 0.05f);
		std::cout << "Frametimer: " << deltaTime << std::endl;

		// clear the graphics window
		screen->Clear(0);
	}
};