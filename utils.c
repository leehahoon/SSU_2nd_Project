#include "utils.h"

extern int exit_flag;
void MemberMenu(){
	int menu;
	while(1) {
		puts(">> 회원 메뉴 <<");
		puts("1. 도서 검색\t\t2. 내 대여 목록");
		puts("3. 개인정보 수정\t4. 회원 탈퇴");
		puts("5. 로그아웃\t\t6. 프로그램 종료");
		printf("번호를 선택하세요 : "); scanf("%d", &menu);

		switch(menu){
			case 1:
				puts("도서 검색");
				break;

			case 2:
				puts("내 대여 목록");
				break;

			case 3:
				puts("개인정보 수정");
				break;

			case 4:
				puts("회원 탈퇴");
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
		sleep(1); system("clear");
	}
}

void AdminMenu(){
	int menu;
	int bookNum = 0;

	while(1){
		puts(">> 관리자 메뉴 <<");
		puts("1. 도서 등록\t\t2. 도서 삭제");
		puts("3. 도서 대여\t\t4. 도서 반납");
		puts("5. 로그아웃\t\t6. 프로그램 종료");
		printf("번호를 선택하세요 : "); scanf("%d", &menu);

		switch(menu){
			case 1:
				puts("도서 등록");
				bookNum++;
				break;

			case 2:
				puts("도서 삭제");
				break;

			case 3:
				puts("도서 대여");
				break;

			case 4:
				puts("도서 반납");
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
		sleep(1); system("clear");
	}
}
