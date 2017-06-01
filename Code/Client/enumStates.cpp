#include "enumStates.h"



enumGameState game_state = enumGameState::GS_MAIN_MENU;
PlayerState player_state = PlayerState::PS_IDLE;
ConnectionState con_state = ConnectionState::CS_NULL;
ServerGameStatus serGame_state = ServerGameStatus::SS_NULL;
UpdateFromServer serUpdate = UpdateFromServer::NO_UPDATE;