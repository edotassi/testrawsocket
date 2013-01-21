
#include <Windows.h>
#include <stdio.h>

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}


__declspec(dllexport) void load() 
{
	printf("ciao mondo\n");
}