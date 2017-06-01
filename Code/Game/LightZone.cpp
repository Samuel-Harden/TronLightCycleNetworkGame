#include "lightZone.h"

#include "Tile.h"
#include "LightCycle.h"



LightZone::LightZone(float& _game_size_x, float& _game_size_y):
	row_size(50),
	col_size(50)
{
	// create grid of tiles
	createGrid(_game_size_x, _game_size_y);
}



LightZone::~LightZone()
{
	for (std::vector<Tile*>::iterator it = m_grid.begin();
	it != m_grid.end(); it++)
	{
		delete (*it);
		(*it) = nullptr;
	}

	m_grid.clear();
}



void LightZone::createGrid(float& _game_size_x, float& _game_size_y)
{
	float x = 0; // posX
	float y = 0; // posY

	float sizeX = _game_size_x / row_size;
	float sizeY = _game_size_y / col_size;

	int row = 0;
	int col = 0;

	float counterX = 0;

	for (int i = 0; i < no_tiles; i++)
	{
		Tile* tile = new Tile(x, y, sizeX, sizeY, row, col);

		if (col == 0 || col == (col_size - 1) || row == 0 || row == (row_size - 1))
		{
			if (tile->getState() == 4)
			{
				tile->setState(5);
				tile->setIgnore(false);
			}
		}

		m_grid.push_back(tile);

		x += sizeX;
		counterX++;
		col++;

		if (counterX == 50)
		{
			counterX = 0;
			x = 0;
			y += sizeY;
			col = 0;
			row++;
		}
	}
}



void LightZone::Tick(std::vector<LightCycle*> _light_cycles)
{
	// loop trough each bike
	for (int i = 0; i < _light_cycles.size(); i++)
	{
		int x = _light_cycles[i]->getPosX();
		int y = _light_cycles[i]->getPosY();

		//check against each tile...
		for (int j = 0; j < m_grid.size(); j++)
		{
			// If this tile is where the bike is currently
			if (x >= (m_grid[j]->getPosX() + 0.1) &&
				x <= (m_grid[j]->getPosX() + 0.1) + (m_grid[j]->getSizeX() - 0.1) &&
				y >= (m_grid[j]->getPosY() + 0.1) &&
				y <= (m_grid[j]->getPosY() + 0.1) + (m_grid[j]->getSizeY() - 0.1))
			{
				// If the current tile pos of the bike isnt this tile, update it
				if (_light_cycles[i]->getCurrentTile() != j)
				{
					_light_cycles[i]->setCurrentTile(j);
				}

				// Snap position to align with the center of current tiles opp axis...
				if (_light_cycles[i]->getState() == 0 || _light_cycles[i]->getState() == 1)
				{
					_light_cycles[i]->setPosY(m_grid[j]->getPosY() + (m_grid[j]->getSizeY() / 2)); // sets previous to be the current
				}

				if (_light_cycles[i]->getState() == 2 || _light_cycles[i]->getState() == 3)
				{
					_light_cycles[i]->setPosX(m_grid[j]->getPosX() + (m_grid[j]->getSizeX() / 2)); // sets previous to be the current
				}

				// set as ignore if free...
				if (m_grid[j]->getState() == 4)
				{
					// set new tile to ignored! So player cant collide with it
					m_grid[j]->setIgnore(true);

					// remove previous tile that was being ignored
					m_grid[_light_cycles[i]->getPreviousTile()]->setIgnore(false);

					// Finally, set color to match cycle
					m_grid[j]->setState(i);
				}
			}
		}
	}
}




bool LightZone::checkCollision(LightCycle* _light_cycles)
{
	int x = _light_cycles->getPosX();
	int y = _light_cycles->getPosY();

	// loop through grid
	for (int j = 0; j < m_grid.size(); j++)
	{

		if (x >= (m_grid[j]->getPosX() + 0.1) &&
			x <= (m_grid[j]->getPosX() + 0.1) + (m_grid[j]->getSizeX() - 0.1) &&

			y >= (m_grid[j]->getPosY() + 0.1) &&
			y <= (m_grid[j]->getPosY() + 0.1) + (m_grid[j]->getSizeY() - 0.1))
		{
			// is the tile ok to check?
			if (m_grid[j]->getIgnore() == false)
			{	
				if (m_grid[j]->getState() != 4)
				{
					 return true; // COLLISION!
				}
			}
		}
	}
	//if no collision return false...
	return false;
}



Tile* LightZone::getTile(int _no)
{
	return m_grid[_no];
}



int LightZone::getZoneSize() const
{
	return no_tiles;
}