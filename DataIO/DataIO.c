#include "DataIO.h"

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

void (*handler)(int,const u_char*);

pcap_t *phandle;

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	handler(header->len, pkt_data);
}

DLLEXPORT void load() 
{
	pcap_if_t *dev;

	printf("loading...\n");
	
	pcap_findalldevs(&dev, NULL);
	phandle = pcap_open_live(dev->name,  65536, 1, 1000, NULL);
	printf("pcap opened...\n");
}

DLLEXPORT void set_handler(void(*_handler)(int, u_char *data))
{
	handler = _handler;
}

DLLEXPORT void start()
{
	pcap_loop(phandle, 0, packet_handler, NULL);
}