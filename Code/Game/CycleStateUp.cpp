#include "CycleStateUp.h"
#include "LightCycle.h"



CycleStateUp::CycleStateUp(float _game_size_x, float _game_size_y)
	: LightCycleState (_game_size_x, _game_size_y)
{

}



CycleStateUp::~CycleStateUp()
{

}



// Move Up...
void CycleStateUp::Tick(LightCycle* _light_cycle)
{
	_light_cycle->setPosY(_light_cycle->getPosY() -= game_size_y / 300);
}