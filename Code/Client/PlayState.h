#pragma once

class TronGame;
class GameData;
class TronClient;

#include "GameState.h"

class PlayState : public GameState
{
public:
	friend class GameManager;
	virtual ~PlayState();

	void setPlayerID(int _ID);

	bool checkSendTileUpdate(std::unique_ptr<TronGame> const& _tron_game,
		std::vector<GameObject2D*>& m_tron_bikes);

	bool getEndGame() const;
	void setEndGame(bool _endgame);

protected:
	PlayState(sf::Font& _font, float& _screen_width, float& _screen_height);

	void Tick(std::unique_ptr<TronGame> const& _tron_game,
		std::vector<GameObject2D*>& m_tron_bikes,
		std::vector<sf::RectangleShape>& _tiles, GameData* _GD,
		std::unique_ptr<TronClient>& _con_server);

	void Draw(sf::RenderWindow* _window, std::vector<GameObject2D*> _GO,
		std::vector<sf::RectangleShape>& _tiles) override;

private:

	void updatePlayer(std::unique_ptr<TronGame> const& _tron_game,
		std::vector<GameObject2D*>& m_tron_bikes);

	void updateBikes(std::unique_ptr<TronGame> const& _tron_game,
		std::vector<GameObject2D*>& m_tron_bikes);

	void updateTiles(std::unique_ptr<TronGame> const& _tron_game,
		std::vector<sf::RectangleShape>& _tiles);

	sf::Text play;
	int player_ID;
	bool endgame;
};