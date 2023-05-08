#pragma once
#include "Player.h"
#include "LevelManager.h"
#include "Location.h"
#include "Camera.h"
#include "Timer.h"

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
		PLAYING
	};
public:
	// Setters //
	void SetTarget( Surface* surface ) { screen = surface; }
	void SetState(GameState state_in) { state = state_in; }

	// Getters //
	int GetMouseX() const { return mousex; }
	int GetMouseY() const { return mousey; }
	bool GetMouseDown() const { return mouseDown; }
	GameState GetGameState() const { return state; }

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
	LevelManager level;
	Timer timer;
	Player player;

	Camera camera;

	GameState state = GameState::MENU;

	int mousex = 0;
	int mousey = 0;
	bool mouseDown = false;

	Location delta_loc;
	bool movingLeft = false;
	bool movingRight = false;
};

}; // namespace Tmpl8