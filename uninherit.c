#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/capability.h>
#include "dat.h"

extern Cap cap[];

int
main(int argc, char *argv[])
{
	Cap *c;
	struct __user_cap_header_struct h = {};
	struct __user_cap_data_struct d = {};

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

	h.version = _LINUX_CAPABILITY_VERSION_1;
	h.pid = 0;
	if (capget(&h, &d) == -1) {
		perror("capget");
		return 2;
	}

	d.inheritable &= ~(1 << c->n);
	if (capset(&h, &d) == -1) {
		perror("capset");
		return 2;
	}

	execvp(argv[2], argv+2);
	perror("execvp");
	return 2;
}
