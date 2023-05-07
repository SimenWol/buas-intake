#pragma once

#include "surface.h"
#include "Location.h"

namespace Tmpl8
{
	class Player
	{
	public: // Public Functions //
		Player();
		void Draw(Surface* screen_in, const Location& drawOffset);	// Draw player
		void SetLoc(const Location& loc_in);						// Set player starting position
		void Move(const float& dt_in, const Location& delta_loc, class LevelManager& levelmanager, class MenuManager& menu);	// Move Player
		void Reset();
		void BounceFX(Surface* screen, const float& deltaTime, const Location& drawOffset);
		void DeflectX(const float offset);
		void DeflectY(const float offset);
		void DeathFX(Surface* screen, const float& deltaTime, const Location& drawOffset);
		bool CheckCollision(const Location& topLeft, const Location& bottomRight) const;
	public: // Getters & Setters //
		Location GetLoc() const;
		float GetRadius() const;
		bool GetBounceFX() const;
	private: // Private Functions //
		void CheckCollision(class LevelManager& levelmanager, class MenuManager& menu);
	private: // Other Functions //
		bool CircleToAABBCollision(const Location& tile, const float half) const;
		bool CircleToAABBCollision(const Location& center, const Location& half) const;
	private: // Private Variables //
		Location loc = { 220.0f, 400.0f };			// Current location of the player
		Location speed = { 0.0f, 0.0f };			// Current speed of the player

		float radius; // Radius of the player ball

		static constexpr float gravity = 1.0f;			// Level of gravity
		static constexpr float bounceHeight = 2.0f;		// Level of bounce height
		static constexpr float playerSpeed = 1.0f;		// Level of player speed
		static constexpr float maxPlayerSpeed = 500.0f;	// Maximum allowed player speed (X direction only)

		bool playBounceFX = false;
		Location bounceLoc = { 0.0f, 0.0f };

		int deathFrame = 0;
		float deathTimer = 0.1f;
		int bounceFrame = 0;
		float bounceTimer = 0.05f;
		float frameTime = 0.05f;

		// Sprites //
		Sprite player;
		Sprite deathFX;
		Sprite bounceFX;
	};
};