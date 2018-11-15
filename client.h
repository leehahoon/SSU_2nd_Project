#include "common.h"

struct CLIENT {
	struct CLIENT *next;
	char *pw;
	char *name;
	char *address;
	char *dial;
	int stuNum;
};

