#pragma once

#include <string>

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	float& getPosX();
	float& getPosY();
	void setPosX(float _pos_x);
	void setPosY(float _pos_y);

	int getID() const;
	void setID(int& _ID);

	float getSizeX() const;
	float getSizeY() const;

protected:

	// position, where is it...
	float m_pos_x;
	float m_pos_y;

	// Size, used for checking collisions...
	float m_size_x;
	float m_size_y;

	int m_id;

private:

};