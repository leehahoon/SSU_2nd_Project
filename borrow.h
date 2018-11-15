#include "common.h"

struct BORROW {
	struct BORROW *next;
	int stuNum;
	int bookNum;
	time_t lendDate;
	time_t returnDate;
};

