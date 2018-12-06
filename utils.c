#include "client.h"
#include "book.h"
#include "borrow.h"
#include "utils.h"

extern int exit_flag;
extern Client * cli_head;
extern Book * book_head;
extern Borrow * brw_head;

void MemberMenu(int stdNum){
	int menu;
	int searchtype;
	char *searching;
	long long isbn;
	while(1) {
		puts(">> 회원 메뉴 <<");
		puts("1. 도서 검색\t\t2. 내 대여 목록");
		puts("3. 개인정보 수정\t4. 회원 탈퇴");
		puts("5. 로그아웃\t\t6. 프로그램 종료");
		printf("번호를 선택하세요 : "); scanf("%d", &menu);
		puts("");

		switch(menu){
			case 1:
				puts(">> 도서 검색 <<");
				printf("1. 도서명 검색\t\t2. 출판사 검색\n");
				printf("3. ISBN 검색\t\t4. 저자명 검색\n");
				printf("5. 전체 검색\t\t6. 이전 메뉴\n");
				printf("번호를 선택하세요 : "); scanf("%d", &searchtype);
				if (searchtype == 1)
				{
					searching = (char *)malloc(50);
					printf("도서명을 입력하십시오 : "); scanf(" %[^\n]", searching);
					SearchBook(book_head, searching, 11, 1, 1);
					free(searching);
				}
				else if (searchtype == 2)
				{
					searching = (char *)malloc(50);
					printf("출판사를 입력하십시오 : "); scanf(" %[^\n]", searching);
					SearchBook(book_head, searching, 11, 2, 1);
					free(searching);
				}
				else if (searchtype == 3)
				{
					searching = (char *)malloc(50);
					printf("ISBN을 입력하십시오 : "); scanf("%lld", &isbn);
					SearchBook(book_head, "aa", isbn, 3, 1);
				}
				else if (searchtype == 4)
				{
					searching = (char *)malloc(50);
					printf("저자명을 입력하십시오 : "); scanf(" %[^\n]", searching);
					SearchBook(book_head, searching, 11, 4, 1);
					free(searching);
				}
				else if (searchtype == 5)
				{
					printf("전체 검색 결과\n");
					SearchBook(book_head, "aaa", 11, 5, 1);
				}
				else if (searchtype == 6)
				{
					;
				}
				else
					printf("잘못된 입력입니다");

				break;

			case 2:
				puts(">> 내 대여 목록 <<");
				int lendlist=0;
				Borrow *p = brw_head->next;
				Book *o = book_head->nxt;

				while(p != NULL){
					if(p->stdNum == stdNum) {
						o = book_head->nxt;
						while(o != NULL) {
							if(o->bookNum == p->bookNum) {
								PrintBorrowInfo(p, o->bookName);
								lendlist=1;
							}
							o = o->nxt;
						}
					}
					p = p->next;
				}
				if(!lendlist) puts("대여 목록이 없습니다.\n");
				
				break;

			case 3:
				puts(">> 개인정보 수정 <<");
				ModifyClient(cli_head, stdNum);
				break;

			case 4:
				puts(">> 회원 탈퇴 <<");
				if(IsDelete(brw_head, stdNum)){
					DeleteClient(cli_head, stdNum);
					puts("회원 탈퇴가 완료되었습니다.");
				}
				else puts("현재 대여중인 도서가 존재합니다.\n도서를 모두 반납한 후, 시도해주세요.\n");
				break;

			case 5:
				puts("초기 화면으로 이동합니다.");
				return;

			case 6:
				puts("프로그램이 종료됩니다.");
				exit_flag=1;
				return;

			default:
				puts("잘못된 입력입니다.");
		}
		puts("계속하려면 ENTER를 눌러주세요.");
		getchar(); getchar(); system("clear");
	}
}

