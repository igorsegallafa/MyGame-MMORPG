#include "stdafx.h"
#include "CServer.h"

CServer * CServer::pcInstance = NULL;

URHO3D_DEFINE_APPLICATION_MAIN( CServer )

CServer::CServer( Context * pcContext ) : Application( pcContext )
{
	//Instanciar esta classe
	pcInstance = this;

	INI::Parser::RegisterObject( pcContext );

	//Registrar Objetos
	pcContext->RegisterFactory<CCharacter>();
	pcContext->RegisterFactory<CNonPlayerCharacter>();

	pServerConfig	= new CServerConfig( pcContext, "server.ini" );
	pServerNetwork	= new CServerNetwork( pcContext );
	pServerHandler	= new CServerHandler( pcContext );
}

void CServer::Setup()
{
	//Configurações da Aplicação
	if( SERVERCONFIG->Read() )
	{
		engineParameters_[EP_WINDOW_TITLE] = SERVERCONFIG->Get().GetServerInfo()->strName.CString();
		engineParameters_[EP_FULL_SCREEN] = false;
		engineParameters_[EP_HEADLESS] = true;
		engineParameters_[EP_SOUND] = false;
		engineParameters_[EP_WINDOW_RESIZABLE] = false;
		engineParameters_[EP_WINDOW_WIDTH] = 800;
		engineParameters_[EP_WINDOW_HEIGHT] = 416;
		engineParameters_[EP_RESOURCE_PATHS] = "../Server Data;";
	}

	//Setar o mouse como visivel
	GetSubsystem<Input>()->SetMouseVisible( true );
}

void CServer::Start()
{
	Application::Start();

	//Criar o console para o servidor
	OpenConsoleWindow();

	if( !Init() )
		Application::ErrorExit();
}

void CServer::Stop()
{
}

BOOL CServer::Init()
{
	BOOL bRet = TRUE;

	if( !SetupDatabase() )
		bRet = FALSE;

	if( !pServerNetwork->Init() )
		bRet = FALSE;

	if( !pServerHandler->Init() )
		bRet = FALSE;

	return bRet;
}

BOOL CServer::SetupDatabase()
{
	mongocxx::instance cInstance{};

	cURI = mongocxx::uri( "mongodb://localhost:27017" );
	cClient = mongocxx::client( cURI );

	//Setup Databases
	mongocxx::database cUserDatabase = cClient["userdb"];
	
	//Setup Collections
	UserEntry::SetCollection( cUserDatabase["user"] );

	return TRUE;
}