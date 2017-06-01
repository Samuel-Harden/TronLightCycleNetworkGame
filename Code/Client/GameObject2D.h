#pragma once

#include <SFML\Graphics.hpp>
#include <string>

class GameObject2D
{
public:

	GameObject2D(std::string _file_name);
	virtual ~GameObject2D();

	void Tick();

	void reset(int _x, int _y);

	int getState() const;
	void setState(int _state);

	void setPos(float _posX, float _posY);

	int getCurrentTile();
	int getPreviousTile();
	void setCurrentTile(int _tile);

	bool getMoving();
	void setMoving(bool _moving);

	sf::Sprite& getSprite();


protected:
	sf::Sprite m_sprite;

private:
	sf::Texture m_texture;

	int state;
	int current_tile;
	int previous_tile;
	bool moving;

	int id;

};