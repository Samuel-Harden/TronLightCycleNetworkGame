#pragma once
#include <SFML/Network.hpp>
enum NetMsg : sf::Int32
{
		       INVALID = 0,
	            UPDATE = 1,
			TILEUPDATE = 2,
	              PING = 3,
	              PONG = 4,
	CONFIRM_CONNECTION = 5,
	         SETSTATUS = 6,
	          AWAITING = 7,
		   LAUNCH_GAME = 8,
 	           ENDGAME = 9
};