#pragma once

#include "LightCycleState.h"

class LightCycle;

class CycleStateDown : public LightCycleState
{
public:
	friend class LightCycle;
	virtual ~CycleStateDown();

	void Tick(LightCycle* _light_cycle) override;

protected:
	CycleStateDown(float _game_size_x, float _game_size_y);

private:

};