#include "SplashState.h"

#include <Game\TronGame.h>

#include "enumStates.h"
#include "GameObject2D.h"
#include "GameState.h"
#include "TronClient.h"



SplashState::SplashState(sf::Font& _font, float& _screen_Width, float& _screen_Height)
	:GameState( _screen_Width, _screen_Height)
{
	menu.setString("Tron");
	menu.setFont(_font);
	menu.setCharacterSize(50);
	menu.setPosition(_screen_Width / 4 * 0.2, _screen_Height / 4 * 0.2);
	splash_text.push_back(menu);

	con.setString("Connected");
	con.setFont(_font);
	con.setPosition((_screen_Width / 4 * 3.1), (_screen_Height / 4 * 3));

	search.setString("Searching for game...");
	search.setFont(_font);
	search.setPosition((_screen_Width / 4 * 1.5), (_screen_Height / 4 * 3.15));
	search.setCharacterSize(50);

	left_stick_details.setString("Move LightCycle");
	left_stick_details.setFont(_font);
	left_stick_details.setPosition((_screen_Width / 4 * 0.5),
		(_screen_Height / 4 * 0.8));
	splash_text.push_back(left_stick_details);

	action_button_details.setString("Action Button");
	action_button_details.setFont(_font);
	action_button_details.setPosition((_screen_Width / 4 * 0.5),
		(_screen_Height / 4 * 1.2));
	splash_text.push_back(action_button_details);

	back_button_details.setString("Back Button");
	back_button_details.setFont(_font);
	back_button_details.setPosition((_screen_Width / 4 * 0.5),
		(_screen_Height / 4 * 1.6));
	splash_text.push_back(back_button_details);

	find_game.setString("Find Game");
	find_game.setFont(_font);
	find_game.setPosition((_screen_Width / 4 * 0.5), (_screen_Height / 4 * 3.69));
	splash_text.push_back(find_game);

	exit_game.setString("Exit Game");
	exit_game.setFont(_font);
	exit_game.setPosition((_screen_Width / 4 * 2.7), (_screen_Height / 4 * 3.69));
	splash_text.push_back(exit_game);

	lc_texture.loadFromFile("../../Resources/TronSplash.png");
	action_button_texture.loadFromFile("../../Resources/AButton.png");
	back_button_texture.loadFromFile("../../Resources/BButton.png");
	left_stick_texture.loadFromFile("../../Resources/LeftStick.png");

	light_cycles.setTexture(lc_texture);
	light_cycles.setOrigin(lc_texture.getSize().x, lc_texture.getSize().y);
	light_cycles.setPosition(_screen_Width, _screen_Height);
	splash_sprites.push_back(light_cycles);

	left_stick_sprite.setTexture(left_stick_texture);
	left_stick_sprite.setPosition((_screen_Width / 10 * 0.5),
		_screen_Height / 10 * 2);
	left_stick_sprite.setScale(0.4f, 0.4f);
	splash_sprites.push_back(left_stick_sprite);

	action_button_sprite.setTexture(action_button_texture);
	action_button_sprite.setPosition((_screen_Width / 10 * 0.5),
		_screen_Height / 10 * 3);
	action_button_sprite.setScale(0.4f, 0.4f);
	splash_sprites.push_back(action_button_sprite);

	back_button_sprite.setTexture(back_button_texture);
	back_button_sprite.setPosition((_screen_Width / 10 * 0.5),
		_screen_Height / 10 * 4);
	back_button_sprite.setScale(0.4f, 0.4f);
	splash_sprites.push_back(back_button_sprite);

	action_button_sprite2 = action_button_sprite;
	back_button_sprite2 = back_button_sprite;

	action_button_sprite2.setPosition((_screen_Width / 10 * 0.5),
		_screen_Height / 10 * 9.2);
	action_button_sprite2.setScale(0.4f, 0.4f);
	splash_sprites.push_back(action_button_sprite2);

	back_button_sprite2.setPosition((_screen_Width / 10 * 6),
		_screen_Height / 10 * 9.2);
	back_button_sprite2.setScale(0.4f, 0.4f);
	splash_sprites.push_back(back_button_sprite2);


}



SplashState::~SplashState()
{
	
}



void SplashState::Tick(std::unique_ptr<TronGame> const& _tron_game,
	std::vector<GameObject2D*>& m_tron_bikes,
	std::vector<sf::RectangleShape>& _tiles, GameData* _GD,
	std::unique_ptr<TronClient>& _con_server)
{
	
}



void SplashState::Draw(sf::RenderWindow* _window,
	std::vector<GameObject2D*> _GO, std::vector<sf::RectangleShape>& _tiles)
{
	for (int i = 0; i < splash_sprites.size(); i++)
	{
		_window->draw(splash_sprites[i]);
	}

	if (con_state == ConnectionState::CS_CONNECTED)
	{
		_window->draw(con);
	}

	if (serGame_state == ServerGameStatus::SS_AWAITING)
	{
		_window->draw(search);
	}

	for (int i = 0; i < splash_text.size(); i++)
	{
		_window->draw(splash_text[i]);
	}
}