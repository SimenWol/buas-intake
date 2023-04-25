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
		// void LoadLevel(const int level) const;
		void DrawLevel(Surface* screen, const int level);
		LevelState GetLevelState(const int level) const;
		TileContents GetContents(const Location& loc) const;
	private:
		void DrawTile(Surface* screen, const Location& loc, const Location& tileLoc);
	public:
		static constexpr int tileSize = 64; // Width & Height for each tile
	private:
		// int currentLevel = 0;

		static constexpr int numLevels = 1;
		LevelState state[numLevels] = { LevelState::Closed }; // Using an array to store level states. Defaults to closed.
	};

};