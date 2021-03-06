#pragma once

#include "CServerConfig.h"
#include "CServerNetwork.h"
#include "CServerHandler.h"

#define SERVER						(CServer::GetInstance())
#define SERVERCONFIG				(SERVER->GetServerConfig())

#define SERVER_TYPE					(SERVERCONFIG->Get().GetServerInfo()->eType)
#define SERVER_PORT					(SERVERCONFIG->Get().GetServerInfo()->iPort)

#define LOGIN_SERVER				(SERVER_TYPE == SERVERTYPE_Login)
#define GAME_SERVER					(SERVER_TYPE == SERVERTYPE_Game)

#define SERVERNETWORK				(SERVER->GetServerNetwork())
#define SERVERHANDLER				(SERVER->GetServerHandler())

class CServer : public Application
{
	URHO3D_OBJECT( CServer, Application );
public:
    //Construtor
    explicit						CServer( Context * pcContext);

	void							Setup() override;

    //Inicializar depois do Setup e antes do Main Loop
    void							Start() override;

	void							Stop() override;

	BOOL							Init();

	//Getters and Setters
	static CServer				  * GetInstance(){ return pcInstance; }

	CServerNetwork				  * GetServerNetwork() const{ return pServerNetwork; }
	CServerHandler				  * GetServerHandler() const{ return pServerHandler; }
	CServerConfig				  * GetServerConfig() const{ return pServerConfig; }
private:
	BOOL							SetupDatabase();
protected:
	SharedPtr<CServerNetwork>		pServerNetwork;
	SharedPtr<CServerHandler>		pServerHandler;
	SharedPtr<CServerConfig>		pServerConfig;
private:
	static CServer				  * pcInstance;

	mongocxx::uri					cURI;
	mongocxx::client				cClient;
};
