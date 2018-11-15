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

