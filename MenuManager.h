#pragma once

#include "surface.h"
#include "game.h"

namespace Tmpl8
{
	class MenuManager
	{
	public:
		enum MenuState
		{
			Main,			// Main Menu
			LevelSelect,	// Level Selection Menu
			LevelFailed,	// Menu that pops up after player fails a level
			LevelComplete	// Menu that pops up after player completes a level
		};
	public:
		void Draw(Surface* screen_in, Game& game_in);
		void SetMenuState(MenuState state_in);
		// LoadMenu?
	private:
		MenuState menuState = MenuState::Main;
	};

};