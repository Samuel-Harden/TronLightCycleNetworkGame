// TronServerW32.cpp : Defines the entry point for the console application.

#include <Server/stdafx.h>
#include <memory>

#include "Server.h"

int main()
{
	std::unique_ptr<Server> m_server;
	m_server = std::make_unique<Server>();

	m_server->runServer();

    return 0;
}

