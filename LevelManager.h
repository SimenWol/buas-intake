#pragma once

#include "surface.h"
#include "Location.h"
#include "Player.h"
#include "Timer.h"
#include "Obstacle.h"
#include "WoodStakes.h"
#include "Spikes.h"
#include "Water.h"

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
			ArrowSign,
			Obstacle,
			Finish,
			Water,
			FakeWater, // Water that doesn't do collision detection.
			WoodStakes,
			SpikesBig,
			SpikesMedium,
			SpikesSmall,
			SpikesFloor, // Only the purple floor from spikes.
		};
	public: // PUblic Functions //
		LevelManager();
		void LoadLevel(const int level, Player& player, Timer& timer);
		void DrawLevel(Surface* screen, const float& dt, const Location& drawOffset);
		void CallTrigger(const TileContents& content, const Location& tile, Player& player, class MenuManager& menu);
		void Death(Player& player, class MenuManager& menu);
	public: // Getters & Setters //
		LevelState GetLevelState(const int level) const;
		void SetLevelState(const int level, const LevelState state_in);
		TileContents GetContents(const Location& loc) const;
		TileContents GetContents(const int x, const int y) const;
		int GetCurrentLevel() const;
		bool GetIsDead() const;
	private: // Private Functions //
		void DrawTile(Surface* screen, const Location& loc, const Location& tile);
		void Reset(Player& player);
	public: // Public Variables //
		static constexpr int tileSize = 48; // Width & Height for each tile
		static constexpr int numLevels = 2; // Total amount of levels
	private: // Private Variables //
		int currentLevel = 0;
		LevelState state[numLevels] = { LevelState::Closed }; // Using an array to store level states. Defaults to closed.

		bool isDead = false;

		Obstacle obstacle;
		Water water;
		WoodStakes woodstakes;
		Spikes spikes;
		Finish* finish;

		Sprite arrowSign;

	private:
		// CollMap codes //
		// o: empty
		// A: arrow
		// -: Obstacle
		// F: Finish
		// W: Water
		// w: FakeWater
		// X: WoodStakes
		// S: SpikesBig
		// s: SpikesMedium
		// c: SpikesSmall
		// C: SpikesFloor

		// LEVEL 1 //
		const Location startLoc1 = { 432.0f, 384.0f };
		const float time1 = 10.0f;

		const char levelOne[11][101] = {
			"----------------------------------------------------------------------------------------------------",
			"----------------------------------------------------------------------------------------------------",
			"----------------------------------------------------------------------------------------------------",
			"----------------------------------------------------------------------------------------------------",
			"----------------------------------------------------------------------------------------------------",
			"----------------------------------------------------------------------------------------------------",
			"----------------------------------------------------------------------------------------------------",
			"----------------------------------------------------------------------------------------------------",
			"----------------------------------------------------------------------------------------------------",
			"----------------------------------cbebdbebdbfb--------cbebdbebdbebdbebdbebdbebdbebdbebdbebdbebdbebdb",
			"----------------cbdbebdbebdbebdbebccedcdedededececedededecedcdedededecedededecedecedededcdedecededed",
		};
		const char levelOneColl[11][51] = {
			"-oooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-oooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-oooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-oooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-oooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-oooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-oooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-oooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-ooooooooooooooooooooooooooooccooccoooooFooXXXXXXX",
			"-ooooooooooAooooo-----CSSSSC----------------------",
			"WWWWWWWWw-----------------------------------------",
		};

		// LEVEL 2 //
		const Location startLoc2 = { 528.0f, 48.0f };
		const float time2 = 99.0f;

		const char levelTwo[11][101] =
		{
			"----------------------------------------------------------------------------------------------------",
			"----------------------------------------------------------------------------------------------------",
			"----------------------------------------------------------------------------------------------------",
			"--------------------idjdkd--------------------------------------------------------------------------",
			"----------------------------------------------------------------------------------------------------",
			"----------------------------------------------------------------------------------------------------",
			"----------------------------------------------------------------------------------------------------",
			"----------------------------------------------------------------------------------------------------",
			"----------------------------------------------------------------------------------------------------",
			"----------------------------------------------------------------------------------------------------",
			"----------------------------------------------------------------------------------------------------",
		};
		const char levelTwoColl[11][51] =
		{
			"-oooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-oooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-ooooooooooAooooooooooooooooooooooooooooooooooooo-",
			"-ooooooooo---oooooooooooooooooooooooooooooooooooo-",
			"-oooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-oooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-oooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-oooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-oooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-oooooooooooooooooooooooooooooooooooooooooooooooo-",
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
		};
	};

};