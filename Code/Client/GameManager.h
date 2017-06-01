#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

class GameState;
class SplashState;
class PlayState;
class EndGameState;
class InputHandler;
class GameObject2D;
class TronGame;
class GameData;
class TronClient;

class GameManager
{
public:
	GameManager(sf::Font& _font, float& _screen_width, float& _screen_height, std::unique_ptr<TronGame> const& _tron_game);
	~GameManager();

	void Tick(std::unique_ptr<TronGame> const& _tron_game, GameData* _GD, std::unique_ptr<TronClient>& _con_server);
	void Draw(sf::RenderWindow* _window);

	GameObject2D* getBike(int _bike);

	void setSplashState();
	void setPlayState();
	void setEndGameState();

	bool checkSplashState();
	bool checkPlayState();
	bool checkEndGameState();

	float getGameSizeX() const;
	float getGameSizeY() const;

	int getPlayerID() const;

	GameState getCurrentState();

	bool checkTileUpdate(std::unique_ptr<TronGame> const& _tron_game);

	void sendTileUpdate(std::unique_ptr<TronClient>& _con_server);

	void resetBikes(std::unique_ptr<TronGame> const& _tron_game);
	void resetTiles(std::unique_ptr<TronGame> const& _tron_game);

protected:

private:

	void setGameObjects(std::unique_ptr<TronGame> const& _tron_game);
	void createTiles(std::unique_ptr<TronGame> const& _tron_game);

	void movementUpdate(std::unique_ptr<TronGame> const& _tron_game, GameData* _GD);
	void tilesUpdate(std::unique_ptr<TronGame> const& _tron_game, GameData* _GD);

	float game_size_x;
	float game_size_y;

	GameState* m_current_state;
	SplashState* m_splash_state;
	PlayState* m_play_state;
	EndGameState* m_endgame_state;

	std::vector<std::string> m_light_bike_names; // Names for different coloured Bikes

	std::vector<GameState*> m_game_states; // states
	std::vector<sf::RectangleShape> m_tiles; // Renderables
	std::vector<GameObject2D*> m_tron_bikes; // Renderables

	int player_ID;
	int opp_ID;
};