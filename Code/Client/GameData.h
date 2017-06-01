#pragma once

#include <vector>

class GameData
{
public:
	GameData();
	~GameData();

	int getBikeID();
	void setBikeID(int _ID);

	int getBikePosX(int _bike_no);
	void setBikePosX(int _bike_no, float _pos_x);

	int getBikePosY(int _bike_no);
	void setBikePosY(int _bike_no, float _pos_y);

	int getBikeState(int _bike_no);
	void setBikeState(int _bike_no, int _state);

	int getBikeTilePos(int _bike_no);
	void setBikeTilePos(int _bike_no, int _tile_pos);

	void setBikeMoving(int _bike_no, bool _moving);
	bool getBikeMoving(int _bike_no);

	int getWinner();
	void setWinner(int _ID);

protected:

private:

	int bikeID;       // The Players Bike ID
	int winner;

	std::vector<float> bikes_pos_x; // Variables for all bikes X positions
	std::vector<float> bikes_pos_y; // Variables for all bikes X positions
	std::vector<int> bike_states;  // States for the bikes (ie their direction)
	std::vector<int> bike_tile_pos; // tile positions that the bike are currently on
	std::vector<bool> bike_moving;
};