#pragma once

#include <vector>
#include <string>



class TileState
{
public:
	TileState();
	~TileState();

	std::string getState();
	void setState();

protected:

private:

	std::vector<std::string> m_states;
	std::string m_currentState;

};