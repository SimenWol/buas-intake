#include "Player.h"
#include "surface.h"

// Sprites used (only) in this file
Tmpl8::Sprite player(new Tmpl8::Surface("assets/Template/ball.png"), 1);

void Player::Draw(Tmpl8::Surface* screen_in)
{
	player.Draw(screen_in, x, y);
}
