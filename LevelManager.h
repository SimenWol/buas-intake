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
	public:
		// Constructor //
		LevelManager();

		// Main Functions //
		void LoadLevel(const int level, Player& player, Timer& timer);
		void DrawLevel(Surface* screen, const Location& drawOffset);
		void UpdateAnimations(const float& deltaTime);
		void CallTrigger(const TileContents& content, const Location& tile, Player& player, class MenuManager& menu);
		void Death(Player& player, class MenuManager& menu);

		// Getters //
		LevelState GetLevelState(const int level) const { return state[level - 1]; }
		TileContents GetContents(const Location& loc) const;
		TileContents GetContents(const int x, const int y) const;
		int GetCurrentLevel() const { return currentLevel; }
		bool GetIsDead() const { return isDead; }

		// Setters //
		void SetLevelState(const int level, const LevelState state_in) { state[level - 1] = state_in; }
	private:
		// Main (private) Functions
		void DrawTile(Surface* screen, const Location& loc, const Location& tile);
		void Reset(Player& player);
	public:
		static constexpr int tileSize = 48; // Width & Height for each tile
		static constexpr int numLevels = 3; // Total amount of levels
	private:
		int currentLevel = 0;
		LevelState state[numLevels] = { LevelState::Closed }; // Using an array to store level states. Defaults to closed.

		bool isDead = false; // Used for animation detection

		Obstacle obstacle;
		Water water;
		WoodStakes woodstakes;
		Spikes spikes;
		Finish* finish;

		Sprite arrowSign;
		Surface tiles;

	private: // LEVEL STORAGE //

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
		const float time2 = 12.0f;

		const char levelTwo[11][111] =
		{
			"--------------------------------------------------------------------------------------------------------------",
			"--------------------------------------------------------------------------------------------------------------",
			"--------------------------------------------------------------------------------------------------------------",
			"--------------------idjdkd------------------------------------------------------------------------------------",
			"----------------------------------------------------idjdjdkd--------------------------------------------------",
			"----------------------------------------------idkd------------------------------------------------------------",
			"----------------------------------idkd------------------------------------------------------------------------",
			"--------------------------------------------------------------------------------------------------------------",
			"--------------------------------------------------------------------------------------------------------------",
			"--------------------------------------------------------------------------------------------------------------",
			"--------------------------------------------------------------------------cbfb------ib--------ib--------------",
		};
		const char levelTwoColl[11][56] =
		{
			"-ooooooooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-ooooooooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-ooooooooooAoooooooooooooooooooooooooooooooooooooooooo-",
			"-ooooooooo---oooooooooooooccoooooooooooooooooooooooooo-",
			"-ooooooooooooooooooooooooo----oooooooooooooooooooooooo-",
			"-oooooooooooooooooooooo--ooooooooooooooooooooooooooooo-",
			"-oooooooooooooooo--ooooooooooooooooooooooooooooooooooo-",
			"-ooooooooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-ooooooooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-ooooooooooooooooooooooooooooooooooooooooooooooFoooooo-",
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWwwWWWwWWWWwWWWWWWW",
		};

		// LEVEL 3 //
		const Location startLoc3 = { 528.0f, 48.0f };
		const float time3 = 12.0f;

		// CAVE

		const char levelThree[11][111] =
		{
			"--------------------------------------------------------------------------------------------------------------",
			"--------------------------------------------------------------------------------------------------------------",
			"--------------------------------------------------------------------------------------------------------------",
			"--------------------idjdkd------------------------------------------------------------------------------------",
			"----------------------------------------------------idjdjdkd--------------------------------------------------",
			"----------------------------------------------idkd------------------------------------------------------------",
			"----------------------------------idkd------------------------------------------------------------------------",
			"--------------------------------------------------------------------------------------------------------------",
			"--------------------------------------------------------------------------------------------------------------",
			"--------------------------------------------------------------------------------------------------------------",
			"--------------------------------------------------------------------------cbfb------ib--------ib--------------",
		};
		const char levelThreeColl[11][56] =
		{
			"-ooooooooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-ooooooooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-ooooooooooAoooooooooooooooooooooooooooooooooooooooooo-",
			"-ooooooooo---oooooooooooooccoooooooooooooooooooooooooo-",
			"-ooooooooooooooooooooooooo----oooooooooooooooooooooooo-",
			"-oooooooooooooooooooooo--ooooooooooooooooooooooooooooo-",
			"-oooooooooooooooo--ooooooooooooooooooooooooooooooooooo-",
			"-ooooooooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-ooooooooooooooooooooooooooooooooooooooooooooooooooooo-",
			"-ooooooooooooooooooooooooooooooooooooooooooooooFoooooo-",
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWwwWWWwWWWWwWWWWWWW",
		};
	};

};