// RegisterDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LibraryManage.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"


// RegisterDlg 对话框

IMPLEMENT_DYNAMIC(RegisterDlg, CDialogEx)

RegisterDlg::RegisterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Register, pParent)
	,check(0)
	, account(_T(""))
	, Password(_T(""))
	, tip1(_T(""))
	, tip2(_T(""))
{

}

RegisterDlg::~RegisterDlg()
{
}

void RegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITACC, account);
	DDX_Text(pDX, IDC_EDITPwd, Password);
	DDX_Text(pDX, IDC_ED1, tip1);
	DDX_Text(pDX, IDC_ED2, tip2);
}


BEGIN_MESSAGE_MAP(RegisterDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &RegisterDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// RegisterDlg 消息处理程序


void RegisterDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	check = TRUE;
	CDialogEx::OnOK();
}
