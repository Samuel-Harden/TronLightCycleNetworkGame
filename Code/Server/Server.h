#pragma once

#include <SFML\Network.hpp>
#include <memory>

class Client;
class TronGame;

constexpr int SERVER_TCP_PORT(53000);
constexpr int SERVER_UDP_PORT(53001);

using TcpClient = sf::TcpSocket;
using TcpClientPtr = std::unique_ptr<TcpClient>;
using TcpClients = std::vector<Client>;

class Server
{
public:
	Server();
	~Server();

	void runServer();

protected:

private:

	bool bindServerPort();
	void listen();
	void connect();
	void receiveMsg();
	void sendPlayMsg();

	void ping();
	void clearStaleCli();

	void processUpdate(sf::Packet& packet, Client& sender);

	void processTileUpdate(sf::Packet& packet, Client& sender);

	void processEndGameUpdate(sf::Packet& packet, Client& sender);

	void updateGameStatus(sf::Packet& packet, Client& sender);

	sf::TcpListener tcp_listener;

	sf::SocketSelector selector;

	TcpClients tcp_clients;

	std::unique_ptr<TronGame> server_game;

	int noReadyPlayers;

	bool runGame;
};