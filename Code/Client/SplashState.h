#pragma once

class TronGame;
class GameData;
class TronClient;

#include "GameState.h"

class SplashState : public GameState
{
public:
	friend class GameManager;
	virtual ~SplashState();

protected:
	SplashState(sf::Font& _font, float& _screen_Width, float& _screen_Height);
	void Tick(std::unique_ptr<TronGame> const& _tron_game, std::vector<GameObject2D*>& m_tron_bikes, std::vector<sf::RectangleShape>& _tiles, GameData* _GD, std::unique_ptr<TronClient>& _con_server) override;
	void Draw(sf::RenderWindow* _window, std::vector<GameObject2D*> _GO, std::vector<sf::RectangleShape>& _tiles) override;

private:

	sf::Text menu;
	sf::Text search;
	sf::Text con;
	sf::Text find_game;
	sf::Text exit_game;

	sf::Texture lc_texture;
	sf::Sprite light_cycles;

	sf::Texture action_button_texture;
	sf::Sprite action_button_sprite;
	sf::Sprite action_button_sprite2;
	sf::Text action_button_details;

	sf::Texture back_button_texture;
	sf::Sprite back_button_sprite;
	sf::Sprite back_button_sprite2;
	sf::Text back_button_details;

	sf::Texture left_stick_texture;
	sf::Sprite left_stick_sprite;
	sf::Text left_stick_details;

	std::vector<sf::Sprite> splash_sprites;
	std::vector<sf::Text> splash_text;

};