#pragma once

#include <SFML/Graphics.hpp>

#include "GameState.h"

class TronGame;
class GameData;
class TronClient;



class EndGameState : public GameState
{
public:
	friend class GameManager;
	virtual ~EndGameState();

	void setPlayerID(int _ID);
	void setWinner(int _ID);

protected:
	EndGameState(sf::Font& _font, float& _screen_width, float& _screen_height);

	void Tick(std::unique_ptr<TronGame> const& _tron_game,
		std::vector<GameObject2D*>& m_tron_bikes,
		std::vector<sf::RectangleShape>& _tiles, GameData* _GD,
		std::unique_ptr<TronClient>& _con_server);

	void Draw(sf::RenderWindow* _window, std::vector<GameObject2D*> _GO,
		std::vector<sf::RectangleShape>& _tiles) override;

private:

	sf::RectangleShape tint;

	sf::Texture back_button_texture;
	sf::Sprite back_button_sprite;

	sf::Text end_game;
	sf::Text back_button_details;
	int player_ID;
};