#pragma once

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
	private:
	public:
		// void LoadLevel(const int level) const;		// TODO: Check LDTK implementation
		// void DrawLevel(const int level) const;
		LevelState GetLevelState(const int level) const;
	private:
		// int currentLevel = 0;

		// Using an array to store level states. Defaults to closed.
		static constexpr int numLevels = 1;
		LevelState state[numLevels] = { LevelState::Closed };
	};

};