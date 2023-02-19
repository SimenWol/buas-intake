#pragma once

class LevelManager
{
public:
	enum LevelState
	{
		Closed,
		Open,
		Completed
	};
public:
	// GetLevelContents/LoadLevel --> Gets tilemap of specified level
	LevelState GetLevelState(const int level) const;
private:
	// Using an array to store level states. Defaults to closed.
	static constexpr int numLevels = 1;
	LevelState state[numLevels] = { LevelState::Closed };
};