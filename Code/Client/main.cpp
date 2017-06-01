#include <memory>
#include <iostream>

#include "Game.h"



int main()
{
	// create game
	std::unique_ptr<Game> m_game;
	m_game = std::make_unique<Game>();

	// run game
	m_game->run();

	return 0;
}