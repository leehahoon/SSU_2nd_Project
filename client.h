#include "common.h"

typedef struct Client {
	struct Client * next;
	int stdNum;
	char *pw;
	char *name;
	char *address;
	char *dial;
} Client;

void strAllocate(char **chr, char *buf);
//구조체 멤버 변수 중, char 포인터형 변수 할당의 편의를 위한 함수
//char **chr : 메모리 및 문자열 값 할당을 위한 포인터 변수
//char *buf : 임시로 입력받는 문자열 변수

void AddClient(Client *head, Client *cli);
//Client 구조체를 관리함에 있어서 링크드리스트 노드를 추가하기 위한 함수
//Client *head : 관리하는 링크드리스트의 head 노드
//Client *cli : 가장 맨 뒤에 추가하려는 Client 구조체

void DeleteClient(Client *head, int stdNum);
//Client *head : 관리하는 링크드리스트의 head 노드
//int stdNum : 삭제할 Client의 학번

void ModifyClient(Client *head, int stdNum);
//Client *head : 관리하는 링크드리스트의 head 노드
//int stdNum : 수정할 Client의 학번

int SearchClient(Client *head, int type);
//Client 정보 검색
//head : 관리하는 링크드리스트의 head 노드
//type : 검색 타입(1.이름 / 2.학번 / 3.전체)

void PrintClientInfo(Client *cli);
//Client 구조체의 정보 출력

void PrintClientNodes(Client *cli);
//Client 링크드리스트 노드 정보 출력

void ClientFile2Node(Client *head);
//Client 파일을 읽어 링크드리스트 노드로 변환

void ClientNode2File(Client *head);
//링크드리스트 노드를 Client 파일로 변환

int IsOverlapClient(Client *head, int stdNum);
//Client 파일에서 학번 중복 체크
//중복될 경우, return 1, 중복이 아닐 경우, return 0;

int RegisterClient(Client *head, Client *a);
//Client 회원가입 기능 함수
//학번, 비밀번호 등 입력받고 Client *a에 저장

int LoginClient(Client *head, char *stdNum, char *pw);
//Client 로그인 기능 함수
//int stdNum : 학번
//char *pw : 패스워드
