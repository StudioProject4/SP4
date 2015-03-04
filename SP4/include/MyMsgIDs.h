#ifndef __MYSMSGIDS_H__
#define __MYSMSGIDS_H__


#include "RakNet\MessageIdentifiers.h"

enum MyMsgIDs
{
	ID_WELCOME = ID_USER_PACKET_ENUM,
	ID_START,
	ID_CANCEL_START,
	ID_CLIENT_DISCONNECT,
	ID_SEND_OBJECT_INFO,
	ID_NEW_LEVEL,
	ID_GAME_PACKAGE,
	ID_COLLISION,
	ID_JOIN_GAME,
	ID_POINTS,
	//hold all players new position
	ID_NEW_PLAYER,

	ID_MOVEMENT,
	//move a player

	ID_VEL_CHANGED,
	//velocity changed

	ID_OBJ_UPDATE
};


#endif