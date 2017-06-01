#include "Server.h"

#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <thread>

#include <SFML\Network.hpp>
#include <Game\TronGame.h>
#include <Game\LightCycle.h>

#include "MessageTypes.h"
#include "Client.h"



Server::Server():
	noReadyPlayers(0),
	runGame(false)
{
	float x = 1000.0f;
	float y = 1000.0f;
	server_game = std::make_unique<TronGame>(2, x, y);
}



Server::~Server()
{
	// Tidy stuff away
}



void Server::runServer()
{
	if (!bindServerPort())
	{
		return;
	}

	//sf::SocketSelector selector;
	selector.add(tcp_listener);

	//TcpClients tcp_clients;
	return listen();
}



bool Server::bindServerPort()
{
	if (tcp_listener.listen(SERVER_TCP_PORT) != sf::Socket::Done)
	{
		std::cout << "Could not bind server port, is another app using it?";
		std::cout << std::endl << "Port: " << SERVER_TCP_PORT;
		std::cout << std::endl;
		return false;
	}

	std::cout << "TronServer launched on port: " << SERVER_TCP_PORT << std::endl;
	std::cout << "Searching for LightCycles..." << std::endl;
	return true;
}


// Connect a new player to server
void Server::connect()
{
	auto  client_ptr = new sf::TcpSocket;
	auto& client_ref = *client_ptr;

	if (tcp_listener.accept(client_ref) == sf::Socket::Done)
	{
		selector.add(client_ref);

		auto client = Client(client_ptr);
		tcp_clients.push_back(std::move(client));
		std::cout << "client connected" << std::endl;

		sf::Packet packet;
		packet << NetMsg::CONFIRM_CONNECTION;
		client_ref.send(packet);
	}
}



void Server::listen()
{
	while (true)
	{
		// start game
		if (runGame == true)
		{
			server_game->Tick();
		}

		const sf::Time timeout = sf::Time(sf::milliseconds(250));
		if (selector.wait(timeout))
		{
			if (selector.isReady(tcp_listener))
			{
				connect();
			}
			else
			{
				receiveMsg();
				clearStaleCli();
			}
		}
		else
		{
			ping();
		}
	}
}



void Server::receiveMsg()
{
	for (auto& sender : tcp_clients)
	{
		auto& sender_socket = sender.getSocket();
		if (selector.isReady(sender_socket))
		{
			sf::Packet packet;
			if (sender_socket.receive(packet) == sf::Socket::Disconnected)
			{
				selector.remove(sender_socket);
				sender_socket.disconnect();
				std::cout << "Client (" << sender.getClientID()
					<< ") Disconnected" << std::endl;

				noReadyPlayers--;

				break;
			}

			int header = 0;
			packet >> header;

			NetMsg msg = static_cast<NetMsg>(header);

			// forward an update message
			if (msg == NetMsg::UPDATE)
			{
				processUpdate(packet, sender);
			}

			// forward an update message
			if (msg == NetMsg::TILEUPDATE)
			{
				processTileUpdate(packet, sender);
			}

			// If the game ahs ended
			if (msg == NetMsg::ENDGAME)
			{
				processEndGameUpdate(packet, sender);
			}

			else if (msg == NetMsg::PONG)
			{
				sender.pong();
			}

			// If player is ready to play...
			else if (msg == NetMsg::AWAITING)
			{
				updateGameStatus(packet, sender);
			}
		}
	}
}



void Server::clearStaleCli()
{
	tcp_clients.erase(
		std::remove_if(tcp_clients.begin(), tcp_clients.end(), [](const Client& client)
	{
		return(!client.isConnected());
	}), tcp_clients.end());
}



