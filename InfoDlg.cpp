// InfoDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "InfoDlg.h"
#include "afxdialogex.h"


// InfoDlg 对话框

IMPLEMENT_DYNAMIC(InfoDlg, CDialogEx)

InfoDlg::InfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INFORMATION, pParent)
	, input(_T(""))
	, tip(_T(""))
{

}

InfoDlg::~InfoDlg()
{
}

void InfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ED, input);
	DDX_Text(pDX, IDC_EDIT12, tip);
}


BEGIN_MESSAGE_MAP(InfoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &InfoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CANCEL, &InfoDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT12, &InfoDlg::OnEnChangeEdit12)
END_MESSAGE_MAP()


// InfoDlg 消息处理程序


void InfoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	check = true;
}


void InfoDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	check = false;
}


void InfoDlg::OnEnChangeEdit12()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
