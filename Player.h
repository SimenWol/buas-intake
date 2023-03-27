#pragma once

#include "surface.h"

class Player
{
public:
	void Draw(Tmpl8::Surface* screen_in);
private:
	int x = 20, y = 20;
};