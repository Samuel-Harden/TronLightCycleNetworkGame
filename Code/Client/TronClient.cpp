#include "TronClient.h"

#include <future>
#include <iostream>
#include <string>

#include "MessageTypes.h"
#include "enumStates.h"
#include "GameData.h"



TronClient::TronClient()
{

}



TronClient::~TronClient()
{

}



bool TronClient::connect()
{
	auto status = socket.connect(SERVER_IP, SERVER_TCP_PORT);
	if (status != sf::Socket::Done)
	{
		return false;
	}

	std::cout << "Connected to server: " << SERVER_IP << std::endl;
	socket.setBlocking(false);
	return true;
}



void TronClient::client(GameData* _GD)
{
	if (!connect())
	{
		return;
	}

	auto handle = std::async(std::launch::async, [&]
	{
		do
		{
			sf::Packet packet;
			status = socket.receive(packet);
			if (status == sf::Socket::Done)
			{
				int header = 0;
				packet >> header;

				NetMsg msg = static_cast<NetMsg>(header);
				if (msg == NetMsg::UPDATE)
				{
					handleUpdate(packet, _GD);
				}
				if (msg == NetMsg::TILEUPDATE)
				{
					handleTileUpdate(packet, _GD);
				}
				if (msg == NetMsg::ENDGAME)
				{
					handleEndGame(packet, _GD);
				}
				else if (msg == NetMsg::PING)
				{
					pong();
					sf::Packet pong;
					pong << NetMsg::PONG;
					socket.send(pong);

					timestamp = std::chrono::steady_clock::now();
				}
				else if (msg == NetMsg::CONFIRM_CONNECTION)
				{
					con_state = ConnectionState::CS_CONNECTED;
				}
				else if (msg == NetMsg::LAUNCH_GAME)
				{
					startupSettings(packet, _GD);
				}
			}

			if (game_state == enumGameState::GS_EXIT)
			{
				status = sf::Socket::Disconnected;
			}

		} while (status != sf::Socket::Disconnected);
	});
}



void TronClient::sendAwaitingMsg()
{
	sf::Packet awaiting;
	awaiting << NetMsg::AWAITING;
	socket.send(awaiting);
}



void TronClient::sendUpdateMsg(sf::Uint32 _ID_0, float _pos_x_0, float _pos_y_0,
	sf::Uint32 _state_0, sf::Uint32 _current_tile_0,
	sf::Uint32 _ID_1, float _pos_x_1, float _pos_y_1,
	sf::Uint32 _state_1, sf::Uint32 _current_tile_1)
{
	sf::Packet packet;

	packet << NetMsg::UPDATE << _ID_0 << _pos_x_0 << _pos_y_0 <<
		_state_0 << _current_tile_0 << _ID_1 << _pos_x_1 << _pos_y_1 <<
		_state_1 << _current_tile_1;

	socket.send(packet);
}



void TronClient::sendTileUpdateMsg(sf::Uint32 _ID, float _pos_x, float _pos_y,
	sf::Uint32 _current_tile)
{
	sf::Packet packet;
	packet << NetMsg::TILEUPDATE << _ID << _pos_x << _pos_y << _current_tile;
	socket.send(packet);
}



void TronClient::sendEndGameMsg(int _ID)
{
	sf::Packet packet;
	packet << NetMsg::ENDGAME << _ID;
	socket.send(packet);
}



void TronClient::pong()
{
	auto end = std::chrono::steady_clock::now();
	latency = std::chrono::duration_cast
		<std::chrono::microseconds>
		(end - timestamp);
	latency /= 2;
}



void TronClient::handleUpdate(sf::Packet& _packet, GameData* _GD)
{
	int state_0, state_1, current_tile_0, current_tile_1, ID_0, ID_1;
	float pos_x_0, pos_x_1, pos_y_0, pos_y_1;

		_packet >> ID_0 >> pos_x_0 >> pos_y_0 >> state_0 >>
			current_tile_0 >> ID_1 >> pos_x_1 >>
			pos_y_1 >> state_1 >> current_tile_1;

	// Bike1
	_GD->setBikePosX(ID_0, pos_x_0);
	_GD->setBikePosY(ID_0, pos_y_0);
	_GD->setBikeState(ID_0, state_0);
	_GD->setBikeTilePos(ID_0, current_tile_0);

	// Bike2
	_GD->setBikePosX(ID_1, pos_x_1);
	_GD->setBikePosY(ID_1, pos_y_1);
	_GD->setBikeState(ID_1, state_1);
	_GD->setBikeTilePos(ID_1, current_tile_1);

	serUpdate = UpdateFromServer::UPDATE_AVAILABLE;
}



void TronClient::handleTileUpdate(sf::Packet& _packet, GameData* _GD)
{
	int currentTile, ID;
	float pos_x, pos_y;

	_packet >> ID >> pos_x >> pos_y >> currentTile;

	_GD->setBikePosX(ID, pos_x);
	_GD->setBikePosY(ID, pos_y);
	_GD->setBikeTilePos(ID, currentTile);

	serUpdate = UpdateFromServer::TILE_UPDATE_AVAILABLE;
}



void TronClient::handleEndGame(sf::Packet& _packet, GameData* _GD)
{
	int _ID;
	_packet >> _ID;

	_GD->setWinner(_ID);
	serUpdate = UpdateFromServer::END_GAME;
}



void TronClient::startupSettings(sf::Packet& _packet, GameData* _GD)
{
	// BikeID, identifies the players bike...
	sf::Uint32 bike_ID;

	_packet >> bike_ID;

	_GD->setBikeID(bike_ID);

	game_state = enumGameState::GS_PLAY_GAME;
}