#include "GameManager.h"

#include <Game\TronGame.h>
#include <Game\LightZone.h>
#include <Game\LIghtCycle.h>
#include <Game\Tile.h>
#include <Game\GameObject.h>

#include "GameData.h"
#include "enumStates.h"
#include "GameState.h"
#include "SplashState.h"
#include "PlayState.h"
#include "EndGameState.h"
#include "TronClient.h"

#include "GameObject2D.h"



GameManager::GameManager(sf::Font& _font, float& _screen_width,
	float& _screen_height, std::unique_ptr<TronGame> const& _tron_game):
	game_size_x(_screen_width),
	game_size_y(_screen_height),
	opp_ID(0)
{
	m_light_bike_names.reserve(2);
	m_tron_bikes.reserve(2);

	// Create States...
	m_splash_state = new SplashState(_font, _screen_width, _screen_width);
	m_game_states.push_back(m_splash_state);

	m_play_state = new PlayState(_font, _screen_width, _screen_width);
	m_game_states.push_back(m_play_state);

	m_endgame_state = new EndGameState(_font, _screen_width, _screen_width);
	m_game_states.push_back(m_endgame_state);


	// Set initial state to Splash
	m_current_state = m_splash_state;

	createTiles(_tron_game);

	m_light_bike_names.push_back("../../Resources/LightCycleYellow.png");
	m_light_bike_names.push_back("../../Resources/LightCycleAqua.png");

	setGameObjects(_tron_game);
}



GameManager::~GameManager()
{
	// Delete GameStates...
	for (std::vector<GameState *>::iterator it = m_game_states.begin(); it != m_game_states.end(); it++)
	{
		delete (*it);
		(*it) = nullptr;
	}
	m_game_states.clear();

	// Delete TronBikes...
	for (std::vector<GameObject2D *>::iterator it = m_tron_bikes.begin(); it != m_tron_bikes.end(); it++)
	{
		delete (*it);
		(*it) = nullptr;
	}
	m_tron_bikes.clear();
}



void GameManager::Tick(std::unique_ptr<TronGame> const& _tron_game, GameData* _GD, std::unique_ptr<TronClient>& _con_server)
{
	if (game_state == enumGameState::GS_PLAY_GAME)
	{
		if (checkPlayState() == false)
		{
			setPlayState();
			player_ID = _GD->getBikeID();
			m_play_state->setPlayerID(player_ID);
			m_endgame_state->setPlayerID(player_ID);

			m_play_state->setEndGame(false);

			if (player_ID == 0)
			{
				player_state = PlayerState::PS_DOWN;
				opp_ID = 1;
			}

			if (player_ID == 1)
			{
				player_state = PlayerState::PS_UP;
				opp_ID = 0;
			}

			_tron_game->resetTiles();
			resetTiles(_tron_game);

			_tron_game->resetBikes();

			resetBikes(_tron_game); // sets local SPRITE bikes to match that of tronGame
		}
	}

	if (serUpdate == UpdateFromServer::END_GAME)
	{
		game_state = enumGameState::GS_GAME_OVER;
		serUpdate = UpdateFromServer::NO_UPDATE;
		m_endgame_state->setWinner(player_ID);
		return;
	}

	// do we have a new update?
	if (serUpdate == UpdateFromServer::UPDATE_AVAILABLE)
	{
		movementUpdate(_tron_game, _GD);
		//_tron_game->getLightZone()->getTile(_tron_game->getLightCycle(player_ID)->getCurrentTile())->setIgnore(true);
	}

	if (serUpdate == UpdateFromServer::TILE_UPDATE_AVAILABLE)
	{
		tilesUpdate(_tron_game, _GD);
		//_tron_game->getLightZone()->getTile(_tron_game->getLightCycle(player_ID)->getCurrentTile())->setIgnore(true);
	}

	m_current_state->Tick(_tron_game, m_tron_bikes, m_tiles, _GD, _con_server);

	if (m_current_state == m_play_state)
	{
		if (m_play_state->getEndGame() == true)
		{
			_con_server->sendEndGameMsg(opp_ID);
			m_endgame_state->setWinner(opp_ID);
		}
	}
}



void GameManager::Draw(sf::RenderWindow* _window)
{
	m_current_state->Draw(_window, m_tron_bikes, m_tiles);
}



GameState GameManager::getCurrentState()
{
	return*m_current_state;
}



bool GameManager::checkSplashState()
{
	if (m_current_state == m_splash_state)
	{
		return true;
	}
	else
		return false;
}



bool GameManager::checkPlayState()
{
	if (m_current_state == m_play_state)
	{
		return true;
	}
	else
		return false;
}



bool GameManager::checkEndGameState()
{
	if (m_current_state == m_endgame_state)
	{
		return true;
	}
	else
		return false;
}



void GameManager::setSplashState()
{
	m_current_state = m_splash_state;
}



void GameManager::setPlayState()
{
	m_current_state = m_play_state;
}



void GameManager::setEndGameState()
{

	m_current_state = m_endgame_state;
}



