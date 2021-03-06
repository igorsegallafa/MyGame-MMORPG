#pragma once

#include "CGameConfig.h"
#include "CGameManager.h"
#include "CGameHandler.h"
#include "CGameNetwork.h"

#define GAME					(CGame::GetInstance())

#define GAMECONFIG				(GAME->GetGameConfig())
#define GAMEHANDLER				(GAME->GetGameHandler())
#define GAMEMANAGER				(GAME->GetGameManager())
#define GAMENETWORK				(GAME->GetGameNetwork())

class CGame : public Application
{
	URHO3D_OBJECT( CGame, Application );
public:
    //Construtor
    explicit					CGame( Context * pcContext);

	void						Setup() override;

    //Inicializar depois do Setup e antes do Main Loop da Aplicação
    void						Start() override;

	void						Stop() override;

	BOOL						Init();

	//Getters and Setters
	static CGame			  * GetInstance() { return pcInstance; }

	CGameConfig				  * GetGameConfig(){ return pGameConfig; }
	CGameManager			  * GetGameManager(){ return pGameManager; }
	CGameHandler			  * GetGameHandler(){ return pGameHandler; }
	CGameNetwork			  * GetGameNetwork(){ return pGameNetwork; }
private:
    void						HandleUpdate( StringHash cEventType, VariantMap & vEventData );
	void						HandlePostUpdate( StringHash cEventType, VariantMap & vEventData );
	void						HandlePhysicsPreStep( StringHash cEventType, VariantMap & vEventData );
protected:
	SharedPtr<CGameManager>		pGameManager;
	SharedPtr<CGameHandler>		pGameHandler;
	SharedPtr<CGameNetwork>		pGameNetwork;
	SharedPtr<CGameConfig>		pGameConfig;
private:
	static CGame			  * pcInstance;
};
