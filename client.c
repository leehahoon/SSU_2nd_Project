#include "client.h"

void strAllocate(char **chr, char *buf){
	*chr = malloc(sizeof(char) * strlen(buf)-1);
	strcpy(*chr, buf);
}

void AddClient(Client *head, Client *cli){
	Client * p = head;
	Client *newNode = (Client*)malloc(sizeof(Client));

	while(head->next != NULL && head->next->stdNum < cli->stdNum){
		head = head->next;
	}

	newNode->next = head->next;

	newNode->stdNum = cli->stdNum;
	newNode->pw = cli->pw;
	newNode->name = cli->name;
	newNode->address = cli->address;
	newNode->dial = cli->dial;

	head->next = newNode;
	ClientNode2File(p);
}

void DeleteClient(Client *head, int stdNum){
	Client *p = head;
	while(head->next->stdNum != stdNum){
		head = head->next;
	}

	Client *removeNode = head->next;
	head->next = removeNode->next;

	free(removeNode);
	ClientNode2File(p);
}

void ModifyClient(Client *head, int stdNum){
	char buf[100];

	Client *cli = head->next;
	while(cli->next->stdNum != stdNum){
		cli = cli->next;
	}

	if(cli->next == NULL) {
		puts("회원 정보 X");
		return;
	}
	cli = cli->next;
	free(cli->pw); free(cli->address); free(cli->dial);

	puts(">> 회원정보 수정 <<");
	printf("비밀번호 : "); scanf(" %[^\n]", buf);
	strAllocate(&cli->pw, buf);

	printf("주소 : "); scanf(" %[^\n]", buf);
	strAllocate(&cli->address, buf);

	printf("전화번호 : "); scanf(" %[^\n]", buf);
	strAllocate(&cli->dial, buf);

	ClientNode2File(head);

}

int SearchClient(Client *head, int type){
	char input[100];
	Client *p = head->next;
	
	printf("입력 : ");
	scanf(" %[^\n]", input);

	while(p != NULL) {
		switch(type){
			case 1:
				if(!strcmp(p->name, input)){
					PrintClientInfo(p);
					return 0;
				}
				break;

			case 2:
				if(p->stdNum == atoi(input)){
					PrintClientInfo(p);
					return 0;
				}
				break;

			case 3:
				if(p->stdNum ==atoi(input) || !strcmp(p->name, input) \
					|| !strcmp(p->address, input) || !strcmp(p->dial, input)){
					PrintClientInfo(p);
					return 0;
				}
				break;

			default:
				break;

		}
		p = p->next;
	}
	puts("결과 없음"); 
	return 1;
}

void PrintClientInfo(Client *cli) {
		printf("================\n");
		printf("학번 : %d\n", cli->stdNum);
		printf("비밀번호 : %s\n", cli->pw);
		printf("이름 : %s\n", cli->name);
		printf("주소 : %s\n", cli->address);
		printf("전화번호 : %s\n", cli->dial);
		printf("================\n");
}

void PrintNodes(Client *cli) {
	Client *p = cli->next;
	while(p != NULL) {
		PrintClientInfo(p);
		p = p->next;
	}
	puts("");
}

void ClientFile2Node(Client *head) {
	FILE * fp = fopen("client_example.txt", "r");
	Client * cli = (Client*)malloc(sizeof(Client));
	char *buf[4];

	for(int i=0;i<4;i++) buf[i] = (char*)malloc(100);
	
	while(fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%[^\n]", &cli->stdNum, \
		buf[0],buf[1],buf[2],buf[3])!=EOF){
	
		strAllocate(&cli->pw, buf[0]);
		strAllocate(&cli->name, buf[1]);
		strAllocate(&cli->address, buf[2]);
		strAllocate(&cli->dial, buf[3]);

		AddClient(head, cli);
	}

	for(int i=0;i<4;i++) free(buf[i]);
	fclose(fp);
}

void ClientNode2File(Client *head) {
	FILE * fp = fopen("client_example.txt", "w");
	Client *p = head->next;
	while(p != NULL) {
		fprintf(fp, "%08d|%s|%s|%s|%s\n", p->stdNum, p->pw, p->name, p->address, p->dial);
		p = p->next;
	}

	fclose(fp);
}

int IsOverlapClient(Client *head, int stdNum){
	Client *p = head->next;
	while(p != NULL) {
		if(p->stdNum == stdNum) return 1;
		p = p->next;
	}

	return 0;
}

int RegisterClient(Client *head, Client *cli){
	char buf[100];
	Client *head_bak = head;
	printf("학번 : "); scanf("%d", &cli->stdNum);

	if(IsOverlapClient(head, cli->stdNum)) {
		printf("중복된 학번입니다.\n");
		return 1;
	}
	
	printf("비밀번호 : "); scanf(" %[^\n]", buf);
	strAllocate(&cli->pw, buf);
	
	printf("이름 : "); scanf(" %[^\n]", buf);
	strAllocate(&cli->name, buf);

	printf("주소 : "); scanf(" %[^\n]", buf);
	strAllocate(&cli->address, buf);

	printf("전화번호 : "); scanf(" %[^\n]", buf);
	strAllocate(&cli->dial, buf);

	AddClient(head, cli);
	ClientNode2File(head_bak);
	return 0;
}

int LoginClient(Client *head, char *stdNum, char *pw){
	if(!strcmp(stdNum, "admin")) return 2;
	Client *p = head->next;
	while(p != NULL) {
		if(p->stdNum == atoi(stdNum) && !strcmp(p->pw, pw)) return 1;
		p = p->next;
	}
	return 0;
}
