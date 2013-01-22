
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <gmodule.h>
#include <pcap.h>
#include "type.h"


char *p = "\x1\x1\x1\x1\x1\x1\x2\x2\x2\x2\x2\x0\x8\x0\x0\x0\x1";

/* test func pointer */
typedef void (* TestFunc) ();

typedef void (*LoadFunc) ();
typedef void (*SetHandlerFunc) (void(*handler) (int, u_char*));
typedef void (*StartFunc) ();

TestFunc test_func;
LoadFunc load;
SetHandlerFunc set_handler;
StartFunc start;

GModule *test;

void packet_handler(int len, u_char *data)
{
	printf("grab packet %d\n", len);
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
	g_module_symbol(test, "load", (gpointer*) &load);
	g_module_symbol(test, "set_handler", (gpointer*) &set_handler);
	g_module_symbol(test, "start", (gpointer*) &start);


	load();
	set_handler(&packet_handler);
	start();

	system("PAUSE");

	return 0;
}