void GameManager::movementUpdate(std::unique_ptr<TronGame> const& _tron_game, GameData* _GD)
{
	_tron_game->getLightCycle(0)->setPosX(_GD->getBikePosX(0));
	_tron_game->getLightCycle(0)->setPosY(_GD->getBikePosY(0));
	_tron_game->getLightCycle(0)->setState(_GD->getBikeState(0));
	_tron_game->getLightCycle(0)->setCurrentTile(_GD->getBikeTilePos(0));
	_tron_game->getLightCycle(0)->setMoving(_GD->getBikeMoving(0));

	_tron_game->getLightCycle(1)->setPosX(_GD->getBikePosX(1));
	_tron_game->getLightCycle(1)->setPosY(_GD->getBikePosY(1));
	_tron_game->getLightCycle(1)->setState(_GD->getBikeState(1));
	_tron_game->getLightCycle(1)->setCurrentTile(_GD->getBikeTilePos(1));
	_tron_game->getLightCycle(1)->setMoving(_GD->getBikeMoving(1));

	serUpdate = UpdateFromServer::NO_UPDATE; // reset update status
}



void GameManager::tilesUpdate(std::unique_ptr<TronGame> const& _tron_game, GameData* _GD)
{
	_tron_game->getLightCycle(opp_ID)->setPosX(_GD->getBikePosX(opp_ID));
	_tron_game->getLightCycle(opp_ID)->setPosY(_GD->getBikePosY(opp_ID));
	_tron_game->getLightCycle(opp_ID)->setCurrentTile(_GD->getBikeTilePos(opp_ID));

	serUpdate = UpdateFromServer::NO_TILE_UPDATE; // reset update status
}



void GameManager::resetTiles(std::unique_ptr<TronGame> const& _tron_game)
{
	// Tiles... only need to reset the colour
	for (int i = 0; i < _tron_game->getLightZone()->getZoneSize(); i++)
	{
		if (_tron_game->getLightZone()->getTile(i)->getState() == 4)
		{
			m_tiles[i].setOutlineThickness(1.0f);
			m_tiles[i].setOutlineColor(sf::Color::White);
			m_tiles[i].setFillColor(sf::Color::Black);
		}

		if (_tron_game->getLightZone()->getTile(i)->getState() == 5)
		{
			if (player_ID == 0)
			{
				m_tiles[i].setOutlineThickness(3.0f);
				m_tiles[i].setFillColor(sf::Color::Yellow);
				m_tiles[i].setOutlineColor(sf::Color::Black);
			}

			if( player_ID == 1)
			{
				m_tiles[i].setOutlineThickness(3.0f);
				m_tiles[i].setFillColor(sf::Color::Cyan);
				m_tiles[i].setOutlineColor(sf::Color::Black);
			}
		}
	}
}



void GameManager::createTiles(std::unique_ptr<TronGame> const& _tron_game)
{
	// Tiles...
	for (int i = 0; i < _tron_game->getLightZone()->getZoneSize(); i++)
	{
		sf::RectangleShape tile;

		float x = _tron_game->getLightZone()->getTile(i)->getPosX();
		float y = _tron_game->getLightZone()->getTile(i)->getPosY();

		float sizeX = _tron_game->getLightZone()->getTile(i)->getSizeX();
		float sizeY = _tron_game->getLightZone()->getTile(i)->getSizeY();

		tile.setPosition(x, y);
		tile.setSize(sf::Vector2f(sizeX, sizeY));

		m_tiles.push_back(tile);
	}
	resetTiles(_tron_game);
}



void GameManager::resetBikes(std::unique_ptr<TronGame> const& _tron_game)
{
	// Reset Bikes...
	for (int i = 0; i < _tron_game->getLightCycles().size(); i++)
	{
		float x = _tron_game->getLightCycle(i)->getPosX();
		float y = _tron_game->getLightCycle(i)->getPosY();

		m_tron_bikes[i]->setPos(x, y);

		
		float dir = _tron_game->getLightCycle(i)->getState();

		if (dir == 0) // Right
		{
			m_tron_bikes[i]->getSprite().setRotation(180.0f);
			m_tron_bikes[i]->setState(0);
		}

		if (dir == 1) // Left
		{
			m_tron_bikes[i]->getSprite().setRotation(0.0f);
			m_tron_bikes[i]->setState(1);
		}

		if (dir == 2) // Up
		{
			m_tron_bikes[i]->getSprite().setRotation(90.0f);
			m_tron_bikes[i]->setState(2);
		}

		if (dir == 3) // Down
		{
			m_tron_bikes[i]->getSprite().setRotation(270.0f);
			m_tron_bikes[i]->setState(3);
		}
	}
}



void GameManager::setGameObjects(std::unique_ptr<TronGame> const& _tron_game)
{
	// Players...
	for (int i = 0; i < _tron_game->getLightCycles().size(); i++)
	{
		GameObject2D* bike = new GameObject2D(m_light_bike_names[i]);

		m_tron_bikes.push_back(bike);
	}
}



bool GameManager::checkTileUpdate(std::unique_ptr<TronGame> const& _tron_game)
{
	if (m_play_state->checkSendTileUpdate(_tron_game, m_tron_bikes) == true)
	{
		return true;
	}

	else 
		return false;
}



void GameManager::sendTileUpdate(std::unique_ptr<TronClient>& _con_server)
{
	// bike id, posx,posy, tileNo
	_con_server->sendTileUpdateMsg(player_ID,
		getBike(player_ID)->getSprite().getPosition().x,
		getBike(player_ID)->getSprite().getPosition().y,
		getBike(player_ID)->getCurrentTile());
}



GameObject2D* GameManager::getBike(int _bike)
{
	return m_tron_bikes[_bike];
}



int GameManager::getPlayerID() const
{
	return player_ID;
}



float GameManager::getGameSizeX() const
{
	return game_size_y;
}



float GameManager::getGameSizeY() const
{
	return game_size_y;
}