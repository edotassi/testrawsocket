#include "type.h"

tobj type_tobj_new()
{
	tobj t = (tobj) malloc(sizeof(tobj));
	if (t == NULL)
	{
		fprintf(stderr, "Unable to alloc tobj memory\n");
		exit(1);
	}

	return t;
}
