#ifndef __MYSMSGIDS_H__
#define __MYSMSGIDS_H__


#include "RakNet\MessageIdentifiers.h"

enum MyMsgIDs
{
	ID_WELCOME = ID_USER_PACKET_ENUM,
	ID_JOIN_GAME,
	ID_START_COUNTDOWN,
	ID_CANCEL_START,
	ID_CLIENT_DISCONNECT,
	ID_SEND_OBJECT_INFO,
	ID_NEW_LEVEL,
	//hold all players new position

	ID_MOVEMENT,
	//move a player

	ID_OBJ_UPDATE
};


#endif