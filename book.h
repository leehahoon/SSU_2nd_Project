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
 * 도서번호로 검색하는 경우: *target은 아무거나, targetIsbn에 도서번호 입력
 * 그 외의 경우: *target에 검색할 거, targetIsbn에 아무거나
 * searchType: 1도서명, 2출판사, 3ISBN, 4저자명, 5전체, 6도서번호
 * searchType: 5의 경우 target은 아무거나 넣어주면 됨
 * return 0: 찾는 책이 없음
 * return 1: 찾는 책이 있고 lendAble이 'Y'임
 * return 2: lendAble에 관계 없이 찾는 책이 있음
 * 개발자: 권욱제
**********************************************************/
int SearchBook(Book *head, char *target, long long targetIsbn, int searchType, int isPrint);


/*********************************************************
 * 책을 추가하는 함수
 * book: 추가할 책의 정보를 담은 구조체
 * 개발자: 권욱제
**********************************************************/
void AddBook(Book *head, Book book);


/*********************************************************
 * 책을 삭제하는 함수
 * bookNum: 삭제할 책의 책 번호
 * 개발자: 권욱제
**********************************************************/
void RemoveBook(Book *head, int bookNum);


/*********************************************************
 * 책을 빌리는 함수
 * bookNum: 대여할 책의 책 번호
 * 책을 빌릴 수 없으면(이미 빌림, 책이 없음) return 1
 * 외에는 빌림으로 처리하고 return 0
 * 개발자: 권욱제
**********************************************************/
int lendBook(Book *head, int bookNum);


/*********************************************************
 * 책을 반납하는 함수
 * bookNum: 반납할 책의 책 번호
 * 책을 반납할 수 없으면(이미 빌림, 책이 없음) return 1
 * 외에는 반납으로 처리하고 return 0
 * 개발자: 권욱제
**********************************************************/
int returnBook(Book *head, int bookNum);


/*********************************************************
 * 파일 불러오기
 * 개발자: 권욱제
**********************************************************/
void BookFile2Node(Book *head);


/*********************************************************
 * 파일 저장하기
 * 개발자: 권욱제
**********************************************************/
void BookNode2File(Book *head);


/*********************************************************
 * 책 번호 입출력
 * 개발자: 권욱제
**********************************************************/
int ReadBookNum();
void WriteBookNum(int num);
