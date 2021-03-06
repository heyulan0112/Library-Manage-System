// BookDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "BookDlg.h"



// BookDlg 对话框

IMPLEMENT_DYNAMIC(BookDlg, CDialogEx)

BookDlg::BookDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BOOK, pParent)
	, num(_T(""))
	, name(_T(""))
	, date(_T(""))
	, place(_T(""))
	, store(_T(""))
	, sum(_T(""))
	, author(_T(""))
	, type(_T(""))
	, othertip(_T(""))
{

}

BookDlg::~BookDlg()
{
}

void BookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, num);
	DDX_Text(pDX, IDC_EDIT2, name);
	DDX_Text(pDX, IDC_EDIT3, date);
	DDX_Text(pDX, IDC_EDIT4, place);
	DDX_Text(pDX, IDC_EDIT5, store);
	DDX_Text(pDX, IDC_EDIT6, sum);
	DDX_Text(pDX, IDC_EDIT7, author);
	DDX_Text(pDX, IDC_EDIT8, type);
	DDX_Text(pDX, IDC_EDIT9, othertip);
}


BEGIN_MESSAGE_MAP(BookDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &BookDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// BookDlg 消息处理程序


void BookDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	enterBook(con, T2A((LPTSTR)(LPCTSTR)num), T2A((LPTSTR)(LPCTSTR)name), T2A((LPTSTR)(LPCTSTR)date), 
		T2A((LPTSTR)(LPCTSTR)place), T2A((LPTSTR)(LPCTSTR)store), T2A((LPTSTR)(LPCTSTR)sum),
		T2A((LPTSTR)(LPCTSTR)author), T2A((LPTSTR)(LPCTSTR)type), T2A((LPTSTR)(LPCTSTR)othertip));
	CDialogEx::OnOK();
}

void BookDlg::setSql(MYSQL *con2) {
	con = con2;
}

