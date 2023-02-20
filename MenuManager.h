#pragma once

class MenuManager
{
public:
	enum MenuState
	{
		Main,			// Main Menu
		LevelSelect		// Level Selection Menu
	};
public:
	void Draw() const;
	// LoadMenu?
private:
	MenuState state = { MenuState::Main };
};