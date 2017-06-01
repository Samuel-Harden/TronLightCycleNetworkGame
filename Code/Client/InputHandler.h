#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class GameManager;
class TronClient;

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	void checkKeyboard(std::unique_ptr<GameManager>& _game_manager,
		std::unique_ptr<TronClient>& _con_server);

	void checkJoyPad(std::unique_ptr<GameManager>& _game_manager,
		std::unique_ptr<TronClient>& _con_server);

	void checkJoyStick(std::unique_ptr<GameManager>& _game_manager, 
		std::unique_ptr<TronClient>& _con_server);

protected:

private:
	void prepareUpdate(std::unique_ptr<GameManager>& _game_manager,
		std::unique_ptr<TronClient>& _con_server);

	// Movement...
	void moveLeft(std::unique_ptr<GameManager>& _game_manager,
		std::unique_ptr<TronClient>& _con_server);

	void moveRight(std::unique_ptr<GameManager>& _game_manager,
		std::unique_ptr<TronClient>& _con_server);

	void moveUp(std::unique_ptr<GameManager>& _game_manager,
		std::unique_ptr<TronClient>& _con_server);

	void moveDown(std::unique_ptr<GameManager>& _game_manager,
		std::unique_ptr<TronClient>& _con_server);

	// Buttons/Actions...
	void actionButton(std::unique_ptr<TronClient>& _con_server);

	void backButton(std::unique_ptr<GameManager>& _game_manager,
		std::unique_ptr<TronClient>& _con_server);

	float axis_x;
	float axis_y;
};