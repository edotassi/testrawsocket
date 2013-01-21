
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <gmodule.h>
#include <pcap.h>
#include "type.h"


char *p = "\x1\x1\x1\x1\x1\x1\x2\x2\x2\x2\x2\x0\x8\x0\x0\x0\x1";

/* test func pointer */
typedef void (* TestFunc) ();

TestFunc test_func;
GModule *test;

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

	test = g_module_open("DataIO.dll", G_MODULE_BIND_LAZY);
	g_module_symbol(test, "load", (gpointer*) &test_func);
	test_func();


	t->handle = pcap_open_live(t->dev->name, 65536, 1, 1000, t->errbuf);

	pcap_sendpacket(t->handle, (const u_char*) p, 18);

	pcap_loop(t->handle, 0, packet_handler, NULL);

	system("PAUSE");

	return 0;
}