#include "stdafx.h"
#pragma warning(disable : 4996)
#pragma warning(disable : 4267)
#include "system.h"
#include "afxdialogex.h"
#include<time.h>
#include <iostream>
using namespace std;

void insert(char *s1, char *s2, int n)
{
	int len1 = 0, len2 = 0, j = 0, k = 0;
	char s4[400];
	len1 = strlen(s1);
	len2 = strlen(s2);
	for (int i = 0; i < n; i++)
	{
		j++;
	}
	for (int i = 0; i < len1; i++)
	{
		s4[k++] = s1[i];
	}
	for (int i = 0; i < len2; i++)
		s1[j++] = s2[i];

	for (int i = n; i < len1; i++)
		s1[j++] = s4[i];

	s1[j] = '\0';
}
//���ߵ�¼ʱ�˶��˺��Ƿ�����������Ƿ���ȷ
bool Rlogin(MYSQL * con,char *account,char* password)//account��Identity����˺ţ�password������
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char tmp[400];
	char tmp1[400];
	int x = 0, rt;
	int t = 0;
	sprintf_s(tmp, "select * from Identity where Account='");
	sprintf_s(tmp1, account);
	x = strlen(tmp);
	insert(tmp, tmp1, x);
	sprintf_s(tmp1, "' and Password='");
	x = strlen(tmp);
	insert(tmp, tmp1, x);
	sprintf_s(tmp1, password);
	x = strlen(tmp);
	insert(tmp, tmp1, x);
	sprintf_s(tmp1, "'");
	insert(tmp, tmp1, strlen(tmp));
	x = strlen(tmp);
	rt = mysql_real_query(con, tmp,x);
	if (rt){
		MessageBox(NULL,"�д���",NULL,NULL);
		return false;
	}
	res = mysql_store_result(con);//�����������res�ṹ����
	if (row = mysql_fetch_row(res)) {
		return true;
	}
	else {
		return false;
	}
}
//����Ա��¼ʱ�˶��˺��Ƿ�����������Ƿ���ȷ
bool Mlogin(MYSQL * con, char *account, char* password)//account�ǹ���Ա���˺ţ�password�ǹ���Ա������
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char tmp[400];
	char tmp1[400];
	int x = 0, rt;
	int t = 0;
	sprintf_s(tmp, "use mysql");
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt) {
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	sprintf_s(tmp, "select * from Manager where MNo='");
	sprintf_s(tmp1, account);
	x = strlen(tmp);
	insert(tmp, tmp1, x);
	sprintf_s(tmp1, "' and MCode='");
	x = strlen(tmp);
	insert(tmp, tmp1, x);
	sprintf_s(tmp1, password);
	x = strlen(tmp);
	insert(tmp, tmp1, x);
	sprintf_s(tmp1, "'");
	insert(tmp, tmp1, strlen(tmp));
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt) {
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	res = mysql_store_result(con);//�����������res�ṹ����
	if (row = mysql_fetch_row(res)) {
		return true;
	}
	else {
		return false;
	}
}

