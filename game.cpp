#include "game.h"
#include "surface.h"
#include <cstdio> //printf

namespace Tmpl8
{
	void Game::Init() {}
	
	void Game::Shutdown() {}


	void Game::Tick(float deltaTime)
	{
		// clear the graphics window
		screen->Clear(0);
	}
};