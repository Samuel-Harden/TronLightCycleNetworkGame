#pragma once

#include "LightCycleState.h"

class LightCycle;

class CycleStateLeft : public LightCycleState
{
public:
	friend class LightCycle;
	virtual ~CycleStateLeft();

	void Tick(LightCycle* _light_cycle) override;

protected:
	CycleStateLeft(float _game_size_x, float _game_size_y);

private:

};