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

void DeleteBorrow(Borrow *head, int bookNum);
//해당하는 bookNum의 Node 정보를 삭제
//Borrow *head : 관리하는 링크드리스트의 head 노드 

Borrow* LendList(Borrow *head, int stdNum);
//해당하는 학번의 대여 목록을 출력
//Borrow *head : 관리하는 링크드리스트의 head 노드 
//int stdNum : 학번

void BorrowFile2Node(Borrow *head);
//Borrow 파일을 읽어 링크드리스트 노드로 변환

void BorrowNode2File(Borrow *head);
//링크드리스트 노드를 Borrow 파일로 변환

time_t getReturnDate(time_t lend_date);
//도서의 반납 일자 리턴
//time_t lend_date : 대여 일자

char* getDay(struct tm *t);
//해당하는 tm 구조체의 요일 return

void PrintBorrowInfo(Borrow *brw, char *bookName);
//Borrow 구조체 정보 출력

void PrintBorrowNodes(Borrow *brw);
//Borrow 링크드리스트 노드 출력

int IsDelete(Borrow *brw, int stdNum);
//현재 회원탈퇴가 가능한 회원인지 검사