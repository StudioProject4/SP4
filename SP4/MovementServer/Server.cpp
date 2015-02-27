#include "ServerApp.h"
//#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	ServerApp app;
	while (true)
	{
		Sleep(10);
		app.Loop();
	}
	return 0;
}