#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/prctl.h>
#include "dat.h"

extern Cap cap[];

int
main(int argc, char *argv[])
{
	Cap *c;

	for (c = cap; c->s; c++) {
		printf("%s\n", c->s);
	}
	return 0;
}
