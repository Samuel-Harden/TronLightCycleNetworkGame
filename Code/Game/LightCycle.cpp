#include "LightCycle.h"
#include "LightCycleState.h"
#include "CycleStateUp.h"
#include "CycleStateDown.h"
#include "CycleStateLeft.h"
#include "CycleStateRight.h"



LightCycle::LightCycle(float _game_size_x, float _game_size_y) :
	cycle_state(4), // 4 represents Idle 0-3 right,left,up,down
	moveable(true)
{
	createStates(_game_size_x, _game_size_y);
}



LightCycle::~LightCycle()
{
	// Delete states and Clear container...
	for (std::vector<LightCycleState*>::iterator it = m_cycle_states.begin();
	it != m_cycle_states.end(); it++)
	{
		delete (*it);
	}
	m_cycle_states.clear();
}



void LightCycle::Tick(float& _game_size_x, float& _game_size_y)
{
	if (moveable == true)
	{
		m_current_state->Tick(this);
	}
}



void LightCycle::createStates(float _game_size_x, float _game_size_y)
{
	m_current_state = new LightCycleState(_game_size_x, _game_size_y); // Current
	m_cycle_states.push_back(m_current_state);

	state_up = new CycleStateUp(_game_size_x, _game_size_y); // Up
	m_cycle_states.push_back(state_up);

	state_down = new CycleStateDown(_game_size_x, _game_size_y); // Down
	m_cycle_states.push_back(state_down);

	state_left = new CycleStateLeft(_game_size_x, _game_size_y); // Left
	m_cycle_states.push_back(state_left);

	state_right = new CycleStateRight(_game_size_x, _game_size_y); // Right
	m_cycle_states.push_back(state_right);
}



int& LightCycle::getState()
{
	return cycle_state;
}



void LightCycle::setState(int _newState)
{
	cycle_state = _newState;

	if (cycle_state == 0) // right
	{
		m_current_state = state_right;
	}
	if (cycle_state == 1) // left
	{
		m_current_state = state_left;
	}
	if (cycle_state == 2) // up
	{
		m_current_state = state_up;
	}
	if (cycle_state == 3) // down
	{
		m_current_state = state_down;
	}
}



void LightCycle::resetCycle()
{
	cycle_state = 4;
}



int& LightCycle::getCurrentTile()
{
	return current_tile;
}



int& LightCycle::getPreviousTile()
{
	return previous_tile;
}



void LightCycle::setCurrentTile(int _tile)
{
	// set previous tile
	previous_tile = current_tile;

	// set the new tile
	current_tile = _tile;
}


// needs to be called before setting the current tile...
void LightCycle::resetPreviousTile(int _tile)
{
	previous_tile = _tile;
}



bool LightCycle::getMoving()
{
	return moveable;
}



void LightCycle::setMoving(bool _moving)
{
	moveable = _moving;
}