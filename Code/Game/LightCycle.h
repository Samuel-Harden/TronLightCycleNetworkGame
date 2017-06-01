#pragma once

#include "GameObject.h"
#include <vector>

class LightCycleState;
class CycleStateUp;
class CycleStateDown;
class CycleStateLeft;
class CycleStateRight;

class LightCycle : public GameObject
{
public:
	LightCycle(float _game_size_x, float _game_size_y);
	virtual ~LightCycle();

	void Tick(float& _game_size_x, float& _game_size_y);
	int& getState();

	void setState(int _new_state);
	void resetCycle();

	int& getCurrentTile();
	int& getPreviousTile();

	void setCurrentTile(int _tile);
	void resetPreviousTile(int _tile);

	bool getMoving();
	void setMoving(bool _moving);

protected:

private:
	void createStates(float _game_size_x, float _game_size_y);

	// Direction/Heading...
	int cycle_state;
	int current_tile;
	int previous_tile;

	bool moveable; 

	std::vector<LightCycleState*> m_cycle_states;
	// States...
	LightCycleState*  m_current_state;
	CycleStateUp*     state_up;
	CycleStateDown*   state_down;
	CycleStateLeft*   state_left;
	CycleStateRight*  state_right;
};