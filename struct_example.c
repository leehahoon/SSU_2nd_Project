#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct client {
	struct client * next;
	int stu_num;
	char *pw;
	char *name;
	char *address;
	char *dial;
};

struct book {
	struct book * next;
	int book_num;
	char *book_name;
	char *publish;
	char *author;
	long isbn;
	char *location;
	char is_lend;
};

struct borrow {
	struct borrow * next;
	int stu_num;
	int book_num;
	time_t lend_date;
	time_t return_date;
};