#include "book.h"

void PrintBookInfo(Book *cur) {
    printf("\n-----------------------------\n");
    printf("* 도서번호: %d\n", cur->bookNum);
    printf("* 도서명: %s\n", cur->bookName);
    printf("* 출판사: %s\n", cur->publish);
    printf("* 저자명: %s\n", cur->author);
    printf("* ISBN: %lld\n", cur->isbn);
    printf("* 소장처: %s\n", cur->location);
    printf("* 대여가능 여부: %c\n", cur->lendAble);
    printf("-----------------------------\n");

    return;
}

int IsSubstring(char *A, char *B) {
    int aLen = strlen(A);
    int bLen = strlen(B);
	
    if (aLen < bLen) {
        return 0;
    }

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

void SearchBook(Book *head, char *target, long long targetIsbn, int searchType) {
    Book *cur = head;

    while (cur->nxt != NULL) {
        int flag = 0;
        char *temp;
        long long t_isbn;

        cur = cur->nxt;

        if (searchType == 1) {
            temp = cur->bookName;
        } else if (searchType == 2) {
            temp = cur->publish;
        } else if (searchType == 3) {
            t_isbn = cur->isbn;
        } else if (searchType == 4) {
            temp = cur->author;
        }

        if (searchType == 5) {
            flag = 1;
        } else if (searchType != 3) {
            flag = IsSubstring(temp, target);
        } else {
            flag = (targetIsbn == t_isbn);
        }


        if (flag) {
            PrintBookInfo(cur);
        }
    }

    return;
}

void AddBook(Book *head, Book book) {
    Book *cur = head;

    while (cur->nxt != NULL && cur->nxt->isbn < book.isbn) {
        cur = cur->nxt;
    }

    Book *end = cur->nxt;
    cur->nxt = (Book*)malloc(sizeof(Book));

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

int lendBook(Book *head, int bookNum) {
    Book *cur = head;

    while (cur->nxt != NULL && cur->nxt->bookNum != bookNum) {
        cur = cur->nxt;
    }

    if (cur->nxt == NULL) {
        printf("!!!!!! No Book #%d in DB !!!!!!\n", bookNum);
        return 1;
    }

    if (cur->nxt->lendAble == 'N') {
        printf("!!!!!! Book #%d has already been borrowed !!!!!!\n", bookNum);
        return 1;
    }

    cur->nxt->lendAble = 'N';
    BookNode2File(head);

    return 0;
}

int returnBook(Book *head, int bookNum) {
    Book *cur = head;

    while (cur->nxt != NULL && cur->nxt->bookNum != bookNum) {
        cur = cur->nxt;
    }

    if (cur->nxt == NULL) {
        printf("!!!!!! No Book #%d in DB !!!!!!\n", bookNum);
        return 1;
    }

    if (cur->nxt->lendAble == 'Y') {
        printf("!!!!!! Book #%d has not been borrowed !!!!!!\n", bookNum);
        return 1;
    }

    cur->nxt->lendAble = 'Y';
    BookNode2File(head);

    return 0;
}

void BookFile2Node(Book *head) {
    FILE * fp = fopen("txt_files/book.txt", "r");
    Book book;
	
    char buf[4][301];

    while (fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%lld|%[^|]|%c\n", &book.bookNum, buf[0],
                buf[1], buf[2], &book.isbn, buf[3], &book.lendAble) != EOF){
        book.bookName = (char*)malloc(sizeof(char)*(strlen(buf[0])+1));
        book.publish = (char*)malloc(sizeof(char)*(strlen(buf[1])+1));
        book.author = (char*)malloc(sizeof(char)*(strlen(buf[2])+1));
        book.location = (char*)malloc(sizeof(char)*(strlen(buf[3])+1));
        strcpy(book.bookName, buf[0]);
        strcpy(book.publish, buf[1]);
        strcpy(book.author, buf[2]);
        strcpy(book.location, buf[3]);

        AddBook(head, book);
    }

    fclose(fp);
    return;
}

void BookNode2File(Book *head) {
    FILE * fp = fopen("txt_files/book.txt", "w");
    Book * p = head->nxt;
    while (p != NULL) {
        fprintf(fp, "%07d|%s|%s|%s|%lld|%s|%c\n", p->bookNum,
                p->bookName, p->publish, p->author, p->isbn, p->location, p->lendAble);
        p = p->nxt;
    }

    fclose(fp);

    return;
}

void ReadBookNum() {
    int num;
    FILE * fp = fopen("txt_files/book_num.txt", "r");

    fscanf(fp, "%d", &num);

    fclose(fp);

    return num;
}

void WriteBookNum(int num) {
    FILE * fp = fopen("txt_files/book_num.txt", "w");
    fprintf(fp, "%d", num);

    fclose(fp);

    return num;
}