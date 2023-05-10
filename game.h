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
	// All possible game states // 
	enum GameState
	{
		MENU,
		PLAYING
	};
public:
	// Constructor //
	Game();

	// Setters //
	void SetTarget( Surface* surface ) { screen = surface; }
	void SetState(GameState state_in) { state = state_in; }
	void SetAnimations(bool onOff) { animations = onOff; }
	void UnLockLevels();

	// Getters //
	bool GetAnimations() const { return animations; }
	bool GetUnlockLevels() const { return unlockAllLevels; }
	int GetMouseX() const { return mousex; }
	int GetMouseY() const { return mousey; }
	bool GetMouseDown() const { return mouseDown; }
	GameState GetGameState() const { return state; }

	// Main Functions //
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

	// Mouse variables //
	int mousex = 0;
	int mousey = 0;
	bool mouseDown = false;

	// Settings //
	bool animations = true;
	bool unlockAllLevels = false; // Changing this variable in header file does nothing!

	// Variables used for player movement //
	Location delta_loc = { 0.0f, 0.0f };
	bool movingLeft = false;
	bool movingRight = false;

	Sprite background;
};

}; // namespace Tmpl8