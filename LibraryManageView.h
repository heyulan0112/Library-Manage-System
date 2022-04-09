
//
//

#pragma once
#include "mysql.h"
#include "LibraryManageDoc.h"
#include "LoginDlg.h"
#include "BookDlg.h"
#include "VIPDlg.h"
#include "InfoDlg.h"
#include "afxdialogex.h"
#include "RegisterDlg.h"


#include "stdio.h"
#include <windows.h>
#include <winsock.h>
#include <WinUser.h>
#include <iostream>
#include<cstring>

class CLibraryManageView : public CView
{
protected: // 仅从序列化创建
	CLibraryManageView() noexcept;
	DECLARE_DYNCREATE(CLibraryManageView)

// 特性
public:
	CLibraryManageDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CLibraryManageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	CString account;  //账号
	int role;  //角色
	MYSQL * con; //= mysql_init((MYSQL*) 0); 
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CListCtrl m_cListCtrl;
	afx_msg void FindBook();
	afx_msg void ChangePWD();
	afx_msg void Borrow();
	afx_msg void Return();
	afx_msg void AddBook();
	afx_msg void DelBook();
	afx_msg void AddVIP();
	afx_msg void DelVip();
	afx_msg void EditVIP();
	afx_msg void CreateRep();
	afx_msg void AddManager();
	afx_msg void OnUpdateborrow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReturn(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAdd1(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDel1(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAdd2(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDel2(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEdit(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRep(CCmdUI *pCmdUI);
	afx_msg void OnUpdateManager(CCmdUI *pCmdUI);
	bool init();

	afx_msg void ShowAllBook();
	afx_msg void ShowAllReader();
	afx_msg void OnUpdateShowR(CCmdUI *pCmdUI);
	afx_msg void InitPwd();
	afx_msg void OnUpdateInitPwd(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // 
inline CstudentHealthDoc* CstudentHealthView::GetDocument() const
   { return reinterpret_cast<CstudentHealthDoc*>(m_pDocument); }
#endif

