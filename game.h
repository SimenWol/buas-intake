#pragma once
#include "MenuManager.h"
#include "Player.h"

namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp(int button);
	void MouseDown(int button);
	void MouseMove(int x, int y);
	static int GetMouseX() { return mousex; }
	static int GetMouseY() { return mousey; }
	static bool GetMouseDown() { return mouseDown; }
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }
private:
	Surface* screen;
	MenuManager menu;
	Player player;

	static int mousex;
	static int mousey;
	static bool mouseDown;
};

}; // namespace Tmpl8