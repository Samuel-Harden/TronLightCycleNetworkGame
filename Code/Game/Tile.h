#pragma once

#include "GameObject.h"
#include <string>



class Tile : public GameObject
{
public:
	Tile(float& _pos_x, float& _pos_y, float& _size_x, float& _size_y, int _row, int _col);
	virtual ~Tile();

	int getState();
	void setState(int _new_state);
	void resetTile();

	int getRowNo() const;
	int getColNo() const;

	void setIgnore(bool _status);
	bool getIgnore();

protected:

private:

	int row;
	int col;

	int tile_state;
	bool ignore;

};