//���Ĳ���
bool borrowBook(MYSQL * con,char * account,char * bookNo)//���account�ǽ���֤�ţ������ߵĵ�¼�˺ţ���bookNo�����
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char tmp[400];
	char tmp1[400];
	int x = 0, rt;
	int t = 0;
	sprintf_s(tmp, "use mysql");
	rt = mysql_real_query(con, tmp, strlen(tmp));
	//����Ƿ�ɽ���
	sprintf_s(tmp, "select bigNum from Identity where Account='");
	sprintf_s(tmp1, account);
	x = strlen(tmp);
	insert(tmp, tmp1, x);
	sprintf_s(tmp1, "'");
	insert(tmp, tmp1, strlen(tmp));
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	res = mysql_store_result(con);//�����������res�ṹ����
	row = mysql_fetch_row(res);
	if (row[0]==0) 
	{
		MessageBox(NULL,"�����Ѵ����ޣ�", NULL, NULL);
		return false;
	}
	//�������Ƿ���ȷ����������Խ�
	sprintf_s(tmp, "select BNu from Book where BNo='");
	sprintf_s(tmp1, bookNo);
	x = strlen(tmp);
	insert(tmp, tmp1, x);
	sprintf_s(tmp1, "'");
	insert(tmp, tmp1, strlen(tmp));
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	res = mysql_store_result(con);//�����������res�ṹ����
	if (row = mysql_fetch_row(res))
	{
		if (row[0] == 0) {
			MessageBox( NULL,"�鱾�Ѿ����꣡" ,NULL,NULL);
			return false;
		}
		//ͼ�����1
		sprintf_s(tmp, "update Book set BNu=BNu-1 where BNo='");
		sprintf_s(tmp1, bookNo);
		x = strlen(tmp);
		insert(tmp, tmp1, x);
		sprintf_s(tmp1, "'");
		insert(tmp, tmp1, strlen(tmp));
		rt = mysql_real_query(con, tmp,strlen(tmp));
		if (rt)
		{
			MessageBox(NULL, "�д���", NULL, NULL);
			return false;
		}
		//��������������1
		sprintf_s(tmp, "update Identity set bigNum=bigNum-1 where Account='");
		sprintf_s(tmp1, account);
		x = strlen(tmp);
		insert(tmp, tmp1, x);
		sprintf_s(tmp1, "'");
		insert(tmp, tmp1, strlen(tmp));
		rt = mysql_real_query(con, tmp,strlen(tmp));
		if (rt)
		{
			MessageBox(NULL, "�д���", NULL, NULL);
			return false;
		}
		//���뵽���ı�
		char tmp2[400];
		sprintf_s(tmp, "insert into Person values (')");
		sprintf_s(tmp1, account);
		sprintf_s(tmp2, "','");
		insert(tmp1, tmp2, strlen(tmp1));

		char tmp3[400];
		sprintf_s(tmp3, "select PIdentity from Identity where Account='");
		sprintf_s(tmp2, account);
		x = strlen(tmp3);
		insert(tmp3, tmp2, x);
		sprintf_s(tmp2, "'");
		insert(tmp3, tmp2, strlen(tmp3));
		rt = mysql_real_query(con, tmp3, strlen(tmp3));
		if (rt)
		{
			MessageBox(NULL, "�д���", NULL, NULL);
			return false;
		}
		res = mysql_store_result(con);
		row = mysql_fetch_row(res);
		insert(tmp1, row[0], strlen(tmp1));
		sprintf_s(tmp2, "','�ޱ�ע','");
		insert(tmp1, tmp2, strlen(tmp1));
		sprintf_s(tmp2, bookNo);
		insert(tmp1, tmp2, strlen(tmp1));
		sprintf_s(tmp2, "','");
		insert(tmp1, tmp2, strlen(tmp1));

		time_t timep;
		struct tm *p;
		time(&timep);
		p = gmtime(&timep);
		char date[9];
		date[0] = char((1900 + p->tm_year) / 1000 + '0');
		int n1 = (1900 + p->tm_year) / 1000;
		date[1] = char(((1900 + p->tm_year) - n1 * 1000) / 100 + '0');
		int n2 = ((1900 + p->tm_year) - n1 * 1000) / 100;
		date[2] = char(((1900 + p->tm_year) - n1 * 1000 - n2 * 100) / 10 + '0');
		date[3] = char((1900 + p->tm_year) % 10 + '0');
		date[4] = char((1 + p->tm_mon) / 10 + '0');
		date[5] = char((1 + p->tm_mon) % 10 + '0');
		date[6] = char((p->tm_mday) / 10 + '0');
		date[7] = char(((p->tm_mday) % 10) + '0');
		date[8] = '\0';
		insert(tmp1, date, strlen(tmp1));
		sprintf_s(tmp2, "'");
		insert(tmp1, tmp2, strlen(tmp1));
		x = strlen(tmp) - 1;
		insert(tmp, tmp1, x);
		rt = mysql_real_query(con, tmp,strlen(tmp));
		if (rt)
		{
			MessageBox(NULL, "�д���", NULL, NULL);
		}
		else
		{
			MessageBox(NULL,"���ĳɹ�!", NULL, NULL);
		}
	}
    else 
    {
		MessageBox(NULL,"û�д��飡",NULL,NULL);
	    return false;
    }
	return true;
}

