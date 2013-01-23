#include <stdio.h>
#include <stdlib.h>

#include <WinSock2.h>
#include <pcap.h>

#define __WINSOCKAPI__

#include <Windows.h>

#define DLLEXPORT __declspec(dllexport)

DLLEXPORT void load();

DLLEXPORT void set_handler(void(*_handler)(int, u_char *data));

DLLEXPORT void start();