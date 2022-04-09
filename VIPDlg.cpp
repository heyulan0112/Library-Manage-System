// VIPDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VIPDlg.h"



// VIPDlg 对话框

IMPLEMENT_DYNAMIC(VIPDlg, CDialogEx)

VIPDlg::VIPDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIP, pParent)
	, name(_T(""))
	, vipnum(_T(""))
	, date(_T(""))
	, maxbook(_T(""))
{

}

VIPDlg::~VIPDlg()
{
}

void VIPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME1, name);
	DDX_Text(pDX, IDC_NUM1, vipnum);
	DDX_Text(pDX, IDC_DATE1, date);
	DDX_Text(pDX, IDC_MAX1, maxbook);
}


BEGIN_MESSAGE_MAP(VIPDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &VIPDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// VIPDlg 消息处理程序




void VIPDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	enterVip(con, T2A((LPTSTR)(LPCTSTR)vipnum), T2A((LPTSTR)(LPCTSTR)name), T2A((LPTSTR)(LPCTSTR)date), T2A((LPTSTR)(LPCTSTR)maxbook));
	CDialogEx::OnOK();
}

void VIPDlg::setSql(MYSQL * con2) {
	con = con2;
}