//����������֮������˼���
int day_diff(int year_start, int month_start, int day_start, int year_end, int month_end, int day_end)
{
	int y1, m1, d1;
	int y2, m2, d2;
	m1 = (month_start + 9) % 12;
	y1 = year_start - m1 / 10;
	d1 = 365 * y1 + y1 / 4 - y1 / 100 + y1 / 400 + (m1 * 306 + 5) / 10 + (day_start - 1);
	m2 = (month_end + 9) % 12;
	y2 = year_end - m2 / 10;
	d2 = 365 * y2 + y2 / 4 - y2 / 100 + y2 / 400 + (m2 * 306 + 5) / 10 + (day_end - 1);
	return (d2 - d1);
}

//�������
bool returnBook(MYSQL * con,char * account, char * bookNo)//account�ǻ�����˵Ľ���֤�ţ�����¼�˺ţ���bookNo�����
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char tmp[400];
	char tmp1[400];
	char tmp2[400];
	int x = 0, rt;
	int t = 0;
	//����Ƿ���Ҫ����
	//��ȡ��ǰ����
	int days = 0;
	time_t timep;
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);
	int year_end = 1900 + p->tm_year;
	int month_end = 1 + p->tm_mon;
	int day_end = p->tm_mday;
	//��ȡ��������
	sprintf_s(tmp, "select SDate from Person where SNo='");
	sprintf_s(tmp1, account);
	sprintf_s(tmp2, "' and BNo='");
	insert(tmp1, tmp2, strlen(tmp1));
	sprintf_s(tmp2, bookNo);
	insert(tmp1, tmp2, strlen(tmp1));
	sprintf_s(tmp2, "'");
	insert(tmp1, tmp2, strlen(tmp1));
	insert(tmp, tmp1, strlen(tmp));
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	res = mysql_store_result(con);
	row = mysql_fetch_row(res);
	char *date = row[0];
	int year_start = int(date[0]) * 1000 + int(date[1]) * 100 + int(date[2]) * 10 + int(date[3]);
	int month_start = int(date[4]) * 10 + int(date[5]);
	int day_start = int(date[6]) * 10 + int(date[7]);

	days = day_diff(year_start,month_start,day_start,year_end,month_end,day_end);
	if (days > 60) {
		MessageBox (NULL, "δ��ʱ���飬�跣�� !",NULL,NULL);
		return false;
	}
	else {
		MessageBox( NULL,"��ʱ���飬���跣��" ,NULL,NULL);
		return false;
	}
	//ͼ�����1
	sprintf_s(tmp, "update Book set BNu=BNu+1 where BNo='");
	sprintf_s(tmp1, bookNo);
	x = strlen(tmp);
	insert(tmp, tmp1, x);
	sprintf_s(tmp1, "'");
	insert(tmp, tmp1, strlen(tmp));
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	//��������������1
	sprintf_s(tmp, "update Identity set bigNum=bigNum+1 where Account='");
	sprintf_s(tmp1, account);
	x = strlen(tmp);
	insert(tmp, tmp1, x);
	sprintf_s(tmp1, "'");
	insert(tmp, tmp1, strlen(tmp));
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	//�ӽ��ı�ɾ��
	sprintf_s(tmp, "delete from Person where SNo='");
	sprintf_s(tmp1, account);
	sprintf_s(tmp2, "' and BNo='");
	insert(tmp1, tmp2, strlen(tmp1));
	sprintf_s(tmp2, bookNo);
	insert(tmp1, tmp2, strlen(tmp1));
	insert(tmp, tmp1, strlen(tmp));
	sprintf_s(tmp1, "'");
	insert(tmp, tmp1, strlen(tmp));
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	else
	{
		MessageBox(NULL,"����ɹ�!",NULL,NULL);
	}
	return true;
}

