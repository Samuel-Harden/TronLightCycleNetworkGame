#include "GameData.h"



GameData::GameData():
	winner(0)
{
	bikes_pos_x.reserve(2);
	bikes_pos_y.reserve(2);
	bike_states.reserve(2);
	bike_tile_pos.reserve(2);
	bike_moving.reserve(2);

	int x = 0;

	bikes_pos_x.push_back(x);
	bikes_pos_x.push_back(x);

	bikes_pos_y.push_back(x);
	bikes_pos_y.push_back(x);

	bike_states.push_back(x);
	bike_states.push_back(x);

	bike_tile_pos.push_back(x);
	bike_tile_pos.push_back(x);

	bike_moving.push_back(true);
	bike_moving.push_back(true);
}



GameData::~GameData()
{

}



int GameData::getBikeID()
{
	return bikeID;
}



void GameData::setBikeID(int _ID)
{
	bikeID = _ID;
}



int GameData::getBikePosX(int _bike_no)
{
	return bikes_pos_x[_bike_no];
}



void GameData::setBikePosX(int _bike_no, float _pos_x)
{
	bikes_pos_x[_bike_no] = _pos_x;
}



int GameData::getBikePosY(int _bike_no)
{
	return bikes_pos_y[_bike_no];
}



void GameData::setBikePosY(int _bike_no, float _pos_y)
{
	bikes_pos_y[_bike_no] = _pos_y;
}



int GameData::getBikeState(int _bike_no)
{
	return bike_states[_bike_no];
}



void GameData::setBikeState(int _bike_no, int _state)
{
	bike_states[_bike_no] = _state;
}



int GameData::getBikeTilePos(int _bike_no)
{
	return bike_tile_pos[_bike_no];
}



void GameData::setBikeTilePos(int _bike_no, int _tile_pos)
{
	bike_tile_pos[_bike_no] = _tile_pos;
}



void GameData::setBikeMoving(int _bike_no, bool _moving)
{
	bike_moving[_bike_no] = _moving;
}



bool GameData::getBikeMoving(int _bike_no)
{
	return bike_moving[_bike_no];
}



int GameData::getWinner()
{
	return winner;
}



void GameData::setWinner(int _ID)
{
	winner = _ID;
}