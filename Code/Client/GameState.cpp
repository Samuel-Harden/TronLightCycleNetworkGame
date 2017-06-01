#include "GameState.h"

#include <Game\TronGame.h>
#include "GameData.h"
#include "TronClient.h"



GameState::GameState(float& _screen_width, float& _screen_height):
	  screen_width(_screen_width),
	screen_height(_screen_height)
{

}



GameState::~GameState()
{

}



void GameState::Tick(std::unique_ptr<TronGame> const& _tron_game,
	std::vector<GameObject2D*>& m_tron_bikes,
	std::vector<sf::RectangleShape>& _tiles,
	GameData* _GD, std::unique_ptr<TronClient>& _con_server)
{

}



void GameState::Draw(sf::RenderWindow* _window, std::vector<GameObject2D*> _GO,
	std::vector<sf::RectangleShape>& _tiles)
{

}