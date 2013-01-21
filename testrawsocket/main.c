
#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <WinSock2.h>

#include "type.h"


char *p = "\x1\x1\x1\x1\x1\x1\x2\x2\x2\x2\x2\x0\x8\x0\x0\x0\x1";

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	printf("grab packet %d\n", header->len);
}

int main(int argc, char *argv[]) {

	pcap_if_t *alldevs;
	pcap_if_t *d;

	pcap_t *handle;

	tobj t = type_tobj_new();

	if (pcap_findalldevs(&alldevs, t->errbuf) == -1)
	{
		fprintf(stderr, "unable to find interfaces\n");
		exit(1);
	}

	t->dev = alldevs;

	for(d = alldevs; d; d = d->next)
	{
		printf("%s\n", d->description);
	}


	t->handle = pcap_open_live(t->dev->name, 65536, 1, 1000, t->errbuf);

	pcap_sendpacket(t->handle, p, 18);

	pcap_loop(t->handle, 0, packet_handler, NULL);

	system("PAUSE");

	return 0;
}