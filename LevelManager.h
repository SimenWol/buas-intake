#pragma once

#include "surface.h"
#include "Location.h"

namespace Tmpl8
{
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
			Obstacle
		};
	public:
		LevelManager();
		// void LoadLevel(const int level, Player& player);
		void DrawLevel(Surface* screen, const int level);
		LevelState GetLevelState(const int level) const;
		TileContents GetContents(const Location& loc) const;
	private:
		void DrawTile(Surface* screen, const Location& loc, const Location& tileLoc);
		// void Reset(const int level, Player& player);
	public:
		static constexpr int tileSize = 64; // Width & Height for each tile
		static constexpr int numLevels = 1;
	private:
		// int currentLevel = 0;
		LevelState state[numLevels] = { LevelState::Closed }; // Using an array to store level states. Defaults to closed.

		Location startLoc1 = {220.0f, 400.0f};
	};

};