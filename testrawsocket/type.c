#include "type.h"

tobj type_tobj_new()
{
	tobj t = (tobj) g_malloc0(sizeof(tobj));
	if (t == NULL)
	{
		fprintf(stderr, "Unable to alloc tobj memory\n");
		exit(1);
	}

	return t;
}
