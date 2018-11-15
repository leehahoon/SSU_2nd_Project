#include "common.h"

typedef struct Book {
	struct Book *nxt;
	char isLend;
	char *author;
	char *bookName;
	char *location;
	char *publish;
	long isbn;
	int bookNum;
} Book;

void PrintBookList(Book *head) {
	Book *cur = head;

	while (cur != NULL) {
		// TODO : add printf to print contents
		printf("* %s\n", cur->author);
		cur = cur->nxt;
	}
}

void AddBook(Book *head, Book book) {
	Book *cur = head;

	while (cur->nxt != NULL) {
		cur = cur->nxt;
	}

	cur->nxt = malloc(sizeof(Book));

	cur = cur->nxt;
	
	cur->isLend = book.isLend;
	cur->author = book.author;
	cur->bookName = book.bookName;
	cur->location = book.location;
	cur->publish = book.publish;
	cur->isbn = book.isbn;
	cur->bookNum = book.bookNum;

	cur->nxt = NULL;
}

