
#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>

typedef struct _tobj
{
	pcap_if_t *dev;
	pcap_t *handle;
	char *errbuf;
} *tobj;

//typedef struct _tobj * tobj;

tobj type_tobj_new();
