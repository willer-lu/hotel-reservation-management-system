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
	fgets(s, 14, fp);//�����ļ��е�����
	fclose(fp);
	color1();//����֮ǰ�޸ĵ���ɫ����ϵͳ��ɫ
	printf("\n�������¼����:");
	gets(c);
	while (strcmp(c, s) != 0) { //�ж������Ƿ���ȷ������ȷ�Ļ��������롣
		printf("\n�������������");
		gets(c);
	}
	if (strcmp(c, s) == 0) {
		read_();
		while (1)
		{

			system("cls");//��ս���
			color1();//����֮ǰ�޸ĵ���ɫ����ϵͳ��ɫ
			printf("\n\n\n\n");
			printf(" ***********************************************\n");
			printf(" ^_^  ^_^  ^_^  ^_^  ^_^  ^_^  ^_^  ^_^  ^_^ ^_^\n");
			printf(" ***********************************************\n");
			printf("_______________________________________________\n");
			printf("��                                            ��\n");
			printf("��              �Ƶ�ԤԼ����ϵͳ              ��\n");
			printf("��            ��ӭ������ɽ��ˮ�Ƶ꣡          ��\n");
			printf("��            ������%d��", 1900 + p->tm_year);/*��ȡ��ǰ���,��֪1900��ʼ������Ҫ��1900*/
			printf("%d��", 1 + p->tm_mon);/*��ȡ��ǰ�·�,��Χ��0-11,����Ҫ��1*/
			printf("%d��", p->tm_mday);/*��ȡ��ǰ�·�����,��Χ��1-31*/
			printf("%dʱ", 8 + p->tm_hour);/*��ȡ��ǰʱ,�����ȡ������ʱ�ټ�,�պ����˸���Сʱ*/
			printf("         ��\n");
			printf("��                                            ��\n");
			printf("��                                            ��\n");
			printf("��____________________________________________��\n");
			printf("***********************************************\n");
			printf("***********************************************\n");
			printf("**            1.�ͻ���ס��Ϣ�Ǽ�             **\n");
			printf("**            2.�޸ı�����ɫ                 **\n");
			printf("**            3.�޸�����                     **\n");
			printf("**            4.��ѯ��Ϣ                     **\n");
			printf("**            5.�޸Ķ�����Ϣ                 **\n");
			printf("**            6.ɾ������                     **\n");
			printf("**            7.ͳ����Ϣ                     **\n");
			printf("**            8.����                         **\n");
			printf("**            9.�˳�������                   **\n");
			printf("***********************************************\n");
			printf("***********************************************\n");
			printf("***********************************************\n");
			printf("^_^  ^_^  ^_^  ^_^  ^_^  ^_^  ^_^  ^_^  ^_^ ^_^\n");
			printf("***********************************************\n");
			printf("               ѡ�������");
			int m;
			char t[20];
			scanf("%d", &m);
			while (m < 1 || m>9) { printf("\n�밴Ҫ������"); scanf("%d", &m); }
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
				printf("ѡ���ѯ���\n");
				printf("1.��ѯ������Ϣ\n");
				printf("2.��ѯ������Ϣ\n");
				printf("����ѡ�");
				gets(t);
				while ((strcmp(t, "1") != 0) && (strcmp(t, "2") != 0)) {
					printf("\n�밴Ҫ������\n");
					gets(t);
					fflush(stdin);
				}
				if ((strcmp(t, "1") == 0))search1();//��ѯ����
				if ((strcmp(t, "2") == 0))search2();//��ѯ����
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
Room* readroom()//���ļ����������room�ŵ���������
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
		fgets(p->roomnumber, 20, fp);//�������Ļ��л��з�
		//printf("%s\n",p->roomnumber);
		fgets(p->type, 20, fp);//�������Ļ��л��з�
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
	return rhead;//����ָ���ͷ
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
void emptyroom(char roomnumber_[10])//���һ������
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
	return flag;//���֤������Ϲ���Ļ�����0��else����1.
}
int judgephone(char t[]) {
	int flag = 0;
	int i = 0;
	for (i = 0; i < 11; i++) {

		if (t[i] <= '9' && t[i] >= '0')flag = 0;
		else flag = 1;
	}
	return flag;//�绰�ŷ��Ϲ���Ļ�����0��else����1.
}
Order* exploitorderhead() {
	ohead = (Order*)malloc(sizeof(Order));
	if (ohead != NULL)
	{
		ohead->onext = NULL;
		return ohead;
	}
	else
		printf("���ٶ���ͷʧ��\n");
}
void chooseroomtype() {
	char c[20];
	char choice[10];
	while (1) {
		system("cls");
		printf("��������:\n");
		printf("1.single\n");
		printf("2.double\n");
		printf("3.triple\n");
		printf("4.four\n");
		printf("5.������һ��\n");
		printf("���������ѡ��:");
		fflush(stdin);
		rewind(stdin);
		gets(c);
		while ((strcmp(c, "1") != 0) && (strcmp(c, "2") != 0) && (strcmp(c, "3") != 0) && (strcmp(c, "4") != 0) && (strcmp(c, "5") != 0)) {
			printf("ѡ����������������:");
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
			printf("��������ѡ��ɹ�\n");
			openroom(c);
		}
		else
		{
			printf("��Ǹ�����෿��û�пշ���������ѡ��");
			system("pause");
			system("cls");
			chooseroomtype();

		}
	}
	if (strcmp(c, "double\n") == 0)
	{
		if (flag2 >= 1) {
			printf("��������ѡ��ɹ�\n");
			openroom(c);
		}
		else
		{
			printf("��Ǹ�����෿��û�пշ���������ѡ��");
			system("pause");
			system("cls");
			chooseroomtype();
		}
	}
	if (strcmp(c, "triple\n") == 0)
	{
		if (flag3 >= 1) {
			printf("��������ѡ��ɹ�\n");
			openroom(c);
		}
		else
		{
			printf("��Ǹ�����෿��û�пշ���������ѡ��");
			system("pause");
			system("cls");
			chooseroomtype();
		}
	}
	if (strcmp(c, "four\n") == 0)
	{
		if (flag4 >= 1) {
			printf("��������ѡ��ɹ�\n");
			openroom(c);
		}
		else
		{
			printf("��Ǹ�����෿��û�пշ���������ѡ��");
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
	}//�ҵ�ָ��ĩβ��
	Order* oop = (Order*)malloc(sizeof(Order));
	op->onext = oop;
	oop->onext = NULL;
	char id[40];
	char phonenumber_[20];
	while (p != NULL) {
		if (p->flag == 0 && strcmp(p->type, t) == 0) {
			p->flag = 1;
			oop->room_ = p;
			printf("�����뷿��������");
			fflush(stdin);
			rewind(stdin);
			scanf("%s", p->u.name);
			checkchar1(p->u.name);//����\n�����Ժ��ж�
			printf("������18λ�����֤���룺");
			fflush(stdin);
			rewind(stdin);
			scanf("%s", id);
			while (strlen(id) != 18 || judgeid(id) != 0) {//�ж����֤���Ƿ���Ϲ���
				printf("���֤�����ʽ��������������:");
				fflush(stdin);
				rewind(stdin);
				scanf("%s", id);
			}
			checkchar1(id);//����\n�����Ժ��ж�
			strcpy(p->u.idcard, id);
			printf("������11λ�绰�ţ�");
			fflush(stdin);
			rewind(stdin);
			scanf("%s", phonenumber_);
			while (strlen(phonenumber_) != 11 || judgephone(phonenumber_) != 0)
			{//�жϵ绰�ź��Ƿ���Ϲ���
				printf("�绰�Ų�����Ҫ������������:");
				fflush(stdin);
				rewind(stdin);
				scanf("%s", phonenumber_);
			}
			checkchar1(phonenumber_);//����\n�����Ժ��ж�
			strcpy(p->u.phonenumber, phonenumber_);
			printf("��������סʱ�䣺������ʱ(24ʱ���м�����/������");
			fflush(stdin);
			rewind(stdin);
			while ((scanf("%d/%d/%d/%d", &oop->year[0], &oop->mon[0], &oop->day[0], &oop->hour[0])) != 4 || Check_date1(oop->year, oop->mon, oop->day, oop->hour) != 0) {//�ж������Ƿ���ڵ�ǰ����
				printf("������������");
				printf("������������סʱ�䣺������ʱ(24ʱ���м�����/������");
				fflush(stdin);
				rewind(stdin);
			}
			printf("�������뿪ʱ�䣺������ʱ(24ʱ���м�����/������");
			fflush(stdin);
			rewind(stdin);
			while ((scanf("%d/%d/%d/%d", &oop->year[1], &oop->mon[1], &oop->day[1], &oop->hour[1])) != 4 || Check_date2(oop->year, oop->mon, oop->day, oop->hour) != 0) {//�ж��뿪�����Ƿ���ס��ǰ����
				printf("������������");
				printf("�����������뿪ʱ�䣺������ʱ(24ʱ���м�����/������");
			}
			printf("���ķ�����룺%s", p->roomnumber);
			printf("���������ɹ�\n");
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
	printf("��������:\n");
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
		fputs(p->room_->roomnumber, fp);//�����з�һ�𱣴�
		fputs(p->room_->type, fp);//�����з�һ�𱣴�
		fputs(p->room_->u.name, fp);//�����з�һ�𱣴�
		fputs(p->room_->u.idcard, fp);//�����з�һ�𱣴�
		fputs(p->room_->u.phonenumber, fp);//�����з�һ�𱣴�
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
			fgets(p->room_->roomnumber, 40, fp);//�������Ļ��л��з�
			fgets(p->room_->type, 10, fp);//�������Ļ��л��з�
			fgets(p->room_->u.name, 40, fp);//�������Ļ��л��з�
			fgets(p->room_->u.idcard, 20, fp);//�������Ļ��л��з�
			fgets(p->room_->u.phonenumber, 20, fp);//�������Ļ��л��з�
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
	/*printf("%d\n", p->tm_sec); ��ȡ��ǰ��
	printf("%d\n", p->tm_min);��ȡ��ǰ��
	printf("%d\n", 8 + p->tm_hour);��ȡ��ǰʱ,�����ȡ������ʱ��,�պ����˸�Сʱ
	printf("%d\n", p->tm_mday);��ȡ��ǰ�·�����,��Χ��1-31
	printf("%d\n", 1 + p->tm_mon);��ȡ��ǰ�·�,��Χ��0-11,����Ҫ��1
	printf("%d\n", 1900 + p->tm_year);��ȡ��ǰ���,��1900��ʼ������Ҫ��1900
	printf("%d\n", p->tm_yday); �ӽ���1��1�������������������ΧΪ0-36*/
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

	return flag;//����0���������ڴ��ڵ�ǰ���ڣ�1����������С�ڵ�ǰ����
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

	 //����0���뿪���ڴ�����ס���ڣ�1���뿪����С����ס����
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

	return flag;//����1���뿪���ڴ����������ڣ�0���뿪����С����������
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
	return flag;//����0���������ڴ��ڵ�ǰ���ڣ�1����������С�ڵ�ǰ����
}
void deletedisabledorder() {
	Order* p;
	Order* q;
	p = ohead;
	int m = 0;
	q = p->onext;
	while (q != NULL) {
		if (Check_date3(q->year[1], q->mon[1], q->day[1], q->hour[1]) != 1)//�ж϶����Ƿ�ʧЧ
		{
			emptyroom(q->room_->roomnumber);//�ѷ���״̬���
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
	if (m != 0)printf("ʧЧ������ɾ��\n");
	else
		printf("��ǰ��ʧЧ����\n");
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
			t[i + 1] = '\0';//��ӻ��з�
			break;
		}
	}
}
void changeorder()//�޸Ķ���
{
	system("cls");
	char phonenumber_[20];
	char id[40];
	Order* p;
	char num[20];
	int m = 0, m1 = 0;
	if (ohead->onext == NULL)
	{
		printf("����Ϊ���޸�ʧ��\n");
		system("pause");
	}
	else
	{
		p = ohead->onext;
		char nam[20];
		printf("�����޸Ķ����Ŀͻ���������");
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
				printf("�ѵ���ס�����޷��޸�");
				system("pause");
			}
			else while (1)
			{
				system("cls");
				printf("1.�޸�����\n");
				printf("2.�޸ĵ绰\n");
				printf("3.�޸����֤��\n");
				printf("4.�޸���סʱ��\n");
				printf("5.�޸��뿪ʱ��\n");
				printf("6.�˳��޸�\n");
				printf("����Ҫ�޸ĵ�ѡ��:\n");
				fflush(stdin);
				rewind(stdin);
				gets(num);
				while ((strcmp(num, "1") != 0) && (strcmp(num, "2") != 0) && (strcmp(num, "3") != 0) && (strcmp(num, "4") != 0) && (strcmp(num, "5") != 0) && (strcmp(num, "6") != 0)) {
					printf("ѡ����������������:");
					fflush(stdin);
					rewind(stdin);
					gets(num);
				}
				if (strcmp(num, "1") == 0)
				{
					printf("�����µ�������");
					checkchar(p->room_->u.name);
					gets(nam);
					while (strcmp(p->room_->u.name, nam) == 0) {
						printf("����δ���ģ�����������:");
						scanf("%s", nam);
					}
					checkchar1(nam);//���ϻ��з����ܱȽ�
					strcpy(p->room_->u.name, nam);
					printf("�޸ĳɹ�\n");
				}
				if (strcmp(num, "2") == 0)
				{
					printf("�����µĵ绰��");
					checkchar(p->room_->u.phonenumber);
					scanf("%s", phonenumber_);
					while (strlen(phonenumber_) != 11 || judgephone(phonenumber_) != 0 || strcmp(p->room_->u.phonenumber, phonenumber_) == 0) {
						printf("�绰�Ų�����Ҫ������������:");
						scanf("%s", phonenumber_);
					}
					checkchar1(phonenumber_);//���ϻ��з����ܱȽ�
					strcpy(p->room_->u.phonenumber, phonenumber_);
					printf("�޸ĳɹ�\n");
				}
				if (strcmp(num, "3") == 0)
				{
					printf("�����µ����֤�ţ�");
					checkchar(p->room_->u.idcard);
					fflush(stdin);
					rewind(stdin);
					scanf("%s", id);
					while (strlen(id) != 18 || judgeid(id) != 0 || strcmp(p->room_->u.idcard, id) == 0) {
						printf("���֤�����ʽ��������������:");
						fflush(stdin);
						rewind(stdin);
						scanf("%s", id);
					}
					checkchar1(id);//���ϻ��з����ܱȽ�
					strcpy(p->room_->u.idcard, id);
					printf("�޸ĳɹ�\n");
				}
				if (strcmp(num, "4") == 0)
				{
					if (Check_date1(p->year, p->mon, p->day, p->hour) == 0) {
						printf("��������סʱ�䣺������ʱ(24ʱ���м�����/������");
						fflush(stdin);
						rewind(stdin);
						while ((scanf("%d/%d/%d/%d", &p->year[0], &p->mon[0], &p->day[0], &p->hour[0]) != 4) || Check_date1(p->year, p->mon, p->day, p->hour) != 0 || Check_date2(p->year, p->mon, p->day, p->hour) != 0) {
							if (Check_date2(p->year, p->mon, p->day, p->hour) != 0) {
								printf("���޸��뿪ʱ�䣺������ʱ(24ʱ���м�����/������");
								fflush(stdin);
								rewind(stdin);
								while ((scanf("%d/%d/%d/%d", &p->year[1], &p->mon[1], &p->day[1], &p->hour[1]) != 4) || Check_date2(p->year, p->mon, p->day, p->hour) != 0) {
									printf("������������");
									printf("�����������뿪ʱ�䣺������ʱ(24ʱ���м�����/������");
									fflush(stdin);
									rewind(stdin);
								}break;
							}
							else {
								printf("������������\n");
								printf("������������סʱ�䣺������ʱ(24ʱ���м�����/������");
							
							fflush(stdin);
							rewind(stdin);}
						}

						printf("�޸ĳɹ�\n");
					}
				}
				if (strcmp(num, "5") == 0) {
					printf("�������뿪ʱ�䣺������ʱ(24ʱ���м�����/������");
					fflush(stdin);
					rewind(stdin);
					while ((scanf("%d/%d/%d/%d", &p->year[1], &p->mon[1], &p->day[1], &p->hour[1]) != 4) || Check_date2(p->year, p->mon, p->day, p->hour) != 0) {
						printf("������������");
						printf("�����������뿪ʱ�䣺������ʱ(24ʱ���м�����/������");
						fflush(stdin);
						rewind(stdin);
					}
					printf("�޸ĳɹ�\n");
				}
				if (strcmp(num, "6") == 0)break;
				system("pause");
			}

		}
		if (m == 0)printf("�ÿ��˲��ڶ�����\n");
		printf("\n");
		system("pause");
	}
}
void deleteorder() {
	char nam[20];
	system("cls");
	if (ohead->onext == NULL)
	{
		printf("û�п�ɾ���Ķ���\n");
		system("pause");
	}
	else {
		printf("��������Ҫɾ���Ķ�����������");
		fflush(stdin);
		rewind(stdin);
		gets(nam);
		checkchar1(nam);//���ϻ��з����ܱȽ�
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
				printf("��ɾ���ö���\n");
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
	fgets(s, 14, fp);//ȡ������
	rewind(fp);//ָ��ص��ļ���ͷ
	fclose(fp);
	fp = fopen("password.txt", "w");
	printf("������ԭ����:\n");
	fflush(stdin);
	rewind(stdin);
	gets(c);
	while (strcmp(c, s) != 0) {
		printf("ԭ�����������\n����������");
		fflush(stdin);
		rewind(stdin);
		gets(c);
	}
	if (strcmp(c, s) == 0) {
		printf("�����������루6~14λ��:\n");
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
	}//�ж���ĸ���ֺ������ַ��ĸ���

	while (i < 6 || i >= 15 || a == 0 || b == 0 || e == 0|| strcmp(n, s) == 0) {

		if (strcmp(n, s) == 0)printf("\n��ԭ������ͬ\n���������룺");
		else printf("\n��ȫ�Բ��߻�λ��������Ҫ��\n���������룺\n");
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
	}//�ж���ĸ���ֺ������ַ��ĸ���}
	 
	fputs(n, fp);
	fclose(fp);
	printf("\n�����޸ĳɹ�\n");
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

	printf("��ɫ�б�1=��ɫ 2=��ɫ 3=����ɫ 4=��ɫ\n5=��ɫ 6=��ɫ 7=��ɫ 8=��ɫ\n9=����ɫ 10=����ɫ 11=��ǳ��ɫ 12=����ɫ\n13=����ɫ 14=����ɫ 15=����ɫ\n");
	printf("��ѡ����Ӧ���ָı�ϵͳ��ɫ");

	scanf("%d", &a);
	while (a < 1 || a>15) { printf("����������������������\n");  scanf("%d", &a); }
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

	}fclose(p); printf("\n��ɫ�޸ĳɹ�\n");
	system("pause");

}
void search2()
{
	system("cls");
	Order* p;
	int m;
	if (ohead->onext == NULL)
	{
		printf("�޶���������ʧ��\n");
		system("pause");
	}
	else
	{
		while (1) {
			system("cls");
			printf("ѡ����ҷ�ʽ��(1~4)\n");
			printf("1.����������\n");
			printf("2.���绰����\n");
			printf("3.�����֤�Ų���\n");
			printf("4.������Ų���\n");
			printf("5.������һ��\n");
			char t[20];
			fflush(stdin);
			rewind(stdin);
			gets(t);
			while ((strcmp(t, "1") != 0) && (strcmp(t, "2") != 0) && (strcmp(t, "3") != 0) && (strcmp(t, "4") != 0) && (strcmp(t, "5") != 0)) {
				printf("ѡ����������������:");
				fflush(stdin);
				rewind(stdin);
				gets(t);
			}
			if (strcmp(t, "1") == 0)
			{
				m = 0;
				p = ohead->onext;
				printf("������ҵ�������");
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
						printf("\n������%s\n", p->room_->u.name);
						printf("\n�绰��%s\n", p->room_->u.phonenumber);
						printf("���֤�ţ�%s\n", p->room_->u.idcard);
						printf("�����: %s\n", p->room_->roomnumber);
						printf("��ס���ڣ�%d/%d/%d/%d\n", p->year[0], p->mon[0], p->day[0], p->hour[0]);
						printf("�뿪���ڣ�%d/%d/%d/%d\n", p->year[1], p->mon[1], p->day[1], p->hour[1]);

					}
					p = p->onext;
				}

				if (m == 0)
					printf("�����û�������\n");
				system("pause");

			}
			if (strcmp(t, "2") == 0)
			{
				m = 0;
				p = ohead->onext;
				char ph[20];
				printf("������ҵĵ绰��");
				fflush(stdin);
				rewind(stdin);
				gets(ph);
				while (strlen(ph) != 11 || judgephone(ph) != 0)
				{//�жϵ绰�ź��Ƿ���Ϲ���
					printf("�绰�Ų�����Ҫ������������:");
					fflush(stdin);
					rewind(stdin);
					scanf("%s", ph);
				}
				checkchar1(ph);
				while (p != NULL && strcmp(ph, p->room_->u.phonenumber) == 0) {
					//�ҵ��绰һ�µĿ���
					if (strcmp(ph, p->room_->u.phonenumber) == 0)
					{
						m++;
						printf("\n������%s\n", p->room_->u.name);
						printf("\n�绰��%s\n", p->room_->u.phonenumber);
						printf("���֤�ţ�%s\n", p->room_->u.idcard);
						printf("�����: %s\n", p->room_->roomnumber);
						printf("��ס���ڣ�%d/%d/%d/%d\n", p->year[0], p->mon[0], p->day[0], p->hour[0]);
						printf("�뿪���ڣ�%d/%d/%d/%d\n", p->year[1], p->mon[1], p->day[1], p->hour[1]);

					}
					p = p->onext;
				}
				if (m == 0)
					printf("���Һ��벻����\n");
				system("pause");

			}
			if (strcmp(t, "3") == 0)
			{
				char id[18];
				printf("����Ҫ���ҵ����֤�ţ�");
				fflush(stdin);
				rewind(stdin);
				gets(id);
				while (strlen(id) != 18 || judgeid(id) != 0) {//�ж����֤���Ƿ���Ϲ���
					printf("���֤�����ʽ��������������:");
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
						printf("\n������%s\n", p->room_->u.name);
						printf("\n�绰��%s\n", p->room_->u.phonenumber);
						printf("���֤�ţ�%s\n", p->room_->u.idcard);
						printf("�����: %s\n", p->room_->roomnumber);
						printf("��ס���ڣ�%d/%d/%d/%d\n", p->year[0], p->mon[0], p->day[0], p->hour[0]);
						printf("�뿪���ڣ�%d/%d/%d/%d\n", p->year[1], p->mon[1], p->day[1], p->hour[1]);
					}
					p = p->onext;
				}
				if (m == 0)
					printf("���Һ��벻����\n");
				system("pause");
			}
			if (strcmp(t, "4") == 0)
			{
				char roomnum[20];
				printf("����Ҫ���ҵķ���ţ����Ƶ귿���101~112��201~208��301~304��401~403����");
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
						printf("\n������%s\n", p->room_->u.name);
						printf("\n�绰��%s\n", p->room_->u.phonenumber);
						printf("���֤�ţ�%s\n", p->room_->u.idcard);
						printf("�����: %s\n", p->room_->roomnumber);
						printf("��ס���ڣ�%d/%d/%d/%d\n", p->year[0], p->mon[0], p->day[0], p->hour[0]);
						printf("�뿪���ڣ�%d/%d/%d/%d\n", p->year[1], p->mon[1], p->day[1], p->hour[1]);

					}
					p = p->onext;

				}
				if (m == 0)
					printf("����δ��ʹ�û�δ������ȷ�����\n");
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
		printf("�޷��䣬����ʧ��\n");
		system("pause");
	}
	else
	{
		while (1) {
			system("cls");
			printf("�������ѯ��ʽ:\n");
			printf("1.����״̬��ѯ\n");
		 
			printf("2.����״̬�ͷ���������ϲ�ѯ\n");
			printf("3.������һ��\n");
			char t[20];
			fflush(stdin);
			rewind(stdin);
			gets(t);
			while ((strcmp(t, "1") != 0) && (strcmp(t, "2") != 0) && (strcmp(t, "3") != 0)) {
				printf("ѡ����������������:");
				fflush(stdin);
				rewind(stdin);
				gets(t);
			}
			if (strcmp(t, "1") == 0) {
				system("cls");
				printf("���÷�:");
				printf("\n");
				for (p = rhead->rnext; p->rnext != NULL; p = p->rnext)if (p->flag == 0) {
					printf("%s", p->roomnumber); flag1++;
				}
				printf("\n");
				if (flag1 == 0)printf("��");
				printf("��ռ�÷�");
				printf("\n");
				for (p = rhead->rnext; p->rnext != NULL; p = p->rnext)if (p->flag != 0) {
					printf("%s", p->roomnumber); flag2++;
				}
				if (flag2 == 0)printf("��");
				printf("\n");
			}
			 
			
			if (strcmp(t, "2") == 0) {
				while (1) {
					system("cls");
					char n[20];
					printf("��ѡ���ѯ���ͣ�\n1.���˼�\n2.˫�˼�\n3.���˼�\n4.���˼�\n5.������һ��\n");
					fflush(stdin);
					rewind(stdin);
					gets(n);

					while (strcmp(n, "1") != 0 && strcmp(n, "2") != 0 && strcmp(n, "3") != 0 && strcmp(n, "4") != 0 && strcmp(n, "5") != 0) {
						printf("ѡ������������ѡ��");
						fflush(stdin);
						rewind(stdin);
						gets(n);
					}
					if (strcmp(n, "1") == 0) {
						printf("�շ��У�\n");
						for (p = rhead->rnext; p != NULL; p = p->rnext)
							if (p->flag == 0 && strcmp(p->type, "single\n") == 0)
							{
								count1++; printf("%s", p->roomnumber);
							}
						printf("\n");
						printf("���˼仹ʣ%d��", count1);
					}
					if (strcmp(n, "2") == 0) {
						printf("�շ��У�\n");
						for (p = rhead->rnext; p != NULL; p = p->rnext)if (p->flag == 0 && strcmp(p->type, "double\n") == 0)
						{
							count2++; printf("%s", p->roomnumber);
						}
						printf("\n");
						printf("˫�˼仹ʣ%d��", count2);
					}
					if (strcmp(n, "3") == 0) {
						printf("�շ��У�\n");
						for (p = rhead->rnext; p != NULL; p = p->rnext)if (p->flag == 0 && strcmp(p->type, "triple\n") == 0)
						{
							count3++; printf("%s", p->roomnumber);
						}
						printf("���˼仹ʣ%d��", count3);
					}
					if (strcmp(n, "4") == 0) {
						printf("�շ��У�\n");
						for (p = rhead->rnext; p != NULL; p = p->rnext)if (p->flag == 0 && strcmp(p->type, "four\n") == 0)
						{
							count4++; printf("%s", p->roomnumber);
						}
						printf("\n");
						printf("���˼仹ʣ%d��", count4);
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
		printf("�޶���\n");
		system("pause");
	}
	else {
		printf("�������ֹ���� ������ʱ(24ʱ���м�����/������\n");
		fflush(stdin);
		rewind(stdin);

		while ((scanf("%d/%d/%d/%d", &year, &mon, &day, &hour)) != 4 || Check_date4(year, mon, day, hour) == 1)
		{
			printf("��������Чʱ��");
			fflush(stdin);
			rewind(stdin);
		}
		printf("�ڸ�����ǰ��Ч�Ķ�����\n");
		for (e = ohead->onext; e != NULL; e = e->onext)if (time_1(year, mon, day, hour, e) == -1 || time_1(year, mon, day, hour, e) == 0) {
			printf("\n������%s", e->room_->u.name);
			printf("�绰��%s", e->room_->u.phonenumber);
			printf("���֤�ţ�%s", e->room_->u.idcard);
			printf("�����: %s", e->room_->roomnumber);
			printf("��ס���ڣ�%d/%d/%d/%d\n", e->year[0], e->mon[0], e->day[0], e->hour[0]);
			printf("�뿪���ڣ�%d/%d/%d/%d\n", e->year[1],e->mon[1], e->day[1], e->hour[1]);
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
		fgets(p->roomnumber, 20, fp);//�������Ļ��л��з�
		//printf("%s\n",p->roomnumber);
		fgets(p->type, 20, fp);//�������Ļ��л��з�
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
			fgets(p1->room_->roomnumber, 40, fp1);//�������Ļ��л��з�
			fgets(p1->room_->type, 10, fp1);//�������Ļ��л��з�
			fgets(p1->room_->u.name, 40, fp1);//�������Ļ��л��з�
			fgets(p1->room_->u.idcard, 20, fp1);//�������Ļ��л��з�
			fgets(p1->room_->u.phonenumber, 20, fp1);//�������Ļ��л��з�
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
		fputs(p->room_->roomnumber, fp);//�����з�һ�𱣴�
		fputs(p->room_->type, fp);//�����з�һ�𱣴�
		fputs(p->room_->u.name, fp);//�����з�һ�𱣴�
		fputs(p->room_->u.idcard, fp);//�����з�һ�𱣴�
		fputs(p->room_->u.phonenumber, fp);//�����з�һ�𱣴�
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
	if (fclose(fp1) == 0 && fclose(fp) == 0)printf("���ݳɹ�\n");
	else
		printf("����ʧ��\n");
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