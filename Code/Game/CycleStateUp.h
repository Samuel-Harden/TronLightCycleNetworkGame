#pragma once

#include "LightCycleState.h"

class LightCycle;

class CycleStateUp : public LightCycleState
{
public:
	friend class LightCycle;
	virtual ~CycleStateUp();

	void Tick(LightCycle* _light_cycle) override;

protected:
	CycleStateUp(float _game_size_x, float _game_size_y);

private:

};