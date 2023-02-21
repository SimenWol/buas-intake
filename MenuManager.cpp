#include "MenuManager.h"
#include "surface.h"

MenuManager::MenuManager(Tmpl8::Surface* screen_in)
	:
	screen(screen_in) {}

void MenuManager::Draw() const
{
	switch (state)
	{
	case Main:
		// Draw & call actions that are needed
		break;
	case LevelSelect:
		// Draw & call actions that are needed
		break;
	}
}
