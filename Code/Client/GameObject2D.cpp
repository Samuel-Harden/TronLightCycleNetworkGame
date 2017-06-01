#include "GameObject2D.h"



GameObject2D::GameObject2D(std::string _file_name):
	id(0)
{
	if (!m_texture.loadFromFile(_file_name))
	{
		// Error
	}
	m_sprite.setTexture(m_texture);

	m_sprite.setScale(0.25f, 0.25f);

	m_sprite.setOrigin(m_sprite.getTexture()->getSize().x * 0.5,
		m_sprite.getTexture()->getSize().y * 0.5);
}



GameObject2D::~GameObject2D()
{

}



void GameObject2D::Tick()
{

}



void GameObject2D::reset(int _x, int _y)
{
	m_sprite.setPosition(_x, _y);
}



void GameObject2D::setPos(float _posX, float _posY)
{
	m_sprite.setPosition(sf::Vector2f(_posX, _posY));
}




sf::Sprite& GameObject2D::getSprite()
{
	return m_sprite;
}



int GameObject2D::getState() const
{
	return state;
}



void GameObject2D::setState(int _state)
{
	state = _state;
}



int GameObject2D::getCurrentTile()
{
	return current_tile;
}



int GameObject2D::getPreviousTile()
{
	return previous_tile;
}



void GameObject2D::setCurrentTile(int _tile)
{
	previous_tile = current_tile;

	current_tile = _tile;
}



bool GameObject2D::getMoving()
{
	return moving;
}



void GameObject2D::setMoving(bool _moving)
{
	moving = _moving;
}