//����ͼ����Ϣ
bool enterBook(MYSQL * con,char *tmp1,char* tmp2,char* tmp3,char* tmp4,char* tmp5,char* tmp6,char* tmp7,char* tmp8,char* tmp9)
{
	char tmp[400];
	int rt;
	sprintf_s(tmp, "insert into Book values ('','',,'','',,'','','')");
	if (tmp1 == "" || tmp6 == "")
	{
		MessageBox ( NULL,"ͼ���Ż�ͼ�����Ͳ���Ϊ��",NULL,NULL);
		return false;
	}
	insert(tmp, tmp1, strlen(tmp) - 22);
	insert(tmp, tmp2, strlen(tmp) - 19);
	insert(tmp, tmp3, strlen(tmp) - 17);
	insert(tmp, tmp4, strlen(tmp) - 15);
	insert(tmp, tmp5, strlen(tmp) - 12);
	insert(tmp, tmp6, strlen(tmp) - 10);
	insert(tmp, tmp7, strlen(tmp) - 8);
	insert(tmp, tmp8, strlen(tmp) - 5);
	insert(tmp, tmp9, strlen(tmp) - 2);
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		MessageBox(NULL, "�д���", NULL, NULL);
	}
	else
	{
		MessageBox(NULL,"����ɹ�!", NULL, NULL);
		return true;
	}
}

//�����Ա��Ϣ������Աע��
bool enterVip(MYSQL * con,char* tmp1,char* tmp2,char* tmp3,char* tmp4)
{
	char tmp[400];
	int rt;
	sprintf_s(tmp, "insert into Vip values ('','',,'')");

	if (strcmp(tmp1, "") == 0)
	{
		MessageBox(NULL,"��Ա�Ų���Ϊ��,����ʧ��!", NULL, NULL);
		return false;
	}
	insert(tmp, tmp1, strlen(tmp) - 9);
	insert(tmp, tmp2, strlen(tmp) - 6);
	insert(tmp, tmp3, strlen(tmp) - 4);
	insert(tmp, tmp4, strlen(tmp) - 2);
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	else
	{
		//�޸�identity�������ݺ���������
		char tmp5[400];
		sprintf_s(tmp, "update Identity set PIdentity='��ͨ����' where Account='");
		insert(tmp, tmp1, strlen(tmp));
		sprintf_s(tmp5, "'");
		insert(tmp, tmp5, strlen(tmp));
		rt = mysql_real_query(con, tmp, strlen(tmp));
		if (rt)
		{
			MessageBox(NULL, "�д���", NULL, NULL);
			return false;
		}
		sprintf_s(tmp, "update Identity set bigNum=3 where Account='");
		insert(tmp, tmp1, strlen(tmp));
		sprintf_s(tmp5, "'");
		insert(tmp, tmp5, strlen(tmp));
		rt = mysql_real_query(con, tmp, strlen(tmp));
		if (rt)
		{
			MessageBox(NULL, "�д���", NULL, NULL);
			return false;
		}
		MessageBox(NULL,"����ɹ�!", NULL, NULL);
		return true;
	}
}

//ɾ��ͼ����Ϣ
bool delBook(MYSQL * con, char * BNo)//BNo:���
{
	char tmp[400];
	char tmp1[400];
	int rt;
	sprintf_s(tmp, "delete from Book where BNo='");
	insert(tmp, BNo, strlen(tmp));
	sprintf_s(tmp1, "'");
	insert(tmp, tmp1, strlen(tmp));
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	else
	{
		MessageBox(NULL,"ɾ���ɹ�!",NULL,NULL);
		return true;
	}
}

