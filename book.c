#include "book.h"

void PrintBookInfo(Book *cur) {
	printf("\n-----------------------------\n");
	printf("* 도서명: %s\n", cur->bookName);
	printf("* 출판사: %s\n", cur->publish);
	printf("* 저자명: %s\n", cur->author);
	printf("* ISBN: %s\n", cur->isbn);
	printf("* 소장처: %s\n", cur->location);
	printf("* 대여가능 여부: %s\n", cur->lendAble);
	printf("-----------------------------\n");
	
	return;
}

int IsSubstring(char *A, char *B) {
	aLen = strlen(A);
	bLen = strlen(B);

	int *fail, fLen;
	fLen = (aLen >= bLen ? aLen : bLen) + 1;
	fail = (int*)malloc(sizeof(int)*fLen);

	for (int i = 1, j = 0; i < bLen; i++) {
		while (j && B[i] != B[j]) j = fail[j-1];
		if (B[i] == B[j]) fail[i] = ++j;
	}

	for (int i = 0, j = 0; i < aLen; i++) {
		while (j && A[i] != B[j]) j = fail[j-1];
		if (A[i] == B[j]) {
			if (j == bLen-1) return 1;
			else j++;
		}
	}

	free(fail);

	return 0;
}

void SearchBookName(Book *head, char *target, int searchType) {
	Book *cur = head;

	while (cur->nxt != NULL) {
		int flag = 0;
		char *temp;

		if (searchType == 1) {
			temp = book.bookName;
		} else if (searchType == 2) {
			temp = book.publish;
		} else if (searchType == 3) {
			temp = book.isbn;
		} else if (searchType == 4) {
			temp = book.author;
		}

		flag = IsSubstring(temp, target);

		if (searchType == 5) {
			flag = 0;
		}

		if (flag) {
			PrintBookInfo(cur);
		}

		cur = cur->nxt;
	}

	return;
}

void AddBook(Book *head, Book book) {
	Book *cur = head;

	while (cur->nxt != NULL && strcmp(cur->nxt->isbn, book->isbn) < 0) {
		cur = cur->nxt;
	}

	Book *end = cur->nxt;
	cur->nxt = malloc(sizeof(Book));

	cur = cur->nxt;
	
	cur->lendAble = book.lendAble;
	cur->author = book.author;
	cur->bookName = book.bookName;
	cur->location = book.location;
	cur->publish = book.publish;
	cur->isbn = book.isbn;
	cur->bookNum = book.bookNum;

	cur->nxt = end;

	return;
}

void RemoveBook(Book *head, int bookNum) {
	Book *cur = head;

	while (cur->nxt != NULL && cur->nxt->bookNum != bookNum) {
		cur = cur->nxt;
	}

	if (cur->nxt == NULL) {
		printf("!!!!!! No Book #%d in DB !!!!!!", bookNum);
		return;
	}

	Book *tmp = cur->nxt->nxt;
	free(cur->nxt);
	cur->nxt = tmp;

	return;
}

void lendBook(Book *head, int bookNum) {
	while (cur->nxt != NULL && cur->nxt->bookNum != bookNum) {
		cur = cur->nxt;
	}

	if (cur->nxt == NULL) {
		printf("!!!!!! No Book #%d in DB !!!!!!", bookNum);
		return;
	}

	if (cur->nxt->lendAble == 'N') {
		printf("!!!!!! Book #%d has already been borrowed !!!!!!", bookNum);
		return;
	}

	cur->nxt->lendAble = 'N';

	return;
}

void returnBook(Book *head, int bookNum) {
	while (cur->nxt != NULL && cur->nxt->bookNum != bookNum) {
		cur = cur->nxt;
	}

	if (cur->nxt == NULL) {
		printf("!!!!!! No Book #%d in DB !!!!!!", bookNum);
		return;
	}

	if (cur->nxt->lendAble == 'Y') {
		printf("!!!!!! Book #%d has not been borrowed !!!!!!", bookNum);
		return;
	}

	cur->nxt->lendAble = 'Y';

	return;
}