
#include <pcap.h>


typedef struct _tobj tobj;

tobj* type_tobj_new();

struct _tobj
{
	pcap_if_t *dev;
	pcap_t *handle;
	char errbuf[PCAP_ERRBUF_SIZE];
};