//ɾ����Ա��Ϣ
bool delVip(MYSQL * con, char * VNo)//VNo:��¼�˺�
{
	char tmp[400];
	char tmp1[400];
	int rt;
	sprintf_s(tmp, "use mysql");
	rt = mysql_real_query(con, tmp, strlen(tmp));
	sprintf_s(tmp, "delete from Vip where VNo='");
	insert(tmp, VNo, strlen(tmp));
	sprintf_s(tmp1, "'");
	insert(tmp, tmp1, strlen(tmp));
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	else
	{
		//�޸�identity�������ݺ���������
		char tmp1[400];
		sprintf_s(tmp, "update Identity set PIdentity='��ͨ����' where Account='");
		insert(tmp, VNo, strlen(tmp));
		sprintf_s(tmp1, "'");
		insert(tmp, tmp1, strlen(tmp));
		rt = mysql_real_query(con, tmp, strlen(tmp));
		if (rt)
		{
			MessageBox(NULL, "�д���", NULL, NULL);
			return false;
		}
		sprintf_s(tmp, "update Identity set bigNum=1 where Account='");
		insert(tmp, VNo, strlen(tmp));
		sprintf_s(tmp1, "'");
		insert(tmp, tmp1, strlen(tmp));
		rt = mysql_real_query(con, tmp, strlen(tmp));
		if (rt)
		{
			MessageBox(NULL, "�д���", NULL, NULL);
			return false;
		}
		MessageBox(NULL,"ɾ���ɹ�!",NULL,NULL);
		return true;
	}
}

MYSQL *getConnect() {
	MYSQL * con; 
	char dbuser[30] = "root";
	char dbpasswd[30] = "system";
	char dbip[30] = "localhost";
	char dbname[50] = "mysql";

	char tablename[50] = "book";
	const char *query = NULL;

	int x;
	int y;
	int rt;//return value  

	int count = 0;

	con = mysql_init((MYSQL*)0);

	if (con != NULL && mysql_real_connect(con, dbip, dbuser, dbpasswd, dbname, 3306, NULL, 0)) {
		if (!mysql_select_db(con, dbname)) {
			MessageBox(NULL,"�������ݿ�ɹ�!",NULL,NULL);
			con->reconnect = 1;
			query = "set names \'GBK\'";
			rt = mysql_real_query(con, query, strlen(query));
			if (rt) {
				MessageBox(NULL, "�������ݿ�ʧ��!", NULL, NULL);
			}
			else {
				MessageBox(NULL, "�������ݿ�ɹ�!", NULL, NULL);
			}
		}
	}
	else {
		MessageBox(NULL, "�������ݿ�ʧ��!", NULL, NULL);
	}
	mysql_autocommit(con, 1);


	int finish = 0;
	int choice;
	char tmp[400];
	bool passFlag = false;
	char account[50] = "13922387344";////ǰ������
	char account2[50] = "20172137899";
	char password[50] = "tiger";////ǰ������
	char bookNo[50] = "01";////ǰ������
	rt = mysql_real_query(con, "use mysql", strlen("use mysql"));
	if (rt) {
		MessageBox(NULL, "�д���", NULL, NULL);
		return 0;
	}
	return con;
}

//�༭��Ա��Ϣ(1)��ȡ��Աԭ���������ͽ�ֹ����
MYSQL_RES* reVcard1(MYSQL * con, char* account)//account�ǻ�Ա��VNo
{
	MYSQL_RES *res=NULL;
	char tmp[400];
	char tmp1[400];
	int x = 0, rt;
	sprintf_s(tmp, "select VNa,VBdate from Vip where VNo='");
	sprintf_s(tmp1, account);
	insert(tmp, tmp1, strlen(tmp));
	sprintf_s(tmp1, "'");
	insert(tmp, tmp1, strlen(tmp));
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt) {
		MessageBox(NULL, "�д���", NULL, NULL);
		return NULL;
	}
	res = mysql_store_result(con);
	return res;
}

