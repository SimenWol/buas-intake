#include "Obstacle.h"
#include "LevelManager.h"
#include "Player.h"

namespace Tmpl8
{
	void Obstacle::Trigger(const Location& tile, Player& player)
	{
		Location loc = player.GetLoc();
		float radius = player.GetRadius();

		float offX = tile.x - loc.x;
		float offY = tile.y - loc.y;

		float offsetX = offX;
		float offsetY = offY;
		if (offsetX < 0) { offsetX += LevelManager::tileSize / 2 + radius; }
		else { offsetX -= LevelManager::tileSize / 2 + radius; }
		if (offsetY < 0) { offsetY += LevelManager::tileSize / 2 + radius; }
		else { offsetY -= LevelManager::tileSize / 2 + radius; }

		if (offX < 0) { offX = -offX; }
		if (offY < 0) { offY = -offY; }

		/* ======================== DEBUG ======================== */
		// std::cout << offX << " " << offY << std::endl;
		// std::cout << "Obstacle called" << std::endl;
		/* ======================================================= */

		if (offY > offX) { player.DeflectY(offsetY); }
		else if (offX > offY) { player.DeflectX(offsetX); }
	}
};