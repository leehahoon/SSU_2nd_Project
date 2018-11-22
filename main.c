#include "client.h"
#include "book.h"
#include "borrow.h"
#include "utils.h"

int exit_flag = 0;
int main(){
	int menu;
	char *stdNum;
	char *pw;
	Client * cli_head = (Client*)malloc(sizeof(Client));
	Book * book_head = (Book*)malloc(sizeof(Book));
	Borrow * brw_head = (Borrow*)malloc(sizeof(Borrow));

	cli_head->next = NULL;
	book_head->nxt = NULL;
	brw_head->next = NULL;

	ClientFile2Node(cli_head);
	BorrowFile2Node(brw_head);

	while(!exit_flag) {
		puts(">> 도서관 서비스 <<");
		puts("1. 회원 가입\t2. 로그인\t3. 프로그램 종료");
		printf("번호를 선택하세요 : "); scanf("%d", &menu);

		switch(menu) {
			case 1:
				puts(">> 회원 가입 <<");
				puts("학번, 비밀번호, 이름, 주소, 전화번호를 입력하세요.\n");
				Client * regis = (Client*)malloc(sizeof(Client));
				if(!RegisterClient(cli_head, regis)) puts("회원가입에 실패하셨습니다.");
				puts("회원가입에 성공하셨습니다.");
				free(regis);
				sleep(1); system("clear");
				break;

			case 2:
				puts(">> 로그인 <<");
				int login_flag;
				stdNum = (char *)malloc(50);
				pw = (char *)malloc(50);

				printf("학번 : "); scanf("%s", stdNum);
				printf("비밀번호 : "); scanf("%s", pw);

				login_flag = LoginClient(cli_head, stdNum, pw);
				if(login_flag == 1) {
					puts("회원 로그인에 성공하셨습니다.");
					sleep(1); system("clear");
					MemberMenu();
				} else if(login_flag == 2) {
					puts("관리자 로그인에 성공하셨습니다.");
					sleep(1); system("clear");
					AdminMenu();
				} else puts("로그인에 실패하셨습니다.");

				free(pw);
				sleep(1); system("clear");
				break;

			case 3:
				puts("프로그램이 종료됩니다.");
				exit_flag = 1;
				break;

			default:
				puts("잘못된 입력입니다.");
				sleep(1); system("clear");
				break;
		}
	}
	return 0;
}