void strAllocate(char **chr, char *buf){
	*chr = malloc(sizeof(char) * strlen(buf)-1);
	strcpy(*chr, buf);
}

void register_client(Client *a){
	char buf[100];

	printf("학번 : "); scanf("%d", &a->stdNum);
	
	printf("비밀번호 : "); scanf(" %[^\n]", buf);
	strAllocate(&a->pw, buf);
	
	printf("이름 : "); scanf(" %[^\n]", buf);
	strAllocate(&a->name, buf);

	printf("주소 : "); scanf(" %[^\n]", buf);
	strAllocate(&a->address, buf);

	printf("전화번호 : "); scanf(" %[^\n]", buf);
	strAllocate(&a->dial, buf);

}

void AddClient(Client *head, Client *cli){
	Client *newNode = (Client*)malloc(sizeof(Client));

	while(head->next != NULL){
		head = head->next;
	}

	head->next = newNode;

	newNode->stdNum = cli->stdNum;
	newNode->pw = cli->pw;
	newNode->name = cli->name;
	newNode->address = cli->address;
	newNode->dial = cli->dial;

	newNode->next = NULL;
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

void File2Node(Client *head) {
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
}
