#include "common.h"

typedef struct Book {
    struct Book *nxt;
    char lendAble;
    char *author;
    char *bookName;
    char *location;
    char *publish;
    char *isbn;
    int bookNum;
} Book;

void PrintBookInfo(Book *cur);
int IsSubstring(char *A, char *B); // KMP algorithm written by Wookje Kwon
void SearchBookName(Book *head, char *target, int searchType);
void AddBook(Book *head, Book book);
void RemoveBook(Book *head, int bookNum);
void lendBook(Book *head, int bookNum);
void returnBook(Book *head, int bookNum);
