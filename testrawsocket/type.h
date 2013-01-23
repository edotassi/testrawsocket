
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#define u_char unsigned char

typedef struct _tobj
{
	GString *string;
} *tobj;

//typedef struct _tobj * tobj;

tobj type_tobj_new();