//�༭��Ա��Ϣ(2)����Ա�µ������ͽ�ֹ����д�����ݿ�
bool reVcard2(MYSQL * con,char*vno, char* vname, char* vbdate) //vanme:��������vbdate:������
{
	char tmp[400];
	char tmp1[400];
	int x = 0, rt;
	sprintf_s(tmp, "update Vip set VNa='");
	sprintf_s(tmp1, vname);
	insert(tmp, tmp1, strlen(tmp));
	sprintf_s(tmp1, "' where VNo='");
	insert(tmp, tmp1, strlen(tmp));
	sprintf_s(tmp1, vno);
	insert(tmp, tmp1, strlen(tmp));
	sprintf_s(tmp1, "'");
	insert(tmp, tmp1, strlen(tmp));
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt) {
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	sprintf_s(tmp, "update Vip set VBdate='");
	sprintf_s(tmp1, vbdate);
	insert(tmp, tmp1, strlen(tmp));
	sprintf_s(tmp1, "' where VNo='");
	insert(tmp, tmp1, strlen(tmp));
	sprintf_s(tmp1, vno);
	insert(tmp, tmp1, strlen(tmp));
	sprintf_s(tmp1, "'");
	insert(tmp, tmp1, strlen(tmp));
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt) {
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	else
	{
		return true;
	}
}

//��ӡ��Ա��
MYSQL_RES* printV(MYSQL * con, char *vno) //vno:��Ա��
{
	MYSQL_RES* res = NULL;
	char tmp[400];
	char tmp1[400];
	int x = 0, rt;
	sprintf_s(tmp, "select * from Vip where VNo='");
	sprintf_s(tmp1, vno);
	insert(tmp, tmp1, strlen(tmp));
	sprintf_s(tmp1, "'");
	insert(tmp, tmp1, strlen(tmp));
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt) {
		MessageBox(NULL, "�д���", NULL, NULL);
		return NULL;
	}
	res = mysql_store_result(con);
	return res;
}

//���ɴ߻��鱨��
MYSQL_RES* creRep(MYSQL * con) 
{
	MYSQL_RES* res = NULL;
	MYSQL_RES* res1 = NULL;
	MYSQL_ROW row;
	char tmp[400];
	char tmp1[400];
	int x = 0, rt;
	int days = 0;
	time_t timep;
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);
	int year_end = 1900 + p->tm_year;
	int month_end = 1 + p->tm_mon;
	int day_end = p->tm_mday;
	sprintf_s(tmp, "create temporary table Result(Date char(10))");
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt) {
		MessageBox(NULL, "�д���", NULL, NULL);
		return NULL;
	}
	sprintf_s(tmp, "select SDate from Person");
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt) {
		MessageBox(NULL, "�д���", NULL, NULL);
		return NULL;
	}
	res = mysql_store_result(con);
	while (row = mysql_fetch_row(res)) {
		char *date = row[0];
		days = 0;
		int year_start = int(date[0]) * 1000 + int(date[1]) * 100 + int(date[2]) * 10 + int(date[3]);
		int month_start = int(date[4]) * 10 + int(date[5]);
		int day_start = int(date[6]) * 10 + int(date[7]);

		days = day_diff(year_start, month_start, day_start, year_end, month_end, day_end);
		if (days > 60) {
			sprintf_s(tmp, "insert into Result values('')");
			x = strlen(tmp) - 2;
			sprintf_s(tmp1, row[0]);
			insert(tmp, tmp1,x);
			rt = mysql_real_query(con, tmp, strlen(tmp));
			if (rt) {
				MessageBox(NULL, "�д���", NULL, NULL);
				return NULL;
			}
		}
	}
	sprintf_s(tmp, "select Person.* from Person inner join Result on Person.SDate=Result.Date");
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt) {
		MessageBox(NULL, "�д���", NULL, NULL);
		return NULL;
	}
	res1 = mysql_store_result(con);
	sprintf_s(tmp, "drop table Result");
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt) {
		MessageBox(NULL, "�д���", NULL, NULL);
		return NULL;
	}
	return res1;
}

