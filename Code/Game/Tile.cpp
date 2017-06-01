#include "Tile.h"



Tile::Tile(float& _pos_x, float& _pos_y, float& _size_x, float& _size_y, int _row, int _col):
	tile_state(4), // 0-3 represent ownership, 4 = empty/clear
	row(_row),
	col(_col)
{
	m_pos_x = _pos_x;
	m_pos_y = _pos_y;

	m_size_x = _size_x;
	m_size_y = _size_y;
}



Tile::~Tile()
{

}



int Tile::getState()
{
	return tile_state;
}



void Tile::setState(int _newState)
{
	tile_state = _newState;
}



void Tile::resetTile()
{
	tile_state = 4;
}



bool Tile::getIgnore()
{
	return ignore;
}



void Tile::setIgnore(bool _status)
{
	ignore = _status;
}



int Tile::getRowNo() const
{
	return row;
}



int Tile::getColNo() const
{
	return col;
}