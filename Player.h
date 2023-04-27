#pragma once

#include "surface.h"
#include "Location.h"

namespace Tmpl8
{
	class Player
	{
	public: // Public Functions //
		Player();
		void Draw(Surface* screen_in);								// Draw player
		void SetLoc(const Location& loc_in);						// Set player starting position
		void Move(const float& dt_in, const Location& delta_loc, class LevelManager& levelmanager, class MenuManager& menu);	// Move Player
		void Reset();
		void DeflectX(const float offset);
		void DeflectY(const float offset);
		void Death(Surface* screen, const float& deltaTime);
	public: // Getters & Setters //
		Location GetLoc();
		float GetRadius();
	private: // Private Functions //
		void CheckCollision(class LevelManager& levelmanager, class MenuManager& menu);
	private: // Other Functions //
		bool CircleToAABBCollision(const Location& tile, const float half);
	private: // Private Variables //
		Location loc = { 220.0f, 400.0f };			// Current location of the player
		Location speed = { 0.0f, 0.0f };			// Current speed of the player

		float radius; // Radius of the player ball

		static constexpr float gravity = 1.0f;			// Level of gravity
		static constexpr float bounceHeight = 1.0f;		// Level of bounce height
		static constexpr float playerSpeed = 1.0f;		// Level of player speed
		static constexpr float maxPlayerSpeed = 500.0f;	// Maximum allowed player speed (X direction only)

		int frame = 0;
		float timer = 0.1f;
		float frameTime = 0.1f;

		// Sprites //
		Sprite player;
		Sprite deathFX;
	};
};