//��������ģ����ѯ
MYSQL_RES* findBook2(MYSQL * con, char* BNa)
{
	MYSQL_RES* res = NULL;
	char tmp[400];
	char tmp1[400];
	int rt;
	sprintf_s(tmp, "select * from Book where BNa like '%%'");
	sprintf_s(tmp1, BNa);
	insert(tmp, tmp1, strlen(tmp) - 2);
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		MessageBox(NULL, "�д���", NULL, NULL);
		return NULL;
	}
	res = mysql_store_result(con);
	return res;
}

//��������ֶ���������ֶν���ģ����ѯ
MYSQL_RES* findBook(MYSQL * con,char* tmp1,char* tmp2,char* tmp3,char* tmp4,char* tmp5)
{
	MYSQL_RES* res=NULL;
	char tmp[400];
	char tmp6[400] = "";
	int rt;
	sprintf_s(tmp, "select * from Book ");
	if (strcmp(tmp1, "") == 0 && strcmp(tmp2, "") == 0 && strcmp(tmp3, "") == 0 && strcmp(tmp4, "") == 0 && strcmp(tmp5, "") == 0)
	{
		rt = mysql_real_query(con, tmp, strlen(tmp));
		if (rt)
		{
			MessageBox(NULL, "�д���", NULL, NULL);
			return NULL;
		}
		res = mysql_store_result(con);
		return res;
	}
	else
	{
		sprintf_s(tmp6, "where ");
		insert(tmp, tmp6, strlen(tmp));
		if (strcmp(tmp1, "") != 0)
		{
			sprintf_s(tmp6, " BNo like '%%' or");
			insert(tmp6, tmp1, strlen(tmp6) - 5);
			insert(tmp, tmp6, strlen(tmp));
		}
		if (strcmp(tmp2, "") != 0)
		{
			sprintf_s(tmp6, " BNa like '%%' or");
			insert(tmp6, tmp2, strlen(tmp6) - 5);
			insert(tmp, tmp6, strlen(tmp));
		}
		if (strcmp(tmp3, "") != 0)
		{
			sprintf_s(tmp6, " BPu like '%%' or");
			insert(tmp6, tmp3, strlen(tmp6) - 5);
			insert(tmp, tmp6, strlen(tmp));
		}
		if (strcmp(tmp4, "") != 0)
		{
			sprintf_s(tmp6, " BWriter like '%%' or");
			insert(tmp6, tmp4, strlen(tmp6) - 5);
			insert(tmp, tmp6, strlen(tmp));
		}
		if (strcmp(tmp5, "") != 0)
		{
			sprintf_s(tmp6, " BType like '%%' or");
			insert(tmp6, tmp5, strlen(tmp6) - 5);
			insert(tmp, tmp6, strlen(tmp));
		}
		rt = mysql_real_query(con, tmp, strlen(tmp) - 3);
		if (rt)
		{
			MessageBox(NULL, "�д���", NULL, NULL);
			return NULL;
		}
		res = mysql_store_result(con);
		return res;
	}
	//output(con); //���������ʾ
}

//���߻��߹���Ա�Ķ�������
bool reInfor(MYSQL * con,char* password,char * account)//account�Ƕ����˺�
{
	char tmp[400];
	char tmp1[400];
	char tmp2[400];
	int rt;
	sprintf_s(tmp, "update Identity set Password=''");
	insert(tmp, password, strlen(tmp) - 1);
	sprintf_s(tmp1, " where Account=''");
	sprintf_s(tmp2, account);
	insert(tmp1, tmp2, strlen(tmp1) - 1);
	insert(tmp, tmp1, strlen(tmp));
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	else
	{
		MessageBox(NULL,"���³ɹ�!", NULL, NULL);
		return true;
	}
}

