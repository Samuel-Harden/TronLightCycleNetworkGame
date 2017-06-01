#pragma once



enum enumGameState
{
	GS_NULL = 0,
	GS_MAIN_MENU,
	GS_PLAY_GAME,
	GS_GAME_OVER,
	GS_EXIT
};



enum ConnectionState
{
	CS_NULL = 0,
	CS_CONNECTED,
	CS_DISCONNECTED
};



enum ServerGameStatus
{
	SS_NULL = 0,
	SS_AWAITING,
	SS_PLAYING
};



enum UpdateFromServer
{
	            NO_UPDATE = 0,
	     UPDATE_AVAILABLE = 1,
	TILE_UPDATE_AVAILABLE = 2,
	       NO_TILE_UPDATE = 3,
				 END_GAME = 4
};



enum PlayerState
{
	PS_RIGHT = 0,
	PS_LEFT  = 1,
	PS_UP    = 2,
	PS_DOWN  = 3,
	PS_IDLE  = 4,
};



extern enumGameState game_state;
extern PlayerState player_state;
extern ConnectionState con_state;
extern ServerGameStatus serGame_state;
extern UpdateFromServer serUpdate;