#pragma once

#include "Location.h"
#include "surface.h"
#include "MenuManager.h"

namespace Tmpl8
{
	class Finish
	{
	public:
		Finish();
		void Draw(Surface* screen, const int tilex, const int tiley, const float& dt);
		void Trigger(MenuManager& menu, class LevelManager& level);
	private:
		void UpdateFrame(const float& dt);
	private:
		int frame = 0;
		float timer = 0.1f;
		float frameTime = 0.1f;

		Sprite flag;
	};
};