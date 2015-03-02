#pragma once

extern "C" {
#include <LUA/lua.h>
#include <LUA/lualib.h>
#include <LUA/lauxlib.h>
}

#include <vector>
#include <string>

class CLuaManager
{
public:
	enum enumLuaDataType
	{
		DATA_NILL = 0,
		DATA_BOOLEAN = 1,
		DATA_NUMBER = 3,
		DATA_STRING = 4,
		DATA_FUNCTION = 6,
	};
	//enum enumprimitiveDataType
	//{
	//	C_NILL = 0,
	//	C_BOOLEAN = 1,
	//	C_INT = 2,
	//	C_FLOAT = 3,
	//	C_CHAR = 5,
	//	C_STRING = 6,
	//};
private:
	bool inited;
	lua_State *L;

private:
	CLuaManager(void);
	static CLuaManager* instance;
public:
	
	static CLuaManager* GetInstance();
	void Init(char* filetobeused);
	void CloseState();
	void Test();
	~CLuaManager(void);


	inline void GetGlobal(char * varablename)
	{
		lua_getglobal(L,varablename);
	}

	template <typename type>
	inline type ToNumber(short index = -1)
	{
		return (type)lua_tonumber(L,index);
	}
	inline int ToInterger(short index = -1)
	{
		return (int)lua_tointeger(L,index);
	}
	inline bool ToBoolean(short index= -1)
	{
		return lua_toboolean(L,index);
	}
	inline std::string ToString(short index= -1)
	{
		return lua_tostring(L,index);
	}
	inline bool IsNumber(short index= -1)
	{
		return lua_isnumber(L,index);
	}
	inline bool IsBoolean(short index= -1)
	{
		return lua_isboolean(L,index);
	}
	inline bool IsString(short index = -1)
	{
		return lua_isstring(L,index);
	}
	inline bool PCall(int narg,int nresult,int errfun = 0)
	{
		return lua_pcall(L,narg,nresult,errfun);
	}
	inline bool GetWithCheckBoolean(char * varbilename,int index = -1)
	{
		PopStack();//prevent accidental overflow of stack

		GetGlobal(varbilename);
		if(IsBoolean())
		{
			return ToBoolean(index);
		}else
		{
			printf ("\n");
			printf (varbilename);
			printf (" needs to be a boolean");
			return false;
		}
	}
	inline void PopStack(int index = -1)
	{
		lua_pop(L,index);
	}
	inline std::string GetWithCheckString(char * varbilename,int index = -1)
	{
		PopStack();//prevent accidental overflow of stack

		GetGlobal(varbilename);
		if(IsString())
		{
			return ToString(index);
		}else
		{
			printf ("\n");
			printf (varbilename);
			printf (" needs to be a string");
			return " ";
		}
	}
	template<typename type>
	inline type GetWithCheckNumber(char * varbilename,int index = -1)
	{
		PopStack();//prevent accidental overflow of stack

		GetGlobal(varbilename);
		if(IsNumber())
		{
			return ToNumber<type>(index);
		}else
		{
			printf ("\n");
			printf (varbilename);
			printf (" needs to be a number");
			return (type)0;
		}
	}

	//inline void Register(char* nameoffunction,int (*pt2Func)(char))
	//{
	//	
	//	lua_register(L,nameoffunction,luaSetCubePosition);
	//}

	template<typename type1>
	inline void PushNumber(type1 number)
	{
		
		lua_pushnumber(L,number);
	}

	void testfunction()
	{
		//GetGlobal("add");
		//PushNumber(10);
		//PushNumber(10);
		//PCall(2,1);
		//return (float)lua_tointeger(L, -1);

		std::vector<int> arglist;
		arglist.push_back(10.11);
		arglist.push_back(2.33);
		//const char* type = typeid(int).name();

		printf("%i ",CallLuaFunctionNumber<int>("add",arglist));
	}

	template <typename type>
	inline type CallLuaFunctionNumber(char * functionname,std::vector<type>arglist)
	{
		PopStack();
		GetGlobal(functionname);
		for(unsigned short i = 0; i<arglist.size();++i)
		{
			PushNumber(arglist[i]);
		}
		PCall(arglist.size(),1);
		return ToNumber<type>();
	}
	bool Exit()
	{
		if(instance != 0)
		{
			//CleanUp();
			//if(L != 0)
			//{
			//	delete L;
			//	L = 0;
			//}
			delete instance;
			instance = 0;

			return true;
		}else
		{
			return true;
		}
		return false;
	}
	////not working
	//template<typename type>
	//inline enumprimitiveDataType CheckDataType(type)
	//{
	//	const char * INT = "int";
	//	const char * FLOAT = "float";
	//	const char * BOOL = "bool";
	//	const char * CHAR = "char";
	//	const char * STRING  = "string";
	//	if(typeid(type).name == INT)
	//	{
	//		return enumprimitiveDataType::C_INT;
	//	}else
	//		if(typeid(type).name == FLOAT)
	//	{
	//		return enumprimitiveDataType::C_FLOAT;
	//	}else
	//		if(typeid(type).name == BOOL)
	//	{
	//		return enumprimitiveDataType::C_BOOLEAN;
	//	}else
	//		if(typeid(type).name == CHAR)
	//	{
	//		return enumprimitiveDataType::C_CHAR;
	//	}else
	//		if(typeid(type).name == STRING)
	//	{
	//		return enumprimitiveDataType::C_STRING;
	//	}
	//}

	
};

