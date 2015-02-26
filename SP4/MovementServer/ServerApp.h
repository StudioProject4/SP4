#ifndef SERVERAPP_H_
#define SERVERAPP_H_

#include "RakNet\RakPeerInterface.h"
#include <map>
#include <vector>


using namespace RakNet;

struct GameObject 
{
	GameObject(unsigned int newid)
	: x_(0), y_(0), type_(1)
	{
		id = newid;
	}

	unsigned int id;
	std::string username;
	float x_;
	float y_;
	float sizeX;
	float sizeY;
	int type_;
};


struct ClientInfo//to keep client information on the outermost layer
{
	SystemAddress address;
	int ClientID;
	std::string username;
};

class ServerApp
{
	bool gameStart;
	int playerNum;
	int maxPlayers;
	RakPeerInterface* rakpeer_;
	std::vector<ClientInfo*> clients_;
	unsigned int newID;
	int clientNum;
	void SendGamePackage(SystemAddress& addr,std::string name,int ClientID);//client id is suppsed to be the database id
	void SendLobbyInfo(SystemAddress& addr,std::string name,int ClientID);
	void AcceptConnection(SystemAddress& addr);
	void SendDisconnectionNotification(SystemAddress& addr);
public:
	ServerApp();
	~ServerApp();
	void Loop();
};

#endif