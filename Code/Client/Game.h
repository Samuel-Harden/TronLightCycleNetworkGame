#pragma once

#include <SFML\Graphics.hpp>

#include <thread>
#include <memory>

class GameData;
class InputHandler;
class TronClient;
class TronGame;
class AssetManager;
class GameManager;

class Game
{
public:
	Game();
	~Game();

	void run();

protected:

private:

	void connection();
	void input();

	sf::Font font;
	sf::Event m_event;
	sf::RenderWindow* m_window;

	// Connection to Server
	std::unique_ptr<TronClient> m_con_server;

	// Inputs
	std::unique_ptr<InputHandler> m_input_handler;

	// Handles local renderables
	std::unique_ptr<GameManager> m_game_manager;

	// The Actual Tron Game!
	std::unique_ptr<TronGame> m_tron_game;

	// Threads
	std::thread m_loop_connection;
	std::thread m_input;

	GameData* m_GD;

	float screen_width;
	float screen_height;

	bool update;
};