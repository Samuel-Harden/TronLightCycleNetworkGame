#include "CycleStateRight.h"
#include "LightCycle.h"



CycleStateRight::CycleStateRight(float _game_size_x, float _game_size_y)
	: LightCycleState (_game_size_x, _game_size_y)
{

}



CycleStateRight::~CycleStateRight()
{

}



// Move Right...
void CycleStateRight::Tick(LightCycle* _light_cycle)
{
	_light_cycle->setPosX(_light_cycle->getPosX() += game_size_x / 300);
}