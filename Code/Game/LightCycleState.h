#pragma once

class LightCycle;

class LightCycleState
{
public:
	friend class LightCycle;
	virtual ~LightCycleState();

	virtual void Tick(LightCycle* _light_cycle);

protected:
	LightCycleState(float _game_size_x, float _game_size_y);

	int game_size_x;
	int game_size_y;

private:

};