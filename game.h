#pragma once
#include "Player.h"

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

	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }
private:
	Surface* screen;
	MenuManager* menu;
	Player player;

	GameState state = GameState::MENU;

	static int mousex;
	static int mousey;
	static bool mouseDown;
};

}; // namespace Tmpl8