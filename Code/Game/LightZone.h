#pragma once

#include <vector>
#include <list>

class Tile;
class LightCycle;

class LightZone
{
public:
	LightZone(float& _game_size_x, float& _game_size_y);
	~LightZone();

	void Tick(std::vector<LightCycle*> _light_cycles);
	bool checkCollision(LightCycle* _light_cycle);

	Tile* getTile(int _no);
	int getZoneSize() const;

protected:

private:

	void createGrid(float& _game_size_x, float& _game_size_y);

	std::vector<Tile*> m_grid;

	float row_size;
	float col_size;

	const int no_tiles = 2500;
};