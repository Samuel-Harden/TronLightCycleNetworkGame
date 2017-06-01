#pragma once

#include "LightCycleState.h"

class LIghtCycle;

class CycleStateRight : public LightCycleState
{
public:
	friend class LightCycle;
	virtual ~CycleStateRight();

	void Tick(LightCycle* _light_cycle) override;

protected:
	CycleStateRight(float _game_size_x, float _game_size_y);

private:

};