//����Ա�Ĺ���Ա����
bool reInfor2(MYSQL * con, char* password, char * account)//password��������
{
	char tmp[400];
	char tmp1[400];
	char tmp2[400];
	int rt;

	sprintf_s(tmp, "update Manager set MCode=''");
	insert(tmp, password, strlen(tmp) - 1);
	sprintf_s(tmp1, " where MNo=''");
	sprintf_s(tmp2, account);
	insert(tmp1, tmp2, strlen(tmp1) - 1);
	insert(tmp, tmp1, strlen(tmp));
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	else
	{
		MessageBox(NULL, "���³ɹ�!", NULL, NULL);
		return true;
	}
}

//����ע��
bool regR(MYSQL * con, char* account,char * password)//accountע���˺ţ�passwordע������
{
	MYSQL_RES* res = NULL;
	MYSQL_ROW row;
	char tmp[400];
	char tmp1[400];
	int rt;
	sprintf_s(tmp, "select * from Identity where Account='");
	sprintf_s(tmp1, account);
	insert(tmp, tmp1, strlen(tmp));
	sprintf_s(tmp1, "'");
	insert(tmp, tmp1, strlen(tmp));
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	res = mysql_store_result(con);
	if (row = mysql_fetch_row(res)) {
		MessageBox(NULL,"�˺��Ѿ����ڣ�", NULL, NULL);
		return false;
	}
	sprintf_s(tmp, "insert into Identity values('��Ա',60,1,')");
	sprintf_s(tmp1, account);
	insert(tmp, tmp1, strlen(tmp)-1);
	sprintf_s(tmp1, "','");
	insert(tmp, tmp1, strlen(tmp) - 1);
	sprintf_s(tmp1, password);
	insert(tmp, tmp1, strlen(tmp) - 1);
	sprintf_s(tmp1, "'");
	insert(tmp, tmp1, strlen(tmp) - 1);
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	return true;
}

//����Աע��
bool regM(MYSQL * con, char* account,char* name ,char * password)
{
	MYSQL_RES* res=NULL;
	MYSQL_ROW row;
	char tmp[400];
	char tmp1[400];
	int rt;
	sprintf_s(tmp, "select * from Manager where MNo='");
	sprintf_s(tmp1, account);
	insert(tmp, tmp1, strlen(tmp));
	sprintf_s(tmp1, "'");
	insert(tmp, tmp1, strlen(tmp));
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	res = mysql_store_result(con);
	if (row = mysql_fetch_row(res)) {
		MessageBox(NULL,"�˺��Ѿ����ڣ�",NULL,NULL);
		return false;
	}
	sprintf_s(tmp, "insert into Manager values(')");
	sprintf_s(tmp1, account);
	insert(tmp, tmp1, strlen(tmp) - 1);
	sprintf_s(tmp1, "','");
	insert(tmp, tmp1, strlen(tmp) - 1);
	sprintf_s(tmp1, name);
	insert(tmp, tmp1, strlen(tmp) - 1);
	sprintf_s(tmp1, "','");
	insert(tmp, tmp1, strlen(tmp) - 1);
	sprintf_s(tmp1, password);
	insert(tmp, tmp1, strlen(tmp) - 1);
	sprintf_s(tmp1, "'");
	insert(tmp, tmp1, strlen(tmp) - 1);
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		MessageBox(NULL, "�д���", NULL, NULL);
		return false;
	}
	return true;
}
//��ѯ���ж�����Ϣ
MYSQL_RES* findR(MYSQL * con)
{
	MYSQL_RES* res = NULL;
	char tmp[400];
	int rt;
	sprintf_s(tmp, "select * from Identity");
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		MessageBox(NULL, "�д���", NULL, NULL);
		return NULL;
	}
	res = mysql_store_result(con);
	return res;
}
