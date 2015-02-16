#include "LuaManager.h"
#include <stdio.h>

CLuaManager* CLuaManager::instance = 0;

CLuaManager::CLuaManager(void)
	:inited(false)
	,L(0)
{
	////Init();
}

CLuaManager::~CLuaManager(void)
{
}

CLuaManager* CLuaManager::GetInstance()
{
	if(instance == 0)
	{
		instance = new CLuaManager();
	}
	return instance;
}

void CLuaManager::Init(char* filetobeused)
{
	if(inited == false)
	{
		printf("Initing lua");
		L = lua_open();
		luaL_openlibs(L);
		luaL_loadfile(L,filetobeused);
		PCall(0,0);
		printf("\nFinish initing lua");
		inited = true;
	}else
	{
		luaL_loadfile(L,filetobeused);
		PCall(0,0);
		printf("\nLua Inited already");
		printf("\nLua Loaded another file");
	}
}

void CLuaManager::Test()
{
	if(inited)
	{
	char buffer[50];

	//testing lua data_type
	//luaL_dofile(L,"mylua.lua");
	PCall(0,0,0);

	lua_getglobal(L,"testvalue1");
	lua_getglobal(L,"testvalue2");
	lua_getglobal(L,"testvalue3");
	lua_getglobal(L,"testvalue4");
	lua_getglobal(L,"testvalue5");
	lua_getglobal(L,"add");

	

	sprintf(buffer,"%d",lua_type(L,1));
	puts(buffer);

	sprintf(buffer,"%d",lua_type(L,2));
	puts(buffer);

	sprintf(buffer,"%d",lua_type(L,3));
	puts(buffer);

	sprintf(buffer,"%d",lua_type(L,4));
	puts(buffer);
		
	sprintf(buffer,"%d",lua_type(L,5));
	puts(buffer);

	sprintf(buffer,"%d",lua_type(L,6));
	puts(buffer);
	////testing end

	//luaL_dofile(L,"mylua.lua");
	GetGlobal("testvalue1");
	std::string result = lua_tostring(L,1);
	sprintf(buffer,"%f",lua_tonumber(L,1));
	puts(buffer);
	//std::cout<<result<<std::endl;
	
	luaL_dostring(L,"print('hentai')");
	lua_pcall(L,0,0,0);
	}else
	{
		printf("\n init lua first please");
	}
}

void CLuaManager::CloseState()
{
	if(L != 0 )
	{
		lua_close(L);
		L = 0;
		printf("\nLua State closed");
	}
	
}

