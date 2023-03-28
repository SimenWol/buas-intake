#pragma once
#include "Player.h"
#include "Location.h"

namespace Tmpl8 {

// Forward Declaration //
class Surface;
class MenuManager;

class Game
{
public:
	enum GameState
	{
		MENU,
		PLAYING,
		GAMEOVER
	};
public:
	// Setters //
	void SetTarget( Surface* surface ) { screen = surface; }
	void SetState(GameState state_in) { state = state_in; }

	// Getters //
	static int GetMouseX() { return mousex; }
	static int GetMouseY() { return mousey; }
	static bool GetMouseDown() { return mouseDown; }

	// Main Game Functions //
	void Init();
	void Shutdown();
	void Tick( float deltaTime );

	// Input Functions //
	void MouseUp(int button);
	void MouseDown(int button);
	void MouseMove(int x, int y);

	void KeyUp(int key);
	void KeyDown(int key);
private:
	Surface* screen;
	MenuManager* menu;
	Player player;

	GameState state = GameState::MENU;
	
	Location delta_loc;

	static int mousex;
	static int mousey;
	static bool mouseDown;

	static bool movingLeft;
	static bool movingRight;
};

}; // namespace Tmpl8