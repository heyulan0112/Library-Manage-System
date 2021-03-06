#pragma once
#include "mysql.h"
#include "LibraryManage.h"
#include "afxdialogex.h"
#include "RegisterDlg.h"
#include "system.h"
#include "stdio.h"

// LoginDlg 对话框

class LoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LoginDlg)

public:
	LoginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~LoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString account;
	CString password;
	bool res;  //false是登陆失败
	int role;  //role=1是读者，2是管理员
	afx_msg void OnBnClickedButton1();
	void setSql(MYSQL * con2);
	afx_msg void OnBnClickedReg();
	MYSQL *con;
};
