#pragma once
#ifndef _system_h
#define _system_h
#include "stdio.h"
#include "mysql.h"
#include <windows.h>
#include <winsock.h>
#include <WinUser.h>
#include <iostream>
#include<cstring>
#pragma comment(lib, "libmysql.lib")

bool Rlogin(MYSQL * con,char *account,char* password);
bool Mlogin(MYSQL * con, char *account, char* password);
bool borrowBook(MYSQL * con,char * account,char* bookNo);
bool returnBook(MYSQL * con, char * account, char* bookNo);
bool enterBook(MYSQL * con, char *tmp1, char* tmp2, char* tmp3, char* tmp4, char* tmp5, char* tmp6, char* tmp7, char* tmp8, char* tmp9);
bool enterVip(MYSQL * con, char* tmp1, char* tmp2, char* tmp3, char* tmp4);
bool delBook(MYSQL * con, char * BNo);
bool delVip(MYSQL * con, char * VNo);
MYSQL *getConnect();
MYSQL_RES* reVcard1(MYSQL * con, char *account);
bool reVcard2(MYSQL * con, char*vno,char* vname, char* vbdate);
MYSQL_RES* printV(MYSQL * con, char *vno);
MYSQL_RES* creRep(MYSQL * con);
MYSQL_RES* findBook(MYSQL * con, char* tmp1, char* tmp2, char* tmp3, char* tmp4, char* tmp5);
MYSQL_RES* findBook2(MYSQL * con, char* BNa);
bool reInfor(MYSQL * con, char* password,char *account);
bool reInfor2(MYSQL * con, char* password, char * account);
bool regR(MYSQL * con, char* account, char * password);
bool regM(MYSQL * con, char* account, char* name, char * password);
MYSQL_RES* findR(MYSQL * con);
#endif 