void Server::processUpdate(sf::Packet& packet, Client& sender)
{
	// unpack packet,
	int ID0, ID1;
	float posX0, posX1;
	float posY0, posY1;
	int state0, state1;
	int current_tile0, current_tile1;

	packet >> ID0 >> posX0 >> posY0 >> state0 >> current_tile0
		   >> ID1 >> posX1 >> posY1 >> state1 >> current_tile1;

	// first bike
	if (server_game->getLightCycle(ID0)->getPosX() != posX0)
	{
		posX0 = server_game->getLightCycle(ID0)->getPosX();
		std::cout << server_game->getLightCycle(ID0)->getPosX() << std::endl;
	}

	if (server_game->getLightCycle(ID0)->getPosY() != posY0)
	{
		posY0 = server_game->getLightCycle(ID0)->getPosY();
		std::cout << server_game->getLightCycle(ID0)->getPosY() << std::endl;
	}

	// STATE + TILE
	server_game->getLightCycle(ID0)->setState(state0);
	server_game->getLightCycle(ID0)->setCurrentTile(current_tile0);

	// second bike
	if (server_game->getLightCycle(ID1)->getPosX() != posX1)
	{
		posX1 = server_game->getLightCycle(ID1)->getPosX();
		std::cout << server_game->getLightCycle(ID1)->getPosX() << std::endl;
	}

	if (server_game->getLightCycle(ID1)->getPosY() != posY1)
	{
		posY1 = server_game->getLightCycle(ID1)->getPosY();
		std::cout << server_game->getLightCycle(ID1)->getPosY() << std::endl;
	}

	//STATE + TILE
	server_game->getLightCycle(ID1)->setState(state1);
	server_game->getLightCycle(ID1)->setCurrentTile(current_tile1);

	// forward the packet on to the other clients...
	for (auto& client : tcp_clients)
	{
		if (sender == client)
			continue;

		client.getSocket().send(packet);
	}
}


void Server::processTileUpdate(sf::Packet& _packet, Client& sender)
{
	int ID, current_tile;
	float pos_x, pos_y;

	_packet >> ID >> pos_x >> pos_y >> current_tile;

	if (server_game->getLightCycle(ID)->getPosX() != pos_x)
	{
		pos_x = server_game->getLightCycle(ID)->getPosX();
		std::cout << server_game->getLightCycle(ID)->getPosX() << std::endl;
	}

	if (server_game->getLightCycle(ID)->getPosY() != pos_y)
	{
		pos_y = server_game->getLightCycle(ID)->getPosY();
		std::cout << server_game->getLightCycle(ID)->getPosY() << std::endl;
	}

	if (server_game->getLightCycle(ID)->getCurrentTile() != current_tile)
	{
		current_tile = server_game->getLightCycle(ID)->getCurrentTile();
	}

	for (auto& client : tcp_clients)
	{
		if (sender == client)
			continue;

		client.getSocket().send(_packet);
	}
}



void Server::processEndGameUpdate(sf::Packet& packet, Client& sender)
{
	for (auto& client : tcp_clients)
	{
		if (sender == client)
			continue;

		client.getSocket().send(packet);
	}
	runGame = false;
}



void Server::updateGameStatus(sf::Packet& packet, Client& sender)
{
	std::cout << "Client Ready to Play..." << std::endl;

	noReadyPlayers++;

	// check if game is ready to start
	// once we have enough players, set up game...
	if (noReadyPlayers == 2)
	{
		runGame = true;
	}

	if (runGame == true)
	{
		sendPlayMsg();

		// reset players
		noReadyPlayers = 0;
	}
}



void Server::sendPlayMsg()
{
	sf::Uint32 bikeID = 0;

	// Reset Game
	server_game->resetTiles();
	server_game->resetBikes();

	for (auto& client : tcp_clients)
	{
		// Send ID of Bike each player controls...
		sf::Packet packet;
		packet << NetMsg::LAUNCH_GAME << bikeID;

		client.getSocket().send(packet);
		bikeID++;
	}
}



void Server::ping()
{
	constexpr auto timeout = 1.0s;
	for (auto& client : tcp_clients)
	{
		const auto& timestamp = client.getPingTime();
		const auto  now = std::chrono::steady_clock::now();
		auto delta = now - timestamp;
		if (delta > timeout)
		{
			client.ping();
		}
	}
}