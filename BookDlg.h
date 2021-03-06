#pragma once
#include "mysql.h"
#include "LibraryManage.h"
#include "afxdialogex.h"
#include "system.h"

// BookDlg 对话框

class BookDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BookDlg)

public:
	BookDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~BookDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOOK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString num;
	CString name;
	CString date;
	CString place;
	CString store;
	CString sum;
	CString author;
	CString type;
	CString othertip;
public:
	afx_msg void OnBnClickedOk();
	void setSql(MYSQL * con2);
	MYSQL *con;
};
