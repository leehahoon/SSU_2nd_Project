#include "common.h"

// Book을 관리할 구조체
typedef struct Book {
    struct Book *nxt;		// 구조체 포인터
    char lendAble;			// 대여 가능 여부: 'Y', 'N'
    char *author;			// 저자명
    char *bookName;			// 책 이름
    char *location;			// 위치
    char *publish;			// 출판사
    long long isbn;		    // ISBN
    int bookNum;			// 책 번호
} Book;


// 건드리지 마세요
void PrintBookInfo(Book *cur);
int IsSubstring(char *A, char *B); // KMP algorithm written by Wookje Kwon

// 아래부터 가져다 쓰면 되는 함수들
// *head는 항상 구조체 포인터

/*********************************************************
 * *target: 검색할 문자열 포인터
 * ISBN이 long long임에 유의
 * ISBN으로 검색하는 경우: *target은 아무거나, targetIsbn에 값 전달
 * 그 외의 경우: *target에 검색할 거, targetIsbn에 아무거나
 * searchType: 1도서명, 2출판사, 3ISBN, 4저자명, 5전체
 * searchType: 5의 경우 target은 아무거나 넣어주면 됨
**********************************************************/
void SearchBook(Book *head, char *target, long long targetIsbn, int searchType);


/*********************************************************
 * book: 추가할 책의 정보를 담은 구조체
**********************************************************/
void AddBook(Book *head, Book book);


/*********************************************************
 * bookNum: 삭제할 책의 책 번호
**********************************************************/
void RemoveBook(Book *head, int bookNum);


/*********************************************************
 * bookNum: 대여할 책의 책 번호
**********************************************************/
void lendBook(Book *head, int bookNum);


/*********************************************************
 * bookNum: 반납할 책의 책 번호
**********************************************************/
void returnBook(Book *head, int bookNum);


/*********************************************************
 * 파일 불러오기
**********************************************************/
void BookFile2Node(Borrow *head);


/*********************************************************
 * 파일 저장하기
**********************************************************/
void BookNode2File(Borrow *head);
