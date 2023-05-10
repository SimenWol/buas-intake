#include "Obstacle.h"
#include "LevelManager.h"
#include "Player.h"

namespace Tmpl8
{
	// Function that calculates how to deflect the player.
	void Obstacle::Trigger(const Location& tile, Player& player)
	{
		Location loc = player.GetLoc();
		float radius = player.GetRadius();

		// Get Vec2 of distance between centers
		float offX = tile.x - loc.x;
		float offY = tile.y - loc.y;

		// Get new floats for calculations
		float offsetX = offX;
		float offsetY = offY;
		if (offsetX < 0) { offsetX += LevelManager::tileSize / 2 + radius; }
		else { offsetX -= LevelManager::tileSize / 2 + radius; }
		if (offsetY < 0) { offsetY += LevelManager::tileSize / 2 + radius; }
		else { offsetY -= LevelManager::tileSize / 2 + radius; }

		// Make everything positive for checks
		if (offX < 0) { offX = -offX; }
		if (offY < 0) { offY = -offY; }

		// Check how to deflect player.
		if (offY > offX) { player.DeflectY(offsetY); }
		else if (offX > offY) { player.DeflectX(offsetX); }

		/* ======================== DEBUG ======================== */
		// std::cout << offX << " " << offY << std::endl;
		// std::cout << "Obstacle called" << std::endl;
		/* ======================================================= */
	}
};