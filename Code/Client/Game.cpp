#include "Game.h"

#include <SFML\Network.hpp>

#include <Game\TronGame.h>

#include <iostream>
#include <string>

#include "TronClient.h"

#include "InputHandler.h"

#include "enumStates.h"
#include "GameData.h"
#include "GameManager.h"



Game::Game() :
	screen_width(800),
	screen_height(800),
	update(true)
{
	m_window = new sf::RenderWindow(sf::VideoMode(screen_width, screen_height),
		"Tron Game v0.0565 Alpha Master");

	m_GD = new GameData();

	m_con_server = std::make_unique<TronClient>();
	m_input_handler = std::make_unique<InputHandler>();

	// needs to be moved, only gets created when game starts!
	m_tron_game = std::make_unique<TronGame>(2, screen_width, screen_height);

	m_game_manager = std::make_unique<GameManager>(font, screen_width,
		screen_height, m_tron_game);

	game_state = enumGameState::GS_MAIN_MENU;
}



Game::~Game()
{
	// Tidy stuff away...
	delete m_window;
	m_window = nullptr;

	delete m_GD;
	m_GD = nullptr;
}



void Game::run()
{
	m_window->setKeyRepeatEnabled(false);

	if (!font.loadFromFile("../../Resources/BAUHS93.TTF"))
	{
		return;
	}

	// initiate threads for connection and input
	m_loop_connection = std::thread(&Game::connection, this);

	m_input = std::thread(&Game::input, this);

	while (m_window->isOpen())
	{
		// Event Loop
		while (m_window->pollEvent(m_event))
		{
			// For controller input and linking it to active window...
			if (m_event.type == sf::Event::GainedFocus)
				update = true;

			if (m_event.type == sf::Event::LostFocus)
				update = false;

			// Check to exit game
			if (game_state == enumGameState::GS_EXIT)
				m_window->close();
		}

		m_game_manager->Tick(m_tron_game, m_GD, m_con_server);

		if (game_state == enumGameState::GS_GAME_OVER)
		{
			m_game_manager->setEndGameState();
			serGame_state = ServerGameStatus::SS_NULL;
		}

		if (game_state == enumGameState::GS_PLAY_GAME)
		{
			// check for tile update
			if (m_game_manager->checkTileUpdate(m_tron_game) == true)
			{
				// we have a tile update!
				m_game_manager->sendTileUpdate(m_con_server);
			}
		}

		// Draw
		m_window->clear();
		m_game_manager->Draw(m_window);
		m_window->display();
	}

	// Wait for threads to finish, and exit cleanly
	m_input.join();
	m_loop_connection.join();
}



// Thread 1
void Game::connection()
{
	m_con_server->client(m_GD);
}



// Thread 2
void Game::input()
{
	bool buttonDown = false;

	while (game_state != enumGameState::GS_EXIT)
	{
		if (update == true)
		{
			if (m_event.type == sf::Event::KeyPressed)
			{
				m_input_handler->checkKeyboard(m_game_manager, m_con_server);
			}

			if (m_event.type == sf::Event::JoystickButtonPressed 
				&& buttonDown != true)
			{
				m_input_handler->checkJoyPad(m_game_manager, m_con_server);
				buttonDown = true;
			}

			if (m_event.type == sf::Event::JoystickButtonReleased)
			{
				buttonDown = false;
			}

			if (m_event.type == sf::Event::JoystickMoved)
			{
				m_input_handler->checkJoyStick(m_game_manager, m_con_server);
			}
		}
	}
}