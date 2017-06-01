#include "GameObject.h"



GameObject::GameObject()
{

}



GameObject::~GameObject()
{

}



float& GameObject::getPosX()
{
	return m_pos_x;
}



float& GameObject::getPosY()
{
	return m_pos_y;
}



void GameObject::setPosX(float _pos_x)
{
	m_pos_x = _pos_x;
}



void GameObject::setPosY(float _pos_y)
{
	m_pos_y = _pos_y;
}



float GameObject::getSizeX() const
{
	return m_size_x;
}



float GameObject::getSizeY() const
{
	return m_size_y;
}


int GameObject::getID() const
{
	return m_id;
}



void GameObject::setID(int& _ID)
{

}