void AdminMenu(){
	int menu;
	int lend_stdNum, lend_bookNum;
	int del_bookNum = 0;
	int bookNum = ReadBookNum();
	int cli_type;
	char author[100];
	char bookName[100];
	char location[100];
	char publish[100];
	char y_n;
	long long ISBN;
	Borrow *brw;
	Book book;

	while(1){
		puts(">> 관리자 메뉴 <<");
		puts("1. 도서 등록\t\t2. 도서 삭제");
		puts("3. 도서 대여\t\t4. 도서 반납");
		puts("5. 도서 검색\t\t6. 회원 목록");
		puts("7. 로그아웃\t\t8. 프로그램 종료");
		printf("번호를 선택하세요 : "); scanf("%d", &menu);
		puts("");

		switch(menu){
			case 1:
				puts(">> 도서 등록 <<");
				printf("도서명: "); scanf(" %[^\n]", bookName);
				printf("출판사: "); scanf(" %[^\n]", publish);
				printf("저자명: "); scanf(" %[^\n]", author);
				printf("ISBN: "); scanf(" %lld", &ISBN);
				printf("소장처: "); scanf(" %[^\n]", location);

				printf("\n자동입력 사항\n\n");

				printf("대여가능 여부: Y\n");
				printf("도서번호: %d\n\n", bookNum+1);

				char flag;
				printf("등록하시겠습니까?(Y/N) "); scanf(" %c", &flag);

				if (flag == 'Y' || flag == 'y') {
					bookNum++;
					WriteBookNum(bookNum);

					book.bookName = (char*)malloc(sizeof(char)*(strlen(bookName)+1));
					book.publish = (char*)malloc(sizeof(char)*(strlen(publish)+1));
					book.author = (char*)malloc(sizeof(char)*(strlen(author)+1));
					book.location = (char*)malloc(sizeof(char)*(strlen(location)+1));
					strcpy(book.bookName, bookName);
					strcpy(book.publish, publish);
					strcpy(book.author, author);
					strcpy(book.location, location);
					book.isbn = ISBN;
					book.lendAble = 'Y';
					book.bookNum = bookNum;

					AddBook(book_head, book);
					BookNode2File(book_head);

					puts("\n도서 등록이 완료 되었습니다.\n");
				}
				else {
					puts("\n도서 등록이 취소 되었습니다.\n");
				}

				break;

			case 2:
				puts(">> 도서 삭제 <<");
				puts("1. 도서명 검색\t\t2. ISBN 검색\n");

				printf("번호를 선택하세요 : "); scanf("%d", &menu);

				if (menu == 1) {
					printf("도서명 입력 : "); scanf(" %[^\n]", bookName);
					printf("\n >> 검색 결과 << \n");
					SearchBook(book_head, bookName, 0, 1, 1);
				}
				else {
					printf("ISBN 입력 : "); scanf(" %lld", &ISBN);
					printf("\n >> 검색 결과 << \n");
					SearchBook(book_head, "0", ISBN, 3, 1);
				}

				printf("\n삭제할 도서의 번호를 입력하세요: "); scanf("%d", &del_bookNum);

				int ret = SearchBook(book_head, "0", (long long)del_bookNum, 6, 0);

				if (ret == 1) {
					RemoveBook(book_head, del_bookNum);
					BookNode2File(book_head);

					printf("\n도서가 삭제 되었습니다.\n");
				}
				else {
					printf("\n이 도서는 삭제할 수 없습니다.\n");
				}

				break;

			case 3:
				puts(">> 도서 대여 <<");
				puts("1. 도서명 검색\t\t2. ISBN 검색");
				printf("번호를 선택하세요 : "); scanf("%d", &menu);
				if(menu == 1){
					printf("도서명 입력 : "); scanf(" %[^\n]", bookName);
					SearchBook(book_head, bookName, 0, 1, 1);
					printf("학번 입력 : "); scanf("%d", &lend_stdNum);
					printf("도서번호 입력 : "); scanf("%d", &lend_bookNum);
					printf("\n이 도서를 대여합니다? (Y/N) : "); scanf(" %c", &y_n);
					if(y_n == 'Y' || y_n == 'y'){
						if(!lendBook(book_head, lend_bookNum)){
							brw = (Borrow*)malloc(sizeof(Borrow));
							brw->stdNum = lend_stdNum;
							brw->bookNum = lend_bookNum;
							brw->lendDate = time(NULL);
							brw->returnDate = getReturnDate(brw->lendDate);

							AddBorrow(brw_head, brw);
							free(brw);
							puts("도서 대여가 완료되었습니다.\n");
						}
					}
					else puts("도서 대여가 취소되었습니다.\n");

				} else if(menu == 2) {
					printf("ISBN 입력 : "); scanf("%lld", &ISBN);
					SearchBook(book_head, "0", ISBN, 3, 1);
					printf("학번 입력 : "); scanf("%d", &lend_stdNum);
					printf("도서번호 입력 : "); scanf("%d", &lend_bookNum);
					printf("\n이 도서를 대여할까요? (Y/N) : "); scanf(" %c", &y_n);
					if(y_n == 'Y' || y_n == 'y'){
						if(!lendBook(book_head, lend_bookNum)){
							brw = (Borrow*)malloc(sizeof(Borrow));
							brw->stdNum = lend_stdNum;
							brw->bookNum = lend_bookNum;
							brw->lendDate = time(NULL);
							brw->returnDate = getReturnDate(brw->lendDate);

							AddBorrow(brw_head, brw);
							free(brw);
							puts("도서 대여가 완료되었습니다.\n");
						}
					}
					else puts("도서 대여가 취소되었습니다.\n");

				} else puts("잘못된 입력입니다.\n");

				break;

			case 4:
				puts(">> 도서 반납 <<");
				printf("학번 입력 : "); scanf("%d", &lend_stdNum);
				int lendlist=0;
				Borrow *p = brw_head->next;
				Book *o = book_head->nxt;

				puts("\n>> 회원의 대여 목록 <<\n");
				while(p != NULL){
					if(p->stdNum == lend_stdNum) {
						o = book_head->nxt;
						while(o != NULL) {
							if(o->bookNum == p->bookNum) {
								PrintBorrowInfo(p, o->bookName);
								lendlist=1;
							}
							o = o->nxt;
						}
					}
					p = p->next;
				}
				
				if(!lendlist) {
					puts("대여 목록이 없습니다.\n");
					break;
				}

				else {
					printf("반납할 도서번호를 입력하세요 : "); scanf("%d", &lend_bookNum);
					printf("\n도서 반납처리를 할까요? (Y/N) : "); scanf(" %c", &y_n);
					if(y_n == 'Y' || y_n == 'y'){
						if(!returnBook(book_head, lend_bookNum)){
							DeleteBorrow(brw_head, lend_bookNum);
							puts("도서 반납이 완료되었습니다.\n");
						}
					}
					else puts("도서 반납이 취소되었습니다.\n");
				}
				break;

			case 5:
				puts("도서 검색");
				break;

			case 6:
				puts(">> 회원 목록 <<");
				puts("1. 이름 검색\t\t2. 학번 검색");
				puts("3. 전체 검색\t\t4. 이전 메뉴");
				printf("번호를 선택하세요 : "); scanf("%d", &cli_type);
				if(cli_type < 4) 
					SearchClient(cli_head, cli_type);
				else puts("잘못된 입력입니다.\n");

				break;

			case 7:
				puts("초기 화면으로 이동합니다.");
				return;

			case 8:
				puts("프로그램이 종료됩니다.");
				exit_flag=1;
				return;

			default:
				puts("잘못된 입력입니다.");
		}
		puts("계속하려면 ENTER를 눌러주세요.");
		getchar(); getchar(); system("clear");
	}
}
