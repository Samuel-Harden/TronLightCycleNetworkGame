#include "CycleStateDown.h"
#include "LightCycle.h"



CycleStateDown::CycleStateDown(float _game_size_x, float _game_size_y)
	: LightCycleState (_game_size_x, _game_size_y)
{

}



CycleStateDown::~CycleStateDown()
{

}



// Move Down...
void CycleStateDown::Tick(LightCycle* _light_cycle)
{
	_light_cycle->setPosY(_light_cycle->getPosY() += game_size_y / 300);
}