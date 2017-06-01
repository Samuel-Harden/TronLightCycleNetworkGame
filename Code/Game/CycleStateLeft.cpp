#include "CycleStateLeft.h"
#include "LightCycle.h"



CycleStateLeft::CycleStateLeft(float _game_size_x, float _game_size_y)
	: LightCycleState (_game_size_x, _game_size_y)
{

}



CycleStateLeft::~CycleStateLeft()
{

}



// Move Left...
void CycleStateLeft::Tick(LightCycle* _light_cycle)
{
	_light_cycle->setPosX(_light_cycle->getPosX() -= game_size_x / 300);
}