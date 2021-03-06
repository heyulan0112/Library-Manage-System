#pragma once

#include "LibraryManage.h"

// InfoDlg 对话框

class InfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InfoDlg)

public:
	InfoDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~InfoDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INFORMATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString input;
	CString tip;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	bool check;
	afx_msg void OnEnChangeEdit12();
};
