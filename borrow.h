#include "common.h"

typedef struct Borrow {
	struct Borrow *next;
	int stdNum;
	int bookNum;
	time_t lendDate;
	time_t returnDate;
} Borrow;

void AddBorrow(Borrow *head, Borrow *brw);
//Borrow 구조체에 Node 추가
//Borrow *head : 관리하는 링크드리스트의 head 노드
//Borrow *brw : 추가할 Borrow 노드
//개발자: 장재훈

void DeleteBorrow(Borrow *head, int bookNum);
//해당하는 bookNum의 Node 정보를 삭제
//Borrow *head : 관리하는 링크드리스트의 head 노드 
//개발자: 장재훈

void BorrowFile2Node(Borrow *head);
//Borrow 파일을 읽어 링크드리스트 노드로 변환
//개발자: 장재훈

void BorrowNode2File(Borrow *head);
//링크드리스트 노드를 Borrow 파일로 변환
//개발자: 장재훈

time_t getReturnDate(time_t lend_date);
//도서의 반납 일자 리턴
//time_t lend_date : 대여 일자
//개발자: 장재훈

char* getDay(struct tm *t);
//함수의 인자로 받은 tm 구조체가 몇요일인지 return
//개발자: 장재훈

void PrintBorrowInfo(Borrow *brw, char *bookName);
//Borrow 구조체 정보 출력
//개발자: 장재훈

void PrintBorrowNodes(Borrow *brw);
//Borrow 링크드리스트 노드 출력
//개발자: 장재훈

int IsDelete(Borrow *brw, int stdNum);
//현재 회원탈퇴가 가능한 회원인지 검사
//만약, 대여중인 도서가 있는 회원이라면, 0을 리턴
//대여중인 도서가 없고 탈퇴 가능하다면, 1을 리턴
//Borrow *brw : 관리하는 링크드리스트의 head 노드 
//int stdNum : 회원탈퇴 가능여부를 검사할 회원의 학번
//개발자: 장재훈
