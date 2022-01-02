#pragma once
typedef struct costomer {
	char name[40];
	char idcard[20];
	char phonenumber[20];
}Costomer;
typedef struct room {
	char roomnumber[10];
	char type[10];
	int flag;
	Costomer u;
	struct room* rnext;

}Room;
typedef struct order {
	Room* room_;
	int hour[2];
	int day[2];
	int mon[2];
	int year[2];
	struct order* onext;
}Order;
typedef struct administrator {
	char username[20];
	char password[20];
}Administrator;
