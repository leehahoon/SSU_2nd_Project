#include "borrow.h"

void AddBorrow(Borrow *head, Borrow *brw){
	Borrow * p = head;
	Borrow *newNode = (Borrow*)malloc(sizeof(Borrow));

	while(head->next != NULL){
		head = head->next;
	}

	newNode->next = head->next;

	newNode->stdNum = brw->stdNum;
	newNode->bookNum = brw->bookNum;
	newNode->lendDate = brw->lendDate;
	newNode->returnDate = brw->returnDate;

	head->next = newNode;
	BorrowNode2File(p);
}

void DeleteBorrow(Borrow *head, int bookNum){
	Borrow *p = head;
	while(head->next->bookNum != bookNum){
		head = head->next;
	}

	Borrow *removeNode = head->next;
	head->next = removeNode->next;

	free(removeNode);
	BorrowNode2File(p);
}

void LendList(Borrow *head, int stdNum) {
	Borrow *p = head->next;
	while(p->next != NULL){
		if(p->stdNum == stdNum) {
			PrintBorrowInfo(p);
		}
		p = p->next;
	}
}

void BorrowFile2Node(Borrow *head) {
	FILE * fp = fopen("txt_files/borrow.txt", "r");
	Borrow * brw = (Borrow*)malloc(sizeof(Borrow));
	
	while(fscanf(fp, "%d|%d|%ld|%ld\n", &brw->stdNum, \
		&brw->bookNum, &brw->lendDate, &brw->returnDate)!=EOF){

		AddBorrow(head, brw);
	}
}

void BorrowNode2File(Borrow *head) {
	FILE * fp = fopen("txt_files/borrow.txt", "w");
	Borrow *p = head->next;
	while(p != NULL) {
		fprintf(fp, "%08d|%d|%ld|%ld\n", p->stdNum, p->bookNum, p->lendDate, p->returnDate);
		p = p->next;
	}

	fclose(fp);
}

time_t getReturnDate(time_t lend_date){
	struct tm * t;
	time_t return_date = time(NULL) + (24 * 60 * 60)*30;
	t = localtime(&return_date);

	if(t->tm_wday == 0) {
		return_date = time(NULL) + (24 * 60 * 60)*31; 
	}
	return return_date;
}

char* getDay(struct tm *t){
	char *day;
	switch(t->tm_wday) {
		case 0:
			day = "일요일";
			break;
		case 1:
			day = "월요일";
			break;
		case 2:
			day = "화요일";
			break;
		case 3:
			day = "수요일";
			break;
		case 4:
			day = "목요일";
			break;
		case 5:
			day = "금요일";
			break;
		default:
			day = "토요일";
	}
	return day;
}

void PrintBorrowInfo(Borrow *brw) {
	struct tm * lend_t = localtime(&brw->lendDate);
	struct tm * return_t;

	printf("================\n");
	printf("학번 : %d\n", brw->stdNum);
	printf("도서 번호 : %d\n", brw->bookNum);
	printf("대여 일자 : %d년  %d월 %d일 %s\n", lend_t->tm_year + 1900, lend_t->tm_mon + 1, \
		lend_t->tm_mday, getDay(lend_t));

	return_t = localtime(&brw->returnDate);

	printf("반납 일자 : %d년  %d월 %d일 %s\n", return_t->tm_year + 1900, return_t->tm_mon + 1, \
		return_t->tm_mday, getDay(return_t));
	printf("================\n");
}

void PrintBorrowNodes(Borrow *brw) {
	Borrow *p = brw->next;
	while(p != NULL) {
		PrintBorrowInfo(p);
		p = p->next;
	}
	puts("");
}
