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

	if (argc < 3) {
		fprintf(stderr, "Usage: %s cap args...\n", argv[0]);
		return 1;
	}

	for (c = cap; c->s; c++) {
		if (strcmp(c->s, argv[1]) == 0) {
			break;
		}
	}
	if (!c->s) {
		fprintf(stderr, "Unknown capability: %s\n", argv[1]);
		return 1;
	}

	if (prctl(PR_CAPBSET_DROP, c->n, 0, 0, 0) == -1) {
		perror("prctl");
		return 2;
	}

	execvp(argv[2], argv+2);
	perror("execvp");
	return 2;
}
