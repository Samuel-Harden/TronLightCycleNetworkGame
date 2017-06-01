#include "PlayState.h"

#include <Game\TronGame.h>
#include <Game\LightZone.h>
#include <Game\LightCycle.h>
#include <Game\Tile.h>

#include "enumStates.h"
#include "GameObject2D.h"
#include "GameData.h"
#include "TronClient.h"



PlayState::PlayState(sf::Font& _font, float& _screen_width, float& _screen_height)
	:GameState(_screen_width, _screen_height)
{
	endgame = false;
	play.setString("PlayTime");
	play.setFont(_font);
}



PlayState::~PlayState()
{

}



void PlayState::Tick(std::unique_ptr<TronGame> const& _tron_game,
	std::vector<GameObject2D*>& m_tron_bikes,
	std::vector<sf::RectangleShape>& _tiles,
	GameData* _GD, std::unique_ptr<TronClient>& _con_server)
{
	// Updates...
	updatePlayer(_tron_game, m_tron_bikes);

	updateBikes(_tron_game, m_tron_bikes);

	updateTiles(_tron_game, _tiles);

	_tron_game->Tick();

	if(_tron_game->getLightZone()->checkCollision(_tron_game->getLightCycle(player_ID)) == true)
	{
		_tron_game->getLightCycle(player_ID)->setMoving(false);
		game_state = enumGameState::GS_GAME_OVER;
		endgame = true;
	}
}



void PlayState::Draw(sf::RenderWindow* _window, std::vector<GameObject2D*> _GO,
	std::vector<sf::RectangleShape>& _tiles)
{
	for (int i = 0; i < _tiles.size(); i++)
	{
		_window->draw(_tiles[i]);
	}

	for (int i = 0; i < _GO.size(); i++)
	{
		_window->draw(_GO[i]->getSprite());
	}

	_window->draw(play);
}



bool PlayState::checkSendTileUpdate(std::unique_ptr<TronGame> const& _tron_game,
	std::vector<GameObject2D*>& m_tronBikes)
{
	// check tron games tile against sprites
	if (_tron_game->getLightCycle(player_ID)->getCurrentTile()
		!= m_tronBikes[player_ID]->getCurrentTile())
	{
		// update sprites current tile and pos to match
		m_tronBikes[player_ID]->setCurrentTile(_tron_game->getLightCycle(player_ID)->getCurrentTile());
		m_tronBikes[player_ID]->setPos(_tron_game->getLightCycle(player_ID)->getPosX(),
			_tron_game->getLightCycle(player_ID)->getPosY());
		return true;
	}
	return false;
}



void PlayState::setPlayerID(int _ID)
{
	player_ID = _ID;
}


void PlayState::updatePlayer(std::unique_ptr<TronGame> const& _tron_game,
	std::vector<GameObject2D*>& m_tron_bikes)
{
	if (player_state == PlayerState::PS_RIGHT)
	{
		_tron_game->getLightCycle(player_ID)->setState(0);
		m_tron_bikes[player_ID]->getSprite().setRotation(180.0f);
	}

	if (player_state == PlayerState::PS_LEFT)
	{
		_tron_game->getLightCycle(player_ID)->setState(1);
		m_tron_bikes[player_ID]->getSprite().setRotation(0.0f);
	}

	if (player_state == PlayerState::PS_UP)
	{
		_tron_game->getLightCycle(player_ID)->setState(2);
		m_tron_bikes[player_ID]->getSprite().setRotation(90.0f);
	}

	if (player_state == PlayerState::PS_DOWN)
	{
		_tron_game->getLightCycle(player_ID)->setState(3);
		m_tron_bikes[player_ID]->getSprite().setRotation(270.0f);
	}
}



void PlayState::updateBikes(std::unique_ptr<TronGame> const& _tron_game,
	std::vector<GameObject2D*>& m_tron_bikes)
{
	// Update renderable game objects from TronGame...
	for (int i = 0; i < m_tron_bikes.size(); i++)
	{
		float x = _tron_game->getLightCycle(i)->getPosX();
		float y = _tron_game->getLightCycle(i)->getPosY();

		// set position
		m_tron_bikes[i]->setPos(x, y);

		// set current  tile
		m_tron_bikes[i]->setCurrentTile(_tron_game->getLightCycle(i)->getCurrentTile());

		// set moving
		m_tron_bikes[i]->setMoving(_tron_game->getLightCycle(i)->getMoving());

		if (_tron_game->getLightCycle(i)->getState() == 0)
		{
			m_tron_bikes[i]->getSprite().setRotation(180.0f);
		}

		if (_tron_game->getLightCycle(i)->getState() == 1)
		{
			m_tron_bikes[i]->getSprite().setRotation(0.0f);
		}

		if (_tron_game->getLightCycle(i)->getState() == 2)
		{
			m_tron_bikes[i]->getSprite().setRotation(90.0f);
		}

		if (_tron_game->getLightCycle(i)->getState() == 3)
		{
			m_tron_bikes[i]->getSprite().setRotation(270.0f);
		}
	}
}


void PlayState::updateTiles(std::unique_ptr<TronGame> const& _tron_game,
	std::vector<sf::RectangleShape>& _tiles)
{
	// update tiles
	for (int j = 0; j < _tiles.size(); j++)
	{
		if (_tron_game->getLightZone()->getTile(j)->getState() == 0)
		{
			_tiles[j].setFillColor(sf::Color::Yellow);
		}

		if (_tron_game->getLightZone()->getTile(j)->getState() == 1)
		{
			_tiles[j].setFillColor(sf::Color::Cyan);
		}
	}
}



bool PlayState::getEndGame() const
{
	return endgame;
}

void PlayState::setEndGame(bool _endGame)
{
	endgame = _endGame;
}