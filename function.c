#include "function.h"
#include <stdlib.h >
#include "struct.h"
#include <string.h>
#include <time.h>
#include <windows.h>
#include <stdio.h>
extern Room* rhead;
extern Order* ohead;
void registers() {
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	char s[15], c[15];
	FILE* fp = fopen("password.txt", "r");
	if (fp == NULL) {
		printf("Failed to open file");
	}
	fgets(s, 14, fp);//读出文件中的密码
	fclose(fp);
	color1();//根据之前修改的颜色更新系统颜色
	printf("\n请输入登录密码:");
	gets(c);
	while (strcmp(c, s) != 0) { //判断密码是否正确，不正确的话重新输入。
		printf("\n密码错误请重试");
		gets(c);
	}
	if (strcmp(c, s) == 0) {
		read_();
		while (1)
		{

			system("cls");//清空界面
			color1();//根据之前修改的颜色更新系统颜色
			printf("\n\n\n\n");
			printf(" ***********************************************\n");
			printf(" ^_^  ^_^  ^_^  ^_^  ^_^  ^_^  ^_^  ^_^  ^_^ ^_^\n");
			printf(" ***********************************************\n");
			printf("_______________________________________________\n");
			printf("┃                                            ┃\n");
			printf("┃              酒店预约管理系统              ┃\n");
			printf("┃            欢迎来到白山黑水酒店！          ┃\n");
			printf("┃            现在是%d年", 1900 + p->tm_year);/*获取当前年份,从知1900开始，所以要加1900*/
			printf("%d月", 1 + p->tm_mon);/*获取当前月份,范围是0-11,所以要加1*/
			printf("%d日", p->tm_mday);/*获取当前月份日数,范围是1-31*/
			printf("%d时", 8 + p->tm_hour);/*获取当前时,这里获取西方的时百间,刚好相差八个度小时*/
			printf("         ┃\n");
			printf("┃                                            ┃\n");
			printf("┃                                            ┃\n");
			printf("┃____________________________________________┃\n");
			printf("***********************************************\n");
			printf("***********************************************\n");
			printf("**            1.客户入住信息登记             **\n");
			printf("**            2.修改背景颜色                 **\n");
			printf("**            3.修改密码                     **\n");
			printf("**            4.查询信息                     **\n");
			printf("**            5.修改订单信息                 **\n");
			printf("**            6.删除订单                     **\n");
			printf("**            7.统计信息                     **\n");
			printf("**            8.备份                         **\n");
			printf("**            9.退出并保存                   **\n");
			printf("***********************************************\n");
			printf("***********************************************\n");
			printf("***********************************************\n");
			printf("^_^  ^_^  ^_^  ^_^  ^_^  ^_^  ^_^  ^_^  ^_^ ^_^\n");
			printf("***********************************************\n");
			printf("               选择操作：");
			int m;
			char t[20];
			scanf("%d", &m);
			while (m < 1 || m>9) { printf("\n请按要求输入"); scanf("%d", &m); }
			if (m== 9)
			{
				saveorder();
				saveroom();
			}
			switch (m) {
			case 1: { chooseroomtype(); break; }
			case 2: {changecolor1(); break; }
			case 3:changeKEY(); break;
			case 4: { {system("cls");
				printf("选择查询类别：\n");
				printf("1.查询房间信息\n");
				printf("2.查询订单信息\n");
				printf("输入选项：");
				gets(t);
				while ((strcmp(t, "1") != 0) && (strcmp(t, "2") != 0)) {
					printf("\n请按要求输入\n");
					gets(t);
					fflush(stdin);
				}
				if ((strcmp(t, "1") == 0))search1();//查询房间
				if ((strcmp(t, "2") == 0))search2();//查询订单
				}; break; }
			case 5: {changeorder(); break; }
			case 6: {deleteorder(); break; }
			case 7: {statistics(); break; }
			case 8: {backups(); break; }
			case 9: {exit(0); break; }
			 
			}
		}

	}
}
Room* readroom()//从文件里面读出来room放到链表里面
{
	FILE* fp = NULL;
	char ch;
	Room* rhead;
	rhead = (Room*)malloc(sizeof(Room));
	if (rhead != NULL)
	{
		rhead->rnext = NULL;
	}
	Room* p = rhead;
	Room* q = rhead;
	if ((fp = fopen("room.txt", "r+")) == NULL)
	{
		printf("can't open the file\n");
		system("pause");
		return NULL;
	}
	while (!feof(fp))
	{
		p = (Room*)malloc(sizeof(Room));
		fgets(p->roomnumber, 20, fp);//读进来的还有换行符
		//printf("%s\n",p->roomnumber);
		fgets(p->type, 20, fp);//读进来的还有换行符
		//printf("%s\n",p->type);
		fscanf(fp, "%d", &(p->flag));
		//printf("%d\n",p->flag);
		ch = fgetc(fp);
		ch = fgetc(fp);
		q->rnext = p;
		q = p;
	}
	q->rnext = NULL;
	fclose(fp);
	return rhead;//返回指针的头
}
void saveroom() {
	FILE* fp = NULL;
	Room* p = rhead->rnext;
	if ((fp = fopen("room.txt", "w")) == NULL)
	{
		printf("can't open the room file\n");
		system("pause");
	}

	while (p != NULL) {
		fputs(p->roomnumber, fp);
		fputs(p->type, fp);
		fprintf(fp, "%d", p->flag);
		fputc('\n', fp);
		if (p->rnext != NULL)fputc('\n', fp);
		p = p->rnext;
	}
	fclose(fp);
}
void emptyroom(char roomnumber_[10])//清空一个房间
{
	Room* p = rhead->rnext;
	while (p != NULL) {
		if (strcmp(roomnumber_, p->roomnumber) == 0) {
			p->flag = 0;
			break;
		}
		p = p->rnext;

	}
}
int judgeid(char t[])
{
	int flag = 0;
	int i = 0;
	for (i = 0; i < 18; i++) {
		if (i <= 16)
			if (t[i] < '9' && t[i]>'0')flag = 0;
			else flag = 1;
		if (i == 17)
			if (t[i] == 'X' || (t[i] < '9' && t[i]>'0'))
				flag = 0;
			else flag = 1;
	}
	return flag;//身份证号码符合规则的话返回0，else返回1.
}
int judgephone(char t[]) {
	int flag = 0;
	int i = 0;
	for (i = 0; i < 11; i++) {

		if (t[i] <= '9' && t[i] >= '0')flag = 0;
		else flag = 1;
	}
	return flag;//电话号符合规则的话返回0，else返回1.
}
Order* exploitorderhead() {
	ohead = (Order*)malloc(sizeof(Order));
	if (ohead != NULL)
	{
		ohead->onext = NULL;
		return ohead;
	}
	else
		printf("开辟订单头失败\n");
}
void chooseroomtype() {
	char c[20];
	char choice[10];
	while (1) {
		system("cls");
		printf("房间类型:\n");
		printf("1.single\n");
		printf("2.double\n");
		printf("3.triple\n");
		printf("4.four\n");
		printf("5.返回上一层\n");
		printf("请输入你的选择:");
		fflush(stdin);
		rewind(stdin);
		gets(c);
		while ((strcmp(c, "1") != 0) && (strcmp(c, "2") != 0) && (strcmp(c, "3") != 0) && (strcmp(c, "4") != 0) && (strcmp(c, "5") != 0)) {
			printf("选择有误，请重新输入:");
			gets(c);
		}
		{
			if (strcmp(c, "1") == 0) {
				strcpy(choice, "single\n");
				openroom(choice);
			}
			if (strcmp(c, "2") == 0) {
				strcpy(choice, "double\n");
				openroom(choice);
			}
			if (strcmp(c, "3") == 0) {
				strcpy(choice, "triple\n");
				openroom(choice);
			}
			if (strcmp(c, "4") == 0) {
				strcpy(choice, "four\n");
				openroom(choice);
			}
			if (strcmp(c, "5") == 0) {
				break;
				system("pause");
			}
		}
	}

}
void inquirevacant(char c[])
{
	int flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;
	Room* p = rhead;
	while (p != NULL) {
		if (p->flag == 0) {
			if (strcmp(p->type, "single\n") == 0)
				flag1++;
			if (strcmp(p->type, "double\n") == 0)
				flag2++;
			if (strcmp(p->type, "triple\n") == 0)
				flag3++;
			if (strcmp(p->type, "four\n") == 0)
				flag4++;
		}
		p = p->rnext;

	}
	if (strcmp(c, "single\n") == 0)
	{
		if (flag1 >= 1) {
			printf("房间类型选择成功\n");
			openroom(c);
		}
		else
		{
			printf("抱歉，该类房间没有空房，请重新选择");
			system("pause");
			system("cls");
			chooseroomtype();

		}
	}
	if (strcmp(c, "double\n") == 0)
	{
		if (flag2 >= 1) {
			printf("房间类型选择成功\n");
			openroom(c);
		}
		else
		{
			printf("抱歉，该类房间没有空房，请重新选择");
			system("pause");
			system("cls");
			chooseroomtype();
		}
	}
	if (strcmp(c, "triple\n") == 0)
	{
		if (flag3 >= 1) {
			printf("房间类型选择成功\n");
			openroom(c);
		}
		else
		{
			printf("抱歉，该类房间没有空房，请重新选择");
			system("pause");
			system("cls");
			chooseroomtype();
		}
	}
	if (strcmp(c, "four\n") == 0)
	{
		if (flag4 >= 1) {
			printf("房间类型选择成功\n");
			openroom(c);
		}
		else
		{
			printf("抱歉，该类房间没有空房，请重新选择");
			system("pause");
			system("cls");
			chooseroomtype();
		}
	}
}
void openroom(char t[]) {
	Room* p = rhead;
	Order* op = ohead;
	while (op->onext != NULL) {
		op = op->onext;
	}//找到指针末尾。
	Order* oop = (Order*)malloc(sizeof(Order));
	op->onext = oop;
	oop->onext = NULL;
	char id[40];
	char phonenumber_[20];
	while (p != NULL) {
		if (p->flag == 0 && strcmp(p->type, t) == 0) {
			p->flag = 1;
			oop->room_ = p;
			printf("请输入房主姓名：");
			fflush(stdin);
			rewind(stdin);
			scanf("%s", p->u.name);
			checkchar1(p->u.name);//加上\n方便以后判断
			printf("请输入18位的身份证号码：");
			fflush(stdin);
			rewind(stdin);
			scanf("%s", id);
			while (strlen(id) != 18 || judgeid(id) != 0) {//判断身份证号是否符合规则。
				printf("身份证号码格式有误，请重新输入:");
				fflush(stdin);
				rewind(stdin);
				scanf("%s", id);
			}
			checkchar1(id);//加上\n方便以后判断
			strcpy(p->u.idcard, id);
			printf("请输入11位电话号：");
			fflush(stdin);
			rewind(stdin);
			scanf("%s", phonenumber_);
			while (strlen(phonenumber_) != 11 || judgephone(phonenumber_) != 0)
			{//判断电话号号是否符合规则。
				printf("电话号不符合要求，请重新输入:");
				fflush(stdin);
				rewind(stdin);
				scanf("%s", phonenumber_);
			}
			checkchar1(phonenumber_);//加上\n方便以后判断
			strcpy(p->u.phonenumber, phonenumber_);
			printf("请输入入住时间：年月日时(24时）中间请用/隔开：");
			fflush(stdin);
			rewind(stdin);
			while ((scanf("%d/%d/%d/%d", &oop->year[0], &oop->mon[0], &oop->day[0], &oop->hour[0])) != 4 || Check_date1(oop->year, oop->mon, oop->day, oop->hour) != 0) {//判断日期是否大于当前日期
				printf("日期输入有误，");
				printf("请重新输入入住时间：年月日时(24时）中间请用/隔开：");
				fflush(stdin);
				rewind(stdin);
			}
			printf("请输入离开时间：年月日时(24时）中间请用/隔开：");
			fflush(stdin);
			rewind(stdin);
			while ((scanf("%d/%d/%d/%d", &oop->year[1], &oop->mon[1], &oop->day[1], &oop->hour[1])) != 4 || Check_date2(oop->year, oop->mon, oop->day, oop->hour) != 0) {//判断离开日期是否入住当前日期
				printf("日期输入有误，");
				printf("请重新输入离开时间：年月日时(24时）中间请用/隔开：");
			}
			printf("您的房间号码：%s", p->roomnumber);
			printf("创建订单成功\n");
			fflush(stdin);
			rewind(stdin);
			break;
		}
		p = p->rnext;
	}
	system("pause");
}
void showroomtype() {
	system("cls");
	printf("房间类型:\n");
	printf("1.single\n");
	printf("2.double\n");
	printf("3.triple\n");
	printf("4.four\n");
}
void saveorder() {
	FILE* fp = NULL;
	if ((fp = fopen("order.txt", "w")) == NULL)
	{
		printf("can't built the order file\n");
		system("pause");
	}
	Order* p = ohead->onext;
	while (p != NULL) {
		fputs(p->room_->roomnumber, fp);//连换行符一起保存
		fputs(p->room_->type, fp);//连换行符一起保存
		fputs(p->room_->u.name, fp);//连换行符一起保存
		fputs(p->room_->u.idcard, fp);//连换行符一起保存
		fputs(p->room_->u.phonenumber, fp);//连换行符一起保存
		fprintf(fp, "%d", p->year[0]);
		fputc('/', fp);
		fprintf(fp, "%d", p->mon[0]);
		fputc('/', fp);
		fprintf(fp, "%d", p->day[0]);
		fputc('/', fp);
		fprintf(fp, "%d", p->hour[0]);
		fputc('\n', fp);
		fprintf(fp, "%d", p->year[1]);
		fputc('/', fp);
		fprintf(fp, "%d", p->mon[1]);
		fputc('/', fp);
		fprintf(fp, "%d", p->day[1]);
		fputc('/', fp);
		fprintf(fp, "%d", p->hour[1]);
		fputc('\n', fp);
		if (p->onext != NULL)fputc('\n', fp);
		p = p->onext;
	}
	fclose(fp);

}
Order* readorder() {
	FILE* fp = NULL;
	char ch;
	Order* ohead = exploitorderhead();
	Order* p = ohead;
	Order* q = ohead;
	Room* u;
	if ((fp = fopen("order.txt", "r+")) == NULL)
	{
		printf("can't open the file\n");
		system("pause");
		return NULL;
	}
	ch = fgetc(fp);
	if (!feof(fp)) {
		rewind(fp);
		while (!feof(fp))
		{
			p = (Order*)malloc(sizeof(Order));
			u = (Room*)malloc(sizeof(Room));
			p->room_ = u;
			fgets(p->room_->roomnumber, 40, fp);//读进来的还有换行符
			fgets(p->room_->type, 10, fp);//读进来的还有换行符
			fgets(p->room_->u.name, 40, fp);//读进来的还有换行符
			fgets(p->room_->u.idcard, 20, fp);//读进来的还有换行符
			fgets(p->room_->u.phonenumber, 20, fp);//读进来的还有换行符
			fscanf(fp, "%d/%d/%d/%d", &p->year[0], &p->mon[0], &p->day[0], &p->hour[0]);
			ch = fgetc(fp);
			fscanf(fp, "%d/%d/%d/%d", &p->year[1], &p->mon[1], &p->day[1], &p->hour[1]);
			ch = fgetc(fp);
			ch = fgetc(fp);
			q->onext = p;
			q = p;
		}
	}
	q->onext = NULL;
	fclose(fp);
	return ohead;
}
int Check_date1(int year_[2], int month_[2], int date_[2], int hour_[2]) {
	int flag = 0;
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	/*printf("%d\n", p->tm_sec); 获取当前秒
	printf("%d\n", p->tm_min);获取当前分
	printf("%d\n", 8 + p->tm_hour);获取当前时,这里获取西方的时间,刚好相差八个小时
	printf("%d\n", p->tm_mday);获取当前月份日数,范围是1-31
	printf("%d\n", 1 + p->tm_mon);获取当前月份,范围是0-11,所以要加1
	printf("%d\n", 1900 + p->tm_year);获取当前年份,从1900开始，所以要加1900
	printf("%d\n", p->tm_yday); 从今年1月1日算起至今的天数，范围为0-36*/
	unsigned char Month_buf[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (month_[0] == 2)
		(((year_[0] % 4 == 0) && (year_[0] % 100 != 0)) || (year_[0] % 400 == 0)) ? Month_buf[1] += 1 : Month_buf[1];

	if (month_[0] > 12 || month_[0]<1 || date_[0]>Month_buf[month_[0] - 1] || date_[0] < 1 || hour_[0] < 0 || hour_[0]>23)
	{
		flag = 1;
		return flag;
	}
	if (year_[0] < p->tm_year + 1900)flag = 1;
	else if (year_[0] == p->tm_year + 1900) {
		if (month_[0] < p->tm_mon + 1)flag = 1;
		else if (month_[0] == p->tm_mon + 1) {
			if (date_[0] < p->tm_mday)flag = 1;
			else if (date_[0] == p->tm_mday) {
				if (hour_[0] < 8 + p->tm_hour)flag = 1;
				else if (hour_[0] == 8 + p->tm_hour)flag = 0;
				else if (hour_[0] > 8 + p->tm_hour)flag = 0;
			}
			else if (date_[0] > p->tm_mday)flag = 0;
		}
		else if (month_[0] > p->tm_mon + 1)flag = 0;
	}
	else if (year_[0] > p->tm_year + 1900)flag = 0;

	return flag;//返回0是输入日期大于当前日期，1是输入日期小于当前日期
}
int Check_date2(int year_[2], int month_[2], int date_[2], int hour_[2])
{
	 
	unsigned char Month_buf[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (month_[1] == 2)
		(((year_[1] % 4 == 0) && (year_[1] % 100 != 0)) || (year_[1] % 400 == 0)) ? Month_buf[1] += 1 : Month_buf[1];

	if (month_[1] > 12 || month_[1]<1 || date_[1]>Month_buf[month_[1] - 1] || date_[1] < 1 || hour_[1] < 0 || hour_[1]>23)return 1;
	 
	if (year_[0] < year_[1])return 0;
	else if (year_[0] == year_[1]) {
		if (month_[0] < month_[1])return 0;
		else if (month_[0] == month_[1]) {
			if (date_[0] < date_[1])return  0;
			else if (date_[0] == date_[1]) {
				if (hour_[0] < hour_[1])return  0;
				else if (hour_[0] == hour_[1]) return 1;
				else if (hour_[0] > hour_[1])return 1;
			}
			else if (date_[0] > date_[1])return 1;
		}
		else if (month_[0] > month_[1])return 1;
	}
	else if (year_[0] > year_[1])return 1;

	 //返回0是离开日期大于入住日期，1是离开日期小于入住日期
}
int Check_date3(int year, int month, int date, int hour)
{
	int flag = 0;
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	if (year < p->tm_year + 1900)flag = 0;
	else if (year == p->tm_year + 1900) {
		if (month < p->tm_mon + 1)flag = 0;
		else if (month == p->tm_mon + 1) {
			if (date < p->tm_mday)flag = 0;
			else if (date == p->tm_mday) {
				if (hour < 8 + p->tm_hour)flag = 0;
				else if (hour == 8 + p->tm_hour)flag = 0;
				else if (hour > 8 + p->tm_hour)flag++;
			}
			else if (date > p->tm_mday)flag++;
		}
		else if (month > p->tm_mon + 1)flag++;
	}
	else if (year > p->tm_year + 1900)flag++;

	return flag;//返回1是离开日期大于现在日期，0是离开日期小于现在日期
}
int Check_date4(int year_, int month_, int date_, int hour_) {
	int flag = 0;
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);

	unsigned char Month_buf[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (month_ == 2)
		(((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0)) ? Month_buf[1] += 1 : Month_buf[1];

	if (month_ > 12 || month_<1 || date_>Month_buf[month_ - 1] || date_ < 1 || hour_ < 0 || hour_>23)
	{
		flag++;
		return flag;
	}
	if (year_ < p->tm_year + 1900)flag++;
	else if (year_ == p->tm_year + 1900) {
		if (month_ < p->tm_mon + 1)flag++;
		else if (month_ == p->tm_mon + 1) {
			if (date_ < p->tm_mday)flag++;
			else if (date_ == p->tm_mday) {
				if (hour_ < 8 + p->tm_hour)flag++;
				else if (hour_ == 8 + p->tm_hour)flag = 0;
				else if (hour_ > 8 + p->tm_hour)flag = 0;
			}
			else if (date_ > p->tm_mday)flag = 0;
		}
		else if (month_ > p->tm_mon + 1)flag = 0;
	}
	else if (year_ > p->tm_year + 1900)flag = 0;
	return flag;//返回0是输入日期大于当前日期，1是输入日期小于当前日期
}
void deletedisabledorder() {
	Order* p;
	Order* q;
	p = ohead;
	int m = 0;
	q = p->onext;
	while (q != NULL) {
		if (Check_date3(q->year[1], q->mon[1], q->day[1], q->hour[1]) != 1)//判断订单是否失效
		{
			emptyroom(q->room_->roomnumber);//把房间状态清除
			p->onext = q->onext;
			free(q);
			q = p->onext;
			m++;
		}
		else {
			p = p->onext;
			q = q->onext;
		}
	}
	if (m != 0)printf("失效订单已删除\n");
	else
		printf("当前无失效订单\n");
}
void checkchar(char t[]) {
	int i;
	for (i = 0;; i++) {
		if (t[i] == '\n') {
			t[i] = '\0';
			break;
		}
	}

}
void checkchar1(char t[]) {
	int i;
	for (i = 0;; i++) {
		if (t[i] == '\0') {
			t[i] = '\n';
			t[i + 1] = '\0';//添加换行符
			break;
		}
	}
}
void changeorder()//修改订单
{
	system("cls");
	char phonenumber_[20];
	char id[40];
	Order* p;
	char num[20];
	int m = 0, m1 = 0;
	if (ohead->onext == NULL)
	{
		printf("订单为空修改失败\n");
		system("pause");
	}
	else
	{
		p = ohead->onext;
		char nam[20];
		printf("输入修改订单的客户的姓名：");
		fflush(stdin);
		rewind(stdin);
		gets(nam);
		checkchar1(nam);
		while (strcmp(p->room_->u.name, nam) != 0 && p->onext != NULL)
			p = p->onext;
		if (strcmp(p->room_->u.name, nam) == 0)
		{
			m++;
			if (Check_date1(p->year, p->mon, p->day, p->hour) != 0) {
				printf("已到入住日期无法修改");
				system("pause");
			}
			else while (1)
			{
				system("cls");
				printf("1.修改姓名\n");
				printf("2.修改电话\n");
				printf("3.修改身份证号\n");
				printf("4.修改入住时期\n");
				printf("5.修改离开时期\n");
				printf("6.退出修改\n");
				printf("输入要修改的选项:\n");
				fflush(stdin);
				rewind(stdin);
				gets(num);
				while ((strcmp(num, "1") != 0) && (strcmp(num, "2") != 0) && (strcmp(num, "3") != 0) && (strcmp(num, "4") != 0) && (strcmp(num, "5") != 0) && (strcmp(num, "6") != 0)) {
					printf("选择有误，请重新输入:");
					fflush(stdin);
					rewind(stdin);
					gets(num);
				}
				if (strcmp(num, "1") == 0)
				{
					printf("输入新的姓名：");
					checkchar(p->room_->u.name);
					gets(nam);
					while (strcmp(p->room_->u.name, nam) == 0) {
						printf("姓名未更改，请重新输入:");
						scanf("%s", nam);
					}
					checkchar1(nam);//加上换行符才能比较
					strcpy(p->room_->u.name, nam);
					printf("修改成功\n");
				}
				if (strcmp(num, "2") == 0)
				{
					printf("输入新的电话：");
					checkchar(p->room_->u.phonenumber);
					scanf("%s", phonenumber_);
					while (strlen(phonenumber_) != 11 || judgephone(phonenumber_) != 0 || strcmp(p->room_->u.phonenumber, phonenumber_) == 0) {
						printf("电话号不符合要求，请重新输入:");
						scanf("%s", phonenumber_);
					}
					checkchar1(phonenumber_);//加上换行符才能比较
					strcpy(p->room_->u.phonenumber, phonenumber_);
					printf("修改成功\n");
				}
				if (strcmp(num, "3") == 0)
				{
					printf("输入新的身份证号：");
					checkchar(p->room_->u.idcard);
					fflush(stdin);
					rewind(stdin);
					scanf("%s", id);
					while (strlen(id) != 18 || judgeid(id) != 0 || strcmp(p->room_->u.idcard, id) == 0) {
						printf("身份证号码格式有误，请重新输入:");
						fflush(stdin);
						rewind(stdin);
						scanf("%s", id);
					}
					checkchar1(id);//加上换行符才能比较
					strcpy(p->room_->u.idcard, id);
					printf("修改成功\n");
				}
				if (strcmp(num, "4") == 0)
				{
					if (Check_date1(p->year, p->mon, p->day, p->hour) == 0) {
						printf("请输入入住时间：年月日时(24时）中间请用/隔开：");
						fflush(stdin);
						rewind(stdin);
						while ((scanf("%d/%d/%d/%d", &p->year[0], &p->mon[0], &p->day[0], &p->hour[0]) != 4) || Check_date1(p->year, p->mon, p->day, p->hour) != 0 || Check_date2(p->year, p->mon, p->day, p->hour) != 0) {
							if (Check_date2(p->year, p->mon, p->day, p->hour) != 0) {
								printf("请修改离开时间：年月日时(24时）中间请用/隔开：");
								fflush(stdin);
								rewind(stdin);
								while ((scanf("%d/%d/%d/%d", &p->year[1], &p->mon[1], &p->day[1], &p->hour[1]) != 4) || Check_date2(p->year, p->mon, p->day, p->hour) != 0) {
									printf("日期输入有误，");
									printf("请重新输入离开时间：年月日时(24时）中间请用/隔开：");
									fflush(stdin);
									rewind(stdin);
								}break;
							}
							else {
								printf("日期输入有误\n");
								printf("请重新输入入住时间：年月日时(24时）中间请用/隔开：");
							
							fflush(stdin);
							rewind(stdin);}
						}

						printf("修改成功\n");
					}
				}
				if (strcmp(num, "5") == 0) {
					printf("请输入离开时间：年月日时(24时）中间请用/隔开：");
					fflush(stdin);
					rewind(stdin);
					while ((scanf("%d/%d/%d/%d", &p->year[1], &p->mon[1], &p->day[1], &p->hour[1]) != 4) || Check_date2(p->year, p->mon, p->day, p->hour) != 0) {
						printf("日期输入有误，");
						printf("请重新输入离开时间：年月日时(24时）中间请用/隔开：");
						fflush(stdin);
						rewind(stdin);
					}
					printf("修改成功\n");
				}
				if (strcmp(num, "6") == 0)break;
				system("pause");
			}

		}
		if (m == 0)printf("该客人不在订单中\n");
		printf("\n");
		system("pause");
	}
}
void deleteorder() {
	char nam[20];
	system("cls");
	if (ohead->onext == NULL)
	{
		printf("没有可删除的订单\n");
		system("pause");
	}
	else {
		printf("请输入你要删除的订单的姓名：");
		fflush(stdin);
		rewind(stdin);
		gets(nam);
		checkchar1(nam);//加上换行符才能比较
		Order* p;
		Order* q;
		p = ohead;
		q = p->onext;
		while (q != NULL) {
			if (strcmp(q->room_->u.name, nam) == 0)
			{
				emptyroom(q->room_->roomnumber);
				p->onext = q->onext;
				free(q);
				q = p->onext;
				printf("已删除该订单\n");
				system("pause");
			}
			else {
				p = p->onext;
				q = q->onext;
			}

		}
	}

}
void changeKEY() {
	char s[15], c[15], n[15];
	int i, a = 0, b = 0, e = 0;
	system("cls");

	FILE* fp = fopen("password.txt", "r+");
	if (fp == NULL) {
		printf("Failed to open file");

	}
	fgets(s, 14, fp);//取出密码
	rewind(fp);//指针回到文件开头
	fclose(fp);
	fp = fopen("password.txt", "w");
	printf("请输入原密码:\n");
	fflush(stdin);
	rewind(stdin);
	gets(c);
	while (strcmp(c, s) != 0) {
		printf("原密码输入错误\n请重新输入");
		fflush(stdin);
		rewind(stdin);
		gets(c);
	}
	if (strcmp(c, s) == 0) {
		printf("请输入新密码（6~14位）:\n");
		fflush(stdin);
		rewind(stdin);
		gets(n);
	}
	
	i = strlen(n);

	for (int f = 0; f < i; f++)
	{
		if (('a' <= n[f] && n[f] <= 'z') || ('A' <= n[f] && n[f] <= 'Z'))
			a++;
		else if ('0' <= n[f] && n[f] <= '9')
			b++;

		else
			e++;
	}//判断字母数字和其他字符的个数

	while (i < 6 || i >= 15 || a == 0 || b == 0 || e == 0|| strcmp(n, s) == 0) {

		if (strcmp(n, s) == 0)printf("\n与原密码相同\n请重新输入：");
		else printf("\n安全性不高或位数不符合要求\n请重新输入：\n");
		fflush(stdin);
		rewind(stdin);
		gets(n);
		i = strlen(n);
		a = 0; b = 0; e = 0;
		for (int f = 0; f < i; f++)
		{
			if (('a' <= n[f] && n[f] <= 'z') || ('A' <= n[f] && n[f] <= 'Z'))
				a++;
			else if ('0' <= n[f] && n[f] <= '9')
				b++;

			else
				e++;
		}
	}//判断字母数字和其他字符的个数}
	 
	fputs(n, fp);
	fclose(fp);
	printf("\n密码修改成功\n");
	system("pause");
}
void color1() {
	char e[15];
	FILE* fp = fopen("color.txt", "r");
	if (fp == NULL) {
		printf("Failed to open file");

	}
	e[0] = fgetc(fp);
	fclose(fp);
	switch (*e) {

	case'1':system("color 10"); break;
	case'2':system("color 20"); break;
	case'3':system("color 30"); break;
	case'4':system("color 40"); break;
	case'5':system("color 50"); break;
	case'6':system("color 60"); break;
	case'7':system("color 70"); break;
	case'8':system("color 80"); break;
	case'9':system("color 90"); break;
	case'A':system("color A0"); break;
	case'B':system("color B0"); break;
	case'C':system("color C0"); break;
	case'D':system("color D0"); break;
	case'E':system("color E0"); break;
	case'F':system("color F0"); break;

	}
}
void changecolor1() {
	int a;
	system("cls");
	FILE* p = fopen("color.txt", "w");
	if (p == NULL) {
		printf("Failed to open file");

	}

	printf("颜色列表：1=蓝色 2=绿色 3=湖蓝色 4=红色\n5=紫色 6=黄色 7=白色 8=灰色\n9=淡蓝色 10=淡绿色 11=淡浅绿色 12=淡红色\n13=淡紫色 14=淡黄色 15=亮白色\n");
	printf("请选择相应数字改变系统颜色");

	scanf("%d", &a);
	while (a < 1 || a>15) { printf("您的输入有误，请重新输入\n");  scanf("%d", &a); }
	switch (a) {

	case 1:system("color 10"); fputs("1", p); break;
	case 2:system("color 20"); fputs("2", p); break;
	case 3:system("color 30"); fputs("3", p); break;
	case 4:system("color 40"); fputs("4", p); break;
	case 5:system("color 50"); fputs("5", p); break;
	case 6:system("color 60"); fputs("6", p); break;
	case 7:system("color 70"); fputs("7", p); break;
	case 8:system("color 80"); fputs("8", p); break;
	case 9:system("color 90"); fputs("9", p); break;
	case 10:system("color A0"); fputs("A", p); break;
	case 11:system("color B0"); fputs("B", p); break;
	case 12:system("color C0"); fputs("C", p); break;
	case 13:system("color D0"); fputs("D", p); break;
	case 14:system("color E0"); fputs("E", p); break;
	case 15:system("color F0"); fputs("F", p); break;

	}fclose(p); printf("\n颜色修改成功\n");
	system("pause");

}
void search2()
{
	system("cls");
	Order* p;
	int m;
	if (ohead->onext == NULL)
	{
		printf("无订单，查找失败\n");
		system("pause");
	}
	else
	{
		while (1) {
			system("cls");
			printf("选择查找方式：(1~4)\n");
			printf("1.按姓名查找\n");
			printf("2.按电话查找\n");
			printf("3.按身份证号查找\n");
			printf("4.按房间号查找\n");
			printf("5.返回上一层\n");
			char t[20];
			fflush(stdin);
			rewind(stdin);
			gets(t);
			while ((strcmp(t, "1") != 0) && (strcmp(t, "2") != 0) && (strcmp(t, "3") != 0) && (strcmp(t, "4") != 0) && (strcmp(t, "5") != 0)) {
				printf("选择有误，请重新输入:");
				fflush(stdin);
				rewind(stdin);
				gets(t);
			}
			if (strcmp(t, "1") == 0)
			{
				m = 0;
				p = ohead->onext;
				printf("输入查找的姓名：");
				char nam[40];
				fflush(stdin);
				rewind(stdin);
				gets(nam);
				while (p != NULL)
				{
					checkchar(p->room_->u.name);
					if (FindSubstring(p->room_->u.name, nam) == 0)
					{
						m++;
						checkchar1(p->room_->u.name);
						printf("\n姓名：%s\n", p->room_->u.name);
						printf("\n电话：%s\n", p->room_->u.phonenumber);
						printf("身份证号：%s\n", p->room_->u.idcard);
						printf("房间号: %s\n", p->room_->roomnumber);
						printf("入住日期：%d/%d/%d/%d\n", p->year[0], p->mon[0], p->day[0], p->hour[0]);
						printf("离开日期：%d/%d/%d/%d\n", p->year[1], p->mon[1], p->day[1], p->hour[1]);

					}
					p = p->onext;
				}

				if (m == 0)
					printf("查找用户不存在\n");
				system("pause");

			}
			if (strcmp(t, "2") == 0)
			{
				m = 0;
				p = ohead->onext;
				char ph[20];
				printf("输入查找的电话：");
				fflush(stdin);
				rewind(stdin);
				gets(ph);
				while (strlen(ph) != 11 || judgephone(ph) != 0)
				{//判断电话号号是否符合规则。
					printf("电话号不符合要求，请重新输入:");
					fflush(stdin);
					rewind(stdin);
					scanf("%s", ph);
				}
				checkchar1(ph);
				while (p != NULL && strcmp(ph, p->room_->u.phonenumber) == 0) {
					//找到电话一致的客人
					if (strcmp(ph, p->room_->u.phonenumber) == 0)
					{
						m++;
						printf("\n姓名：%s\n", p->room_->u.name);
						printf("\n电话：%s\n", p->room_->u.phonenumber);
						printf("身份证号：%s\n", p->room_->u.idcard);
						printf("房间号: %s\n", p->room_->roomnumber);
						printf("入住日期：%d/%d/%d/%d\n", p->year[0], p->mon[0], p->day[0], p->hour[0]);
						printf("离开日期：%d/%d/%d/%d\n", p->year[1], p->mon[1], p->day[1], p->hour[1]);

					}
					p = p->onext;
				}
				if (m == 0)
					printf("查找号码不存在\n");
				system("pause");

			}
			if (strcmp(t, "3") == 0)
			{
				char id[18];
				printf("输入要查找的身份证号：");
				fflush(stdin);
				rewind(stdin);
				gets(id);
				while (strlen(id) != 18 || judgeid(id) != 0) {//判断身份证号是否符合规则。
					printf("身份证号码格式有误，请重新输入:");
					fflush(stdin);
					rewind(stdin);
					scanf("%s", id);
				}
				checkchar1(id);
				m = 0;
				p = ohead->onext;
				while (p != NULL && strcmp(p->room_->u.idcard, id) == 0) {
					if (strcmp(p->room_->u.idcard, id) == 0)
					{
						m++;
						printf("\n姓名：%s\n", p->room_->u.name);
						printf("\n电话：%s\n", p->room_->u.phonenumber);
						printf("身份证号：%s\n", p->room_->u.idcard);
						printf("房间号: %s\n", p->room_->roomnumber);
						printf("入住日期：%d/%d/%d/%d\n", p->year[0], p->mon[0], p->day[0], p->hour[0]);
						printf("离开日期：%d/%d/%d/%d\n", p->year[1], p->mon[1], p->day[1], p->hour[1]);
					}
					p = p->onext;
				}
				if (m == 0)
					printf("查找号码不存在\n");
				system("pause");
			}
			if (strcmp(t, "4") == 0)
			{
				char roomnum[20];
				printf("输入要查找的房间号（本酒店房间号101~112；201~208；301~304；401~403）：");
				fflush(stdin);
				rewind(stdin);
				gets(roomnum);
				checkchar1(roomnum);
				m = 0;
				p = ohead->onext;
				while (p != NULL) {

					if (strcmp(p->room_->roomnumber, roomnum) == 0)
					{
						m++;
						printf("\n姓名：%s\n", p->room_->u.name);
						printf("\n电话：%s\n", p->room_->u.phonenumber);
						printf("身份证号：%s\n", p->room_->u.idcard);
						printf("房间号: %s\n", p->room_->roomnumber);
						printf("入住日期：%d/%d/%d/%d\n", p->year[0], p->mon[0], p->day[0], p->hour[0]);
						printf("离开日期：%d/%d/%d/%d\n", p->year[1], p->mon[1], p->day[1], p->hour[1]);

					}
					p = p->onext;

				}
				if (m == 0)
					printf("房间未被使用或未输入正确房间号\n");
				system("pause");
			}
			if (strcmp(t, "5") == 0)break;
			printf("\n");
		}
	}
}
void search1()
{
	int flag1 = 0, flag2 = 0;
	system("cls");
	int count1 = 0, count2 = 0, count3 = 0, count4 = 0, m;
	char c[10];
	Room* p;
	if (rhead->rnext == NULL)
	{
		printf("无房间，查找失败\n");
		system("pause");
	}
	else
	{
		while (1) {
			system("cls");
			printf("请输入查询方式:\n");
			printf("1.房间状态查询\n");
		 
			printf("2.房间状态和房间类型组合查询\n");
			printf("3.返回上一层\n");
			char t[20];
			fflush(stdin);
			rewind(stdin);
			gets(t);
			while ((strcmp(t, "1") != 0) && (strcmp(t, "2") != 0) && (strcmp(t, "3") != 0)) {
				printf("选择有误，请重新输入:");
				fflush(stdin);
				rewind(stdin);
				gets(t);
			}
			if (strcmp(t, "1") == 0) {
				system("cls");
				printf("闲置房:");
				printf("\n");
				for (p = rhead->rnext; p->rnext != NULL; p = p->rnext)if (p->flag == 0) {
					printf("%s", p->roomnumber); flag1++;
				}
				printf("\n");
				if (flag1 == 0)printf("无");
				printf("被占用房");
				printf("\n");
				for (p = rhead->rnext; p->rnext != NULL; p = p->rnext)if (p->flag != 0) {
					printf("%s", p->roomnumber); flag2++;
				}
				if (flag2 == 0)printf("无");
				printf("\n");
			}
			 
			
			if (strcmp(t, "2") == 0) {
				while (1) {
					system("cls");
					char n[20];
					printf("请选择查询类型：\n1.单人间\n2.双人间\n3.三人间\n4.四人间\n5.返回上一层\n");
					fflush(stdin);
					rewind(stdin);
					gets(n);

					while (strcmp(n, "1") != 0 && strcmp(n, "2") != 0 && strcmp(n, "3") != 0 && strcmp(n, "4") != 0 && strcmp(n, "5") != 0) {
						printf("选择有误，请重新选择：");
						fflush(stdin);
						rewind(stdin);
						gets(n);
					}
					if (strcmp(n, "1") == 0) {
						printf("空房有：\n");
						for (p = rhead->rnext; p != NULL; p = p->rnext)
							if (p->flag == 0 && strcmp(p->type, "single\n") == 0)
							{
								count1++; printf("%s", p->roomnumber);
							}
						printf("\n");
						printf("单人间还剩%d间", count1);
					}
					if (strcmp(n, "2") == 0) {
						printf("空房有：\n");
						for (p = rhead->rnext; p != NULL; p = p->rnext)if (p->flag == 0 && strcmp(p->type, "double\n") == 0)
						{
							count2++; printf("%s", p->roomnumber);
						}
						printf("\n");
						printf("双人间还剩%d间", count2);
					}
					if (strcmp(n, "3") == 0) {
						printf("空房有：\n");
						for (p = rhead->rnext; p != NULL; p = p->rnext)if (p->flag == 0 && strcmp(p->type, "triple\n") == 0)
						{
							count3++; printf("%s", p->roomnumber);
						}
						printf("三人间还剩%d间", count3);
					}
					if (strcmp(n, "4") == 0) {
						printf("空房有：\n");
						for (p = rhead->rnext; p != NULL; p = p->rnext)if (p->flag == 0 && strcmp(p->type, "four\n") == 0)
						{
							count4++; printf("%s", p->roomnumber);
						}
						printf("\n");
						printf("四人间还剩%d间", count4);
					}
					if (strcmp(n, "5") == 0)break;
					printf("\n");
					system("pause");
				}
			}
			if (strcmp(t, "3") == 0)break;
			printf("\n");
			system("pause");
		}

	}
}
void statistics() {
	system("cls");

	Order* e; int m, year, mon, day, hour;
	if (ohead->onext == NULL)
	{
		printf("无订单\n");
		system("pause");
	}
	else {
		printf("请输入截止日期 年月日时(24时）中间请用/隔开：\n");
		fflush(stdin);
		rewind(stdin);

		while ((scanf("%d/%d/%d/%d", &year, &mon, &day, &hour)) != 4 || Check_date4(year, mon, day, hour) == 1)
		{
			printf("请输入有效时间");
			fflush(stdin);
			rewind(stdin);
		}
		printf("在该日期前生效的订单有\n");
		for (e = ohead->onext; e != NULL; e = e->onext)if (time_1(year, mon, day, hour, e) == -1 || time_1(year, mon, day, hour, e) == 0) {
			printf("\n姓名：%s", e->room_->u.name);
			printf("电话：%s", e->room_->u.phonenumber);
			printf("身份证号：%s", e->room_->u.idcard);
			printf("房间号: %s", e->room_->roomnumber);
			printf("入住日期：%d/%d/%d/%d\n", e->year[0], e->mon[0], e->day[0], e->hour[0]);
			printf("离开日期：%d/%d/%d/%d\n", e->year[1],e->mon[1], e->day[1], e->hour[1]);
			printf("\n");
		}
	}
	system("pause");
}
int time_1(int year, int mon, int day, int hour, Order* p)
{

	if ((p->year[0]) > year)return 1;
	if ((p->year[0]) < year)return -1;
	if ((p->year[0]) == year) {
		if ((p->mon[0]) > mon)return 1;
		if ((p->mon[0]) < mon)return -1;
		if ((p->mon[0]) == mon) {
			if ((p->day[0]) < day)return -1;
			if ((p->day[0]) > day)return  1;
			if ((p->day[0]) == day) {
				if ((p->hour[0]) < hour)return -1;
				if ((p->hour[0]) > hour)return 1;
				if ((p->hour[0]) == hour)return 0;
			}
		}
	}
}
void read_() {
	 
	extern Room* rhead;
	extern Order* ohead;
	FILE* fp = NULL;
	FILE* fp1 = NULL;
	char ch;
	rhead = (Room*)malloc(sizeof(Room));
	if (rhead != NULL)
	{
		rhead->rnext = NULL;
	}
	ohead = exploitorderhead();
	Room* p = rhead;
	Room* q = rhead;
	Order* p1 = ohead;
	Order* q1 = ohead;
	Room* u;
	if ((fp = fopen("room.txt", "r+")) == NULL || (fp1 = fopen("order.txt", "r+")) == NULL)
	{
		 
		fp = fopen("room1.txt", "r+");
		fp1 = fopen("order1.txt", "r+");
	}
	else {
		fp = fopen("room.txt", "r+");
		fp1 = fopen("order.txt", "r+");
		 
	}
	while (!feof(fp))
	{
		p = (Room*)malloc(sizeof(Room));
		fgets(p->roomnumber, 20, fp);//读进来的还有换行符
		//printf("%s\n",p->roomnumber);
		fgets(p->type, 20, fp);//读进来的还有换行符
		//printf("%s\n",p->type);
		fscanf(fp, "%d", &(p->flag));
		//printf("%d\n",p->flag);
		ch = fgetc(fp);
		ch = fgetc(fp);
		q->rnext = p;
		q = p;
	}
	q->rnext = NULL;
	fclose(fp);
	ch = fgetc(fp1);
	if (!feof(fp1)) {
		rewind(fp1);
		while (!feof(fp1))
		{
			p1 = (Order*)malloc(sizeof(Order));
			u = (Room*)malloc(sizeof(Room));
			p1->room_ = u;
			fgets(p1->room_->roomnumber, 40, fp1);//读进来的还有换行符
			fgets(p1->room_->type, 10, fp1);//读进来的还有换行符
			fgets(p1->room_->u.name, 40, fp1);//读进来的还有换行符
			fgets(p1->room_->u.idcard, 20, fp1);//读进来的还有换行符
			fgets(p1->room_->u.phonenumber, 20, fp1);//读进来的还有换行符
			fscanf(fp1, "%d/%d/%d/%d", &p1->year[0], &p1->mon[0], &p1->day[0], &p1->hour[0]);
			ch = fgetc(fp1);
			fscanf(fp1, "%d/%d/%d/%d", &p1->year[1], &p1->mon[1], &p1->day[1], &p1->hour[1]);
			ch = fgetc(fp1);
			ch = fgetc(fp1);
			q1->onext = p1;
			q1 = p1;
		}
	}
	q1->onext = NULL;
	fclose(fp1);
	deletedisabledorder();
	 
}
void backups() {
	system("cls");
	FILE* fp = NULL;
	FILE* fp1 = NULL;
	if ((fp = fopen("order1.txt", "w")) == NULL)
	{
		printf("can't built the order1 file\n");
		system("pause");
	}
	if ((fp1 = fopen("room1.txt", "w")) == NULL)
	{
		printf("can't open the room1 file\n");
		system("pause");
	}
	Room* p1 = rhead->rnext;
	Order* p = ohead->onext;
	while (p != NULL) {
		fputs(p->room_->roomnumber, fp);//连换行符一起保存
		fputs(p->room_->type, fp);//连换行符一起保存
		fputs(p->room_->u.name, fp);//连换行符一起保存
		fputs(p->room_->u.idcard, fp);//连换行符一起保存
		fputs(p->room_->u.phonenumber, fp);//连换行符一起保存
		fprintf(fp, "%d", p->year[0]);
		fputc('/', fp);
		fprintf(fp, "%d", p->mon[0]);
		fputc('/', fp);
		fprintf(fp, "%d", p->day[0]);
		fputc('/', fp);
		fprintf(fp, "%d", p->hour[0]);
		fputc('\n', fp);
		fprintf(fp, "%d", p->year[1]);
		fputc('/', fp);
		fprintf(fp, "%d", p->mon[1]);
		fputc('/', fp);
		fprintf(fp, "%d", p->day[1]);
		fputc('/', fp);
		fprintf(fp, "%d", p->hour[1]);
		fputc('\n', fp);
		if (p->onext != NULL)fputc('\n', fp);
		p = p->onext;
	}
	while (p1 != NULL) {
		fputs(p1->roomnumber, fp1);
		fputs(p1->type, fp1);
		fprintf(fp1, "%d", p1->flag);
		fputc('\n', fp1);
		if (p1->rnext != NULL)fputc('\n', fp1);
		p1 = p1->rnext;
	}
	if (fclose(fp1) == 0 && fclose(fp) == 0)printf("备份成功\n");
	else
		printf("备份失败\n");
	system("pause");
}
int FindSubstring(const char* strSource, const char* strSub)
{
	unsigned int uLen = strlen(strSource);
	if (uLen == 0)
	{
		return -1;
	}
	char* str1 = (char*)malloc(uLen + 1);
	memset(str1, '\0', uLen + 1);
	strcpy(str1, strSource);
	uLen = strlen(strSub);
	if (uLen == 0)
	{
		free(str1);
		return -1;
	}
	char* str2 = (char*)malloc(uLen + 1);
	memset(str2, '\0', uLen + 1);
	strcpy(str2, strSub);
	unsigned int i = 0, j = 0;
	for (i = 0; i < strlen(strSource); i = i + 2)
	{
		if (str1[i] == str2[j] && str1[i + 1] == str2[j + 1])
		{
			j++;
			j++;
		}
		else
		{
			if (j == uLen)
			{
				break;
			}
			else
			{
				j = 0;
			}
		}
	}
	free(str1);
	free(str2);
	if (j == uLen)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}