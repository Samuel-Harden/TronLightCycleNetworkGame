#pragma once

#include <SFML/Graphics.hpp>
#include <Game\TronGame.h>

#include <memory>
#include <vector>

class GameObject2D;
class TronGame;
class GameData;
class TronClient;

class GameState
{
public:
	friend class GameManager;
	virtual ~GameState();

protected:
	GameState(float& _screen_width, float& _screen_height);

	virtual void Tick(std::unique_ptr<TronGame> const& _tron_game,
		std::vector<GameObject2D*>& m_tron_bikes,
		std::vector<sf::RectangleShape>& _tiles, GameData* _GD,
		std::unique_ptr<TronClient>& _con_server);

	virtual void Draw(sf::RenderWindow* _window, std::vector<GameObject2D*> _GO,
		std::vector<sf::RectangleShape>& _tiles);

	float screen_width;
	float screen_height;

private:

};