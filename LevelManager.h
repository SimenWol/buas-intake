#pragma once

#include "surface.h"
#include "Location.h"
#include "Player.h"
#include "Obstacle.h"
#include "WoodStakes.h"
#include "Spikes.h"

namespace Tmpl8
{
	class Finish;

	class LevelManager
	{
	public:
		enum class LevelState
		{
			Closed,		// Unable to play level
			Open,		// Able to play level, never completed it
			Completed	// Completed the level at least once, still able to play level
		};
		enum class TileContents
		{
			Empty,
			Obstacle,
			Finish,
			WoodStakes,
			SpikesBig,
			SpikesMedium,
			SpikesSmall,
		};
	public: // PUblic Functions //
		LevelManager();
		void LoadLevel(const int level, Player& player);
		void DrawLevel(Surface* screen, const int level, const float& dt);
		void CallTrigger(const TileContents& content, const Location& tile, Player& player, MenuManager& menu);
		void Death(Player& player, MenuManager& menu);
	public: // Getters & Setters //
		LevelState GetLevelState(const int level) const;
		void SetLevelState(const int level, const LevelState state_in);
		TileContents GetContents(const Location& loc) const;
		TileContents GetContents(const int x, const int y) const;
		int GetCurrentLevel() const;
		bool GetIsDead() const;
	private: // Private Functions //
		void DrawTile(Surface* screen, const Location& loc, const Location& tileLoc);
		void Reset(const int level, Player& player);
	public: // Public Variables //
		static constexpr int tileSize = 48; // Width & Height for each tile
		static constexpr int numLevels = 1;
	private: // Private Variables //
		int currentLevel = 0;
		LevelState state[numLevels] = { LevelState::Closed }; // Using an array to store level states. Defaults to closed.

		bool isDead = false;

		Location startLoc1 = {220.0f, 0.0f};

		Obstacle obstacle;
		WoodStakes woodstakes;
		Spikes spikes;
		Finish* finish;

		char map[8][81] = {
			"cbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcb",
			"cbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcb",
			"cbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcb",
			"cbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcb",
			"cbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcb",
			"cbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcb",
			"------cbcbcbcbcbcbcbcb--cbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcb",
			"cbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcb",
		};

		char collisionMap[8][41] = {
			"oooooooooooooooooooooooooooooooooooooooo",
			"oooooooooooooooooooooooooooooooooooooooo",
			"oooooooooooooooooooooooooooooooooooooooo",
			"oooooooooooooooooooooooooooooooooooooooo",
			"oooooooooooooooooooooooooooooooooooooooo",
			"oooooooooooooooooooooooooooooooooooooooo",
			"SscooooooooFoooooooooooooooooooooooooooo",
			"----------------------------------------",
		};
	};

};