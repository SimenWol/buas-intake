#pragma once

#include "surface.h"
#include "Location.h"
#include "Player.h"
#include "Obstacle.h"

namespace Tmpl8
{
	class Finish;

	class LevelManager
	{
	public:
		enum LevelState
		{
			Closed,		// Unable to play level
			Open,		// Able to play level, never completed it
			Completed	// Completed the level at least once, still able to play level
		};
		enum class TileContents
		{
			Empty,
			Obstacle,
			Finish
		};
	public:
		LevelManager();
		void LoadLevel(const int level, Player& player);
		void DrawLevel(Surface* screen, const int level, const float& dt);
		void CallTrigger(const TileContents& content, const Location& tile, Player& player, class MenuManager& menu);
		LevelState GetLevelState(const int level) const;
		TileContents GetContents(const Location& loc) const;
		TileContents GetContents(const int x, const int y) const;
		int GetCurrentLevel() const;
	private:
		void DrawTile(Surface* screen, const Location& loc, const Location& tileLoc);
		void Reset(const int level, Player& player);
	public:
		static constexpr int tileSize = 48; // Width & Height for each tile
		static constexpr int numLevels = 1;
	private:
		int currentLevel = 0;
		LevelState state[numLevels] = { LevelState::Closed }; // Using an array to store level states. Defaults to closed.

		Location startLoc1 = {220.0f, 0.0f};

		Obstacle obstacle;
		Finish* finish;

		char map[8][81] = {
			"cbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcb",
			"cbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcb",
			"cbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcb",
			"cbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcb",
			"cbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcb",
			"cbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcb",
			"cbcbcbcbcbcbcbcbcbcbcb--cbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcb",
			"cbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcbcb",
		};

		char collisionMap[8][41] = {
			"oooooooooooooooooooooooooooooooooooooooo",
			"oooooooooooooooooooooooooooooooooooooooo",
			"oooooooooooooooooooooooooooooooooooooooo",
			"oooooooooooooooooooooooooooooooooooooooo",
			"oooooooooooooooooooooooooooooooooooooooo",
			"oooooooooooooooooooooooooooooooooooooooo",
			"-ooooooooooFoooooooooooooooooooooooooooo",
			"----------------------------------------",
		};
	};

};