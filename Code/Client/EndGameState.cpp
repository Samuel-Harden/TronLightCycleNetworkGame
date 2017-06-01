#include "EndGameState.h"

#include "enumStates.h"
#include "GameObject2D.h"
#include "GameData.h"



EndGameState::EndGameState(sf::Font& _font, float& _screen_width, float&
	_screen_height) :GameState(_screen_width, _screen_height)
{
	end_game.setFont(_font);
	end_game.setCharacterSize(120);
	end_game.setPosition(_screen_width / 3, _screen_height / 3);

	back_button_details.setString("Return to Menu");
	back_button_details.setFont(_font);
	back_button_details.setCharacterSize(40);
	back_button_details.setPosition((_screen_width / 10 * 1.5),
		(_screen_height / 10 * 9));

	tint.setSize(sf::Vector2f(_screen_width, _screen_height));
	tint.setFillColor(sf::Color(0, 0, 0, 128));

	back_button_texture.loadFromFile("../../Resources/BButton.png");

	back_button_sprite.setTexture(back_button_texture);
	back_button_sprite.setPosition((_screen_width / 10 * 0.5),
		_screen_height / 10 * 9);
	back_button_sprite.setScale(0.5f, 0.5f);
}



EndGameState::~EndGameState()
{

}



void EndGameState::Tick(std::unique_ptr<TronGame> const& _tron_game,
	std::vector<GameObject2D*>& m_tron_bikes,
	std::vector<sf::RectangleShape>& _tiles,
	GameData* _GD, std::unique_ptr<TronClient>& _con_server)
{

}



void EndGameState::Draw(sf::RenderWindow* _window, std::vector<GameObject2D*> _GO,
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

	_window->draw(tint);

	_window->draw(end_game);

	_window->draw(back_button_sprite);

	_window->draw(back_button_details);
}


void EndGameState::setPlayerID(int _ID)
{
	player_ID = _ID;
}



void EndGameState::setWinner(int _ID)
{
	if (_ID == player_ID)
		end_game.setString("Won");

	else
		end_game.setString("Lost");
}