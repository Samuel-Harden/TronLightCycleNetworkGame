#include "InputHandler.h"

#include <SFML/Window.hpp>
#include "enumStates.h"
#include "GameManager.h"
#include "GameObject2D.h"
#include "TronClient.h"



InputHandler::InputHandler():
	axis_x(0),
	axis_y(0)
{

}



InputHandler::~InputHandler()
{

}



void InputHandler::checkKeyboard(std::unique_ptr<GameManager>& _game_manager,
	std::unique_ptr<TronClient>& _con_server)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		actionButton(_con_server);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		backButton(_game_manager, _con_server);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moveLeft(_game_manager, _con_server);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveRight(_game_manager, _con_server);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		moveUp(_game_manager, _con_server);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		moveDown(_game_manager, _con_server);
	}
}



void InputHandler::checkJoyPad(std::unique_ptr<GameManager>& _game_manager,
	std::unique_ptr<TronClient>& _con_server)
{
	if (sf::Joystick::isButtonPressed(0, 0))
	{
		actionButton(_con_server);
	}

	if (sf::Joystick::isButtonPressed(0, 1))
	{
		backButton(_game_manager, _con_server);
	}
}



void InputHandler::checkJoyStick(std::unique_ptr<GameManager>& _game_manager,
	std::unique_ptr<TronClient>& _con_server)
{
	axis_x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
	axis_y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);

	if (axis_x < -90)
	{
		//call move left
		moveLeft(_game_manager, _con_server);
		return;
	}

	if (axis_x > 90)
	{
		//call move Right
		moveRight(_game_manager, _con_server);
		return;
	}

	if (axis_y < -90)
	{
		//call move Down
		moveUp(_game_manager, _con_server);
		return;
	}

	if (axis_y > 90)
	{
		//call move Up
		moveDown(_game_manager, _con_server);
		return;
	}
}



void InputHandler::moveLeft(std::unique_ptr<GameManager>& _game_manager,
	std::unique_ptr<TronClient>& _con_server)
{
	// Left
	if (game_state == enumGameState::GS_PLAY_GAME)
	{
		if (player_state != PlayerState::PS_RIGHT && player_state != PlayerState::PS_LEFT)
		{
			player_state = PlayerState::PS_LEFT;
			_game_manager->getBike(_game_manager->getPlayerID())->setState(1);
			prepareUpdate(_game_manager, _con_server);
		}
	}
}



void InputHandler::moveRight(std::unique_ptr<GameManager>& _game_manager,
	std::unique_ptr<TronClient>& _con_server)
{
	// Left
	if (game_state == enumGameState::GS_PLAY_GAME)
	{
		if (player_state != PlayerState::PS_LEFT && player_state != PlayerState::PS_RIGHT)
		{
			player_state = PlayerState::PS_RIGHT;
			_game_manager->getBike(_game_manager->getPlayerID())->setState(0);
			prepareUpdate(_game_manager, _con_server);
		}
	}
}



void InputHandler::moveDown(std::unique_ptr<GameManager>& _game_manager,
	std::unique_ptr<TronClient>& _con_server)
{
	// Down
	if (game_state == enumGameState::GS_PLAY_GAME)
	{
		if (player_state != PlayerState::PS_UP && player_state != PlayerState::PS_DOWN)
		{
			player_state = PlayerState::PS_DOWN;
			_game_manager->getBike(_game_manager->getPlayerID())->setState(3);
			prepareUpdate(_game_manager, _con_server);
		}
	}
}



void InputHandler::moveUp(std::unique_ptr<GameManager>& _game_manager,
	std::unique_ptr<TronClient>& _con_server)
{
	// Down
	if (game_state == enumGameState::GS_PLAY_GAME)
	{
		if (player_state != PlayerState::PS_DOWN && player_state != PlayerState::PS_UP)
		{
			player_state = PlayerState::PS_UP;
			_game_manager->getBike(_game_manager->getPlayerID())->setState(2);
			prepareUpdate(_game_manager, _con_server);
		}
	}
}



void InputHandler::actionButton(std::unique_ptr<TronClient>& _con_server)
{
	if (game_state == enumGameState::GS_MAIN_MENU)
	{
		if (serGame_state != ServerGameStatus::SS_AWAITING)
		{
			serGame_state = ServerGameStatus::SS_AWAITING;
			_con_server->sendAwaitingMsg();
		}
	}
}



void InputHandler::backButton(std::unique_ptr<GameManager>& _game_manager,
	std::unique_ptr<TronClient>& _con_server)
{
	if (game_state == enumGameState::GS_MAIN_MENU)
	{
		game_state = enumGameState::GS_EXIT;
	}

	if (game_state == enumGameState::GS_GAME_OVER)
	{
		game_state = enumGameState::GS_MAIN_MENU;
		_game_manager->setSplashState();
	}
}



void InputHandler::prepareUpdate(std::unique_ptr<GameManager>& _game_manager,
	std::unique_ptr<TronClient>& _con_server)
{
	_con_server->sendUpdateMsg(
		0,
		_game_manager->getBike(0)->getSprite().getPosition().x,
		_game_manager->getBike(0)->getSprite().getPosition().y,
		_game_manager->getBike(0)->getState(),
		_game_manager->getBike(0)->getCurrentTile(),
		1,
		_game_manager->getBike(1)->getSprite().getPosition().x,
		_game_manager->getBike(1)->getSprite().getPosition().y,
		_game_manager->getBike(1)->getState(),
		_game_manager->getBike(0)->getCurrentTile());
}