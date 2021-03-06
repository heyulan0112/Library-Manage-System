#pragma once
#include "mysql.h"
#include "LibraryManage.h"
#include "system.h"
#include "afxdialogex.h"

// VIPDlg 对话框

class VIPDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VIPDlg)

public:
	VIPDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VIPDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString name;
	CString vipnum;
	CString date;
	CString maxbook;
	afx_msg void OnBnClickedOk();
	void setSql(MYSQL * con2);
	MYSQL * con;
};
