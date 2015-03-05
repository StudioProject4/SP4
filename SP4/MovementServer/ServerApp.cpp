#include "ServerApp.h"
#include "RakNet\RakPeerInterface.h"
#include "RakNet\Bitstream.h"
#include "RakNet\GetTime.h"
#include "MyMsgIDs.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>

using namespace std;

ServerApp::ServerApp() : 
	rakpeer_(RakPeerInterface::GetInstance())
	,newID(0)
	//newProjectileID(0),
	,maxPlayers(2)
	,playerNum(0)
	,proc(0)
{
	rakpeer_->Startup(100, &SocketDescriptor(1691, 0), 1);
	rakpeer_->SetMaximumIncomingConnections(100);
	rakpeer_->SetOccasionalPing(true);
	gameStart=false;
	std::cout << "Server Started" << std::endl;
}

ServerApp::~ServerApp()
{
	rakpeer_->Shutdown(100);
	RakPeerInterface::DestroyInstance(rakpeer_);
}

void ServerApp::Loop()
{
	if (Packet* packet = rakpeer_->Receive())
	{
		RakNet::BitStream bs(packet->data, packet->length, false);
		
		unsigned char msgid = 0;
		RakNet::Time timestamp = 0;

		bs.Read(msgid);
		//cout<<"handling msg "<<(int)(msgid)<<" num "<<proc++<<endl;
		if (msgid == ID_TIMESTAMP)
		{
			bs.Read(timestamp);
			bs.Read(msgid);
		}
		switch (msgid)
		{
		case ID_NEW_INCOMING_CONNECTION:
			
			playerNum = static_cast<unsigned int>(clients_.size());
			if(playerNum+1>maxPlayers)//here test for the 2 player thing
			{
				rakpeer_->CloseConnection(packet->systemAddress,true);
			}
			else
			{
				playerNum++;
				cout<<"new connection\n";
				AcceptConnection(packet->systemAddress);

			}
			
			//SendWelcomePackage(packet->systemAddress);
			break;
		case ID_JOIN_GAME:
			if(playerNum+1>maxPlayers)
			{
				std::vector<ClientInfo*>::iterator it=clients_.begin();
				for(;it!=clients_.end();++it)
				{
					if((*it)->address==packet->systemAddress)
					{
						break;
					}
				}
				//if(gameStart)//for games that already started
				{
					SendGamePackage((*it)->address,(*it)->username,(*it)->ClientID);
				}
				//else
				{
					//SendLobbyInfo((*it)->address,(*it)->username,(*it)->ClientID);
				}
			}
			else
			{
				//send error msg
			}
			break;
		case ID_COLLISION:
		case ID_SEND_OBJECT_INFO:
			bs.ResetReadPointer();
			rakpeer_->Send(&bs,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,true);
			break;
		case ID_START:
			gameStart=true;//only does this for gameStart
		case ID_GAME_PACKAGE:
		case ID_CANCEL_START:
		case ID_OBJ_UPDATE:
		case ID_NEW_LEVEL:
		case ID_NEW_PLAYER:
		case ID_MOVEMENT:
		case ID_VEL_CHANGED:
		case ID_NEW_MAP:
		case ID_REQUEST_MAP_CLEAR:
			bs.ResetReadPointer();
			rakpeer_->Send(&bs,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,true);
			break;
		default:
			std::cout << "Unhandled Message Identifier: " << (int)msgid << std::endl;
			assert(msgid<=ID_USER_PACKET_ENUM);
		}

		rakpeer_->DeallocatePacket(packet);
	}
	
}

void ServerApp::SendGamePackage(SystemAddress& addr,string name,int ClientID)
{
	unsigned int shipcount = static_cast<unsigned int>(clients_.size());
	unsigned char msgid;
	
	RakNet::BitStream bs;
	//send to every one that a new person is here
	msgid=ID_NEW_PLAYER;
	bs.Write(msgid);
	
	bs.Write(ClientID);

	//new client information
	rakpeer_->Send(&bs,HIGH_PRIORITY,RELIABLE_ORDERED,0,addr,true);//send to everyone except the new client


	//check for null error here
	std::cout << "New guy, assigned id " << ClientID << std::endl;
}

void ServerApp::SendLobbyInfo(SystemAddress& addr,string name,int ClientID)
{
	unsigned int shipcount = static_cast<unsigned int>(clients_.size());
	unsigned char msgid = ID_WELCOME;
	
	RakNet::BitStream bs;
	bs.Write(msgid);

	//write other info about the new client

	bs.Write(shipcount);

	for (vector<ClientInfo*>::iterator itr = clients_.begin(); itr != clients_.end(); ++itr)
	{
		bs.Write((*itr)->ClientID);

		//write other clients' information here

	}


	RakPeerInterface::GetInstance()->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED,0, addr, false);

	bs.Reset();
	//send to every one that a new person is here
	msgid=ID_JOIN_GAME;
	bs.Write(msgid);

	//new client information

	rakpeer_->Send(&bs,HIGH_PRIORITY,RELIABLE_ORDERED,0,addr,true);
}

void ServerApp::AcceptConnection(SystemAddress& addr)
{
	ClientInfo* temp=new ClientInfo;
	temp->address=addr;
	++newID;
	temp->ClientID=newID;
	clients_.push_back(temp);
	SendGamePackage(addr,"someone",temp->ClientID);
}

void ServerApp::SendDisconnectionNotification(SystemAddress& addr)
{
	//LobbyMap::iterator itr = clients_.find(addr);
	vector<ClientInfo*>::iterator itr = clients_.begin();
	for(;itr!=clients_.end();++itr)
	{
		if((*itr)->address==addr)
			break;
	}
	if (itr == clients_.end())
		return;

	unsigned char msgid = ID_CLIENT_DISCONNECT;
	RakNet::BitStream bs;
	bs.Write(msgid);
	bs.Write((*itr)->ClientID);
	rakpeer_->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, addr, true);

	std::cout << (*itr)->ClientID << " has left the game" << std::endl;


	clients_.erase(itr);
}
