#pragma once

//#include <Server/stdafx.h>
#include <SFML/Network.hpp>

#include <memory>
#include <vector>
#include <chrono>

class GameData;

const sf::IpAddress SERVER_IP("127.0.0.1");
constexpr int SERVER_TCP_PORT(53000);

using TcpClient = sf::TcpSocket;
using TcpClientPtr = std::unique_ptr<TcpClient>;
using TcpClients = std::vector<TcpClientPtr>;

using namespace std::chrono_literals;

class TronClient
{
public:

	TronClient();
	~TronClient();

	void client(GameData* _GD);

	const auto& getPingTime() const { return timestamp; }
	const auto& getLatency()  const { return latency; }

	void sendAwaitingMsg();

	void sendUpdateMsg(sf::Uint32 _ID_0, float _pos_x_0, float _pos_y_0,
		sf::Uint32 _state_0, sf::Uint32 _current_tile_0,
				       sf::Uint32 _ID_1, float _pos_x_1, float _pos_y_1,
		sf::Uint32 _state_1, sf::Uint32 _current_tile_1);

	void sendTileUpdateMsg(sf::Uint32 _ID, float _pos_x, float _pos_y,
		sf::Uint32 _current_tile);
	void sendEndGameMsg(int _ID);

protected:

private:

	bool connect();
	void startupSettings(sf::Packet& _packet, GameData* _GD);
	void handleUpdate(sf::Packet& _packet, GameData* _GD);
	void handleTileUpdate(sf::Packet& _packet, GameData* _GD);
	void handleEndGame(sf::Packet& _packet, GameData* _GD);

	void pong();

	sf::Socket::Status status;
	TcpClient socket;

	std::chrono::steady_clock::time_point timestamp = std::chrono::steady_clock::now();
	std::chrono::microseconds latency = 100us;
};