#include "TronGame.h"

#include <time.h>
#include "LightCycle.h"
#include "LightZone.h"
#include "Tile.h"



TronGame::TronGame(int _no_light_cycles, float& _game_width, float& _game_height):
	game_size_x(_game_width),
	game_size_y(_game_height)
{
	m_light_cycles.reserve(_no_light_cycles);

	// Seed the random number generator
	srand(time(NULL));

	// Create Light Zone...
	createLightZone( _game_width, _game_height);

	// Create Light Cycles
	createLightCycles(_no_light_cycles, _game_width, _game_height);
}



TronGame::~TronGame()
{
	
}



void TronGame::Tick()
{
	auto now = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - updated);

	if (elapsed.count() >= targetFPS)
	{
		for (int i = 0; i < m_light_cycles.size(); i++)
		{
			m_light_cycles[i]->Tick(game_size_x, game_size_y);
		}

		light_zone->Tick(m_light_cycles);

		updated = now;
	}
}



// Reset game State, can be used for initilisation too...
void TronGame::resetBikes()
{
	int a = 624;

	float x = light_zone->getTile(a)->getPosX() + (light_zone->getTile(a)->getSizeX() / 2);
	float y = light_zone->getTile(a)->getPosY() + (light_zone->getTile(a)->getSizeY() / 2);

	m_light_cycles[0]->setPosX(x);
	m_light_cycles[0]->setPosY(y);

	m_light_cycles[0]->setState(3);

	m_light_cycles[0]->setCurrentTile(624);
	m_light_cycles[0]->resetPreviousTile(0);
	light_zone->getTile(a)->setIgnore(true);

	m_light_cycles[0]->setMoving(true);

	int b = 1872;

	x = light_zone->getTile(b)->getPosX() + (light_zone->getTile(b)->getSizeX() / 2);
	y = light_zone->getTile(b)->getPosY() + (light_zone->getTile(b)->getSizeY() / 2);

	m_light_cycles[1]->setPosX(x);
	m_light_cycles[1]->setPosY(y);

	m_light_cycles[1]->setState(2);

	m_light_cycles[1]->setCurrentTile(1872);
	m_light_cycles[1]->resetPreviousTile(0);
	light_zone->getTile(b)->setIgnore(true);

	m_light_cycles[1]->setMoving(true);
}



void TronGame::resetTiles()
{
	//reset tiles
	for (int i = 0; i < light_zone->getZoneSize(); i++)
	{
		if (light_zone->getTile(i)->getState() != 4 && light_zone->getTile(i)->getState() != 5)
		{
			light_zone->getTile(i)->resetTile();
		}
	}
}



void TronGame::createLightZone(float& _game_width, float& _game_height)
{
	light_zone = std::make_unique<LightZone>(_game_width, _game_height);
}



void TronGame::createLightCycles(int& _no_light_cycles, float _game_width, float _game_height)
{
	for (int i = 0; i < _no_light_cycles; i++)
	{
		LightCycle* lightCycle = new LightCycle(_game_width, _game_height);
		m_light_cycles.push_back(lightCycle);
	}
	resetBikes();
}



LightCycle* TronGame::getLightCycle(int _no)
{
	return m_light_cycles[_no];
}



std::unique_ptr<LightZone>& TronGame::getLightZone()
{
	return light_zone;
}



std::vector<LightCycle*> TronGame::getLightCycles()
{
	return m_light_cycles;
}