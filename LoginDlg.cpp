// LoginDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LoginDlg.h"



// LoginDlg 对话框

IMPLEMENT_DYNAMIC(LoginDlg, CDialogEx)

LoginDlg::LoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
	, account(_T(""))
	, password(_T(""))
	,role(0)
{

}

LoginDlg::~LoginDlg()
{
}

void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, account);
	DDX_Text(pDX, IDC_PASSWORD, password);
}


BEGIN_MESSAGE_MAP(LoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &LoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_Reg, &LoginDlg::OnBnClickedReg)
END_MESSAGE_MAP()


// LoginDlg 消息处理程序


void LoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (GetCheckedRadioButton(IDC_READRADIO, IDC_MANRADIO) == IDC_READRADIO)
	{
		role = 1;
	}
	else if (GetCheckedRadioButton(IDC_READRADIO, IDC_MANRADIO) == IDC_MANRADIO)
	{
		role = 2;
	}
	if (role == 0)
		MessageBox("请选择身份");
	else
	{
		
		UpdateData();
		if (role == 1)
			res = Rlogin(con, T2A((LPTSTR)(LPCTSTR)account), T2A((LPTSTR)(LPCTSTR)password));
		else
			res = Mlogin(con, T2A((LPTSTR)(LPCTSTR)account), T2A((LPTSTR)(LPCTSTR)password));
		if (!res)
		{
			MessageBox("账号密码有误，请重新输入！");
			UpdateData(FALSE);
			account = "";
			password = "";
		}
		else
			EndDialog(0);
	}
		
}

void LoginDlg::setSql(MYSQL * con2) {
	con = con2;
}


void LoginDlg::OnBnClickedReg()
{
	// TODO: 在此添加控件通知处理程序代码
	RegisterDlg r;
	r.tip1 = "请输入账号";
	r.tip2 = "请输入密码";
	r.DoModal();
	UpdateData();
	if(r.check)
		regR(con, T2A((LPTSTR)(LPCTSTR)r.account), T2A((LPTSTR)(LPCTSTR)r.Password));
}
