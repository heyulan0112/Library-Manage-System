
// 
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "LibraryManage.h"
#endif


#pragma comment(lib, "libmysql.lib")
#define NUM_THREADS 2


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "LibraryManageView.h"

// CstudentHealthView

IMPLEMENT_DYNCREATE(CLibraryManageView, CView)

BEGIN_MESSAGE_MAP(CLibraryManageView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLibraryManageView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_COMMAND(ID_32786, &CLibraryManageView::FindBook)
	ON_COMMAND(ID_32791, &CLibraryManageView::ChangePWD)
	ON_COMMAND(ID_32788, &CLibraryManageView::Borrow)
	ON_COMMAND(ID_32789, &CLibraryManageView::Return)
	ON_COMMAND(ID_32781, &CLibraryManageView::AddBook)
	ON_COMMAND(ID_32782, &CLibraryManageView::DelBook)
	ON_COMMAND(ID_32783, &CLibraryManageView::AddVIP)
	ON_COMMAND(ID_32784, &CLibraryManageView::DelVip)
	ON_COMMAND(ID_32785, &CLibraryManageView::EditVIP)
	ON_COMMAND(ID_32794, &CLibraryManageView::CreateRep)
	ON_UPDATE_COMMAND_UI(ID_32788, &CLibraryManageView::OnUpdateborrow)
	ON_UPDATE_COMMAND_UI(ID_32789, &CLibraryManageView::OnUpdateReturn)
	ON_UPDATE_COMMAND_UI(ID_32781, &CLibraryManageView::OnUpdateAdd1)
	ON_UPDATE_COMMAND_UI(ID_32782, &CLibraryManageView::OnUpdateDel1)
	ON_UPDATE_COMMAND_UI(ID_32783, &CLibraryManageView::OnUpdateAdd2)
	ON_UPDATE_COMMAND_UI(ID_32784, &CLibraryManageView::OnUpdateDel2)
	ON_UPDATE_COMMAND_UI(ID_32785, &CLibraryManageView::OnUpdateEdit)
	ON_UPDATE_COMMAND_UI(ID_32794, &CLibraryManageView::OnUpdateRep)
	ON_COMMAND(ID_32795, &CLibraryManageView::AddManager)
	ON_UPDATE_COMMAND_UI(ID_32795, &CLibraryManageView::OnUpdateManager)
	ON_COMMAND(ID_32796, &CLibraryManageView::ShowAllBook)
	ON_COMMAND(ID_32797, &CLibraryManageView::ShowAllReader)
	ON_UPDATE_COMMAND_UI(ID_32797, &CLibraryManageView::OnUpdateShowR)
	ON_COMMAND(ID_32798, &CLibraryManageView::InitPwd)
	ON_UPDATE_COMMAND_UI(ID_32798, &CLibraryManageView::OnUpdateInitPwd)
END_MESSAGE_MAP()

// CstudentHealthView 构造/析构

CLibraryManageView::CLibraryManageView() noexcept
{
	// TODO: 在此处添加构造代码
	init();
	LoginDlg l;
	l.setSql(con);
	l.DoModal();
	role = l.role;
	account = l.account;
	if (!l.res)
		PostQuitMessage(0);//最常用,退出程序
	
}

CLibraryManageView::~CLibraryManageView()
{
}

BOOL CLibraryManageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CstudentHealthView 绘图

void CLibraryManageView::OnDraw(CDC* /*pDC*/)
{
	CLibraryManageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
}



void CLibraryManageView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLibraryManageView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CstudentHealthView 诊断

#ifdef _DEBUG
void CLibraryManageView::AssertValid() const
{
	CView::AssertValid();
}

void CLibraryManageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLibraryManageDoc* CLibraryManageView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLibraryManageDoc)));
	return (CLibraryManageDoc*)m_pDocument;
}
#endif //_DEBUG





int CLibraryManageView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  在此添加您专用的创建代码
	m_cListCtrl.Create(LVS_REPORT, CRect(0, 0, 1450, 600), this, IDC_LIST);//按钮标题 按钮风格 按钮大小 按钮父指针 该按钮对应的ID号
	DWORD dwStyle = m_cListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//鼠标选中某行使整行高亮（只适用与属性为report 风格的listctrl ）
	dwStyle |= LVS_EX_GRIDLINES;// 列表有网格线（只适用与report 风格的listctrl ）
	m_cListCtrl.SetExtendedStyle(dwStyle); // 设置扩展风格
	m_cListCtrl.InsertColumn(0, _T("图书编号"), LVCFMT_CENTER, 160);
	m_cListCtrl.InsertColumn(1, _T("图名名称"), LVCFMT_CENTER, 160);
	m_cListCtrl.InsertColumn(2, _T("出版日期"), LVCFMT_CENTER, 160);
	m_cListCtrl.InsertColumn(3, _T("出版社"), LVCFMT_CENTER, 170);
	m_cListCtrl.InsertColumn(4, _T("存放位置"), LVCFMT_CENTER, 160);
	m_cListCtrl.InsertColumn(5, _T("总量"), LVCFMT_CENTER, 160);
	m_cListCtrl.InsertColumn(6, _T("作者"), LVCFMT_CENTER, 160);
	m_cListCtrl.InsertColumn(7, _T("图书类型"), LVCFMT_CENTER, 160);
	m_cListCtrl.InsertColumn(8, _T("备注"), LVCFMT_CENTER, 160);
	m_cListCtrl.ShowWindow(SW_SHOWNORMAL);
	return 0;
}



void CLibraryManageView::FindBook()
{
	// TODO: 在此添加命令处理程序代码
	InfoDlg In;//单个信息查询或者修改的对话框,都是按了取消键就不添加
	In.tip = _T("输入相关信息");
	In.DoModal();
	if (!In.check)
		return;

	int nColumnCount = m_cListCtrl.GetHeaderCtrl()->GetItemCount();
	// Delete all of the columns.
	if (nColumnCount != 9) {
		for (int i = 0; i < nColumnCount; i++)
		{
			m_cListCtrl.DeleteColumn(0);
		}

		m_cListCtrl.InsertColumn(0, _T("图书编号"), LVCFMT_CENTER, 160);
		m_cListCtrl.InsertColumn(1, _T("图名名称"), LVCFMT_CENTER, 160);
		m_cListCtrl.InsertColumn(2, _T("出版日期"), LVCFMT_CENTER, 160);
		m_cListCtrl.InsertColumn(3, _T("出版社"), LVCFMT_CENTER, 170);
		m_cListCtrl.InsertColumn(4, _T("存放位置"), LVCFMT_CENTER, 160);
		m_cListCtrl.InsertColumn(5, _T("总量"), LVCFMT_CENTER, 160);
		m_cListCtrl.InsertColumn(6, _T("作者"), LVCFMT_CENTER, 160);
		m_cListCtrl.InsertColumn(7, _T("图书类型"), LVCFMT_CENTER, 160);
		m_cListCtrl.InsertColumn(8, _T("备注"), LVCFMT_CENTER, 160);
		m_cListCtrl.ShowWindow(SW_SHOWNORMAL);
	}

	m_cListCtrl.DeleteAllItems();
	

	MYSQL_ROW row;
	MYSQL_RES * res = findBook(con, T2A((LPTSTR)(LPCTSTR)In.input), T2A((LPTSTR)(LPCTSTR)In.input), T2A((LPTSTR)(LPCTSTR)In.input), T2A((LPTSTR)(LPCTSTR)In.input), T2A((LPTSTR)(LPCTSTR)In.input));
	int m = 0;
	while (row = mysql_fetch_row(res))
	{
		m_cListCtrl.InsertItem(m, row[0]);//添加行及首数据
		m_cListCtrl.SetItemText(m, 1, row[1]);
		m_cListCtrl.SetItemText(m, 2, row[2]);
		m_cListCtrl.SetItemText(m, 3, row[3]);
		m_cListCtrl.SetItemText(m, 4, row[4]);
		m_cListCtrl.SetItemText(m, 5, row[5]);
		m_cListCtrl.SetItemText(m, 6, row[6]);
		m_cListCtrl.SetItemText(m, 7, row[7]);
		m_cListCtrl.SetItemText(m, 8, row[8]);
		m++;
	}


	
}



void CLibraryManageView::ChangePWD()
{
	// TODO: 在此添加命令处理程序代码
	InfoDlg In;//单个信息查询或者修改的对话框,都是按了取消键就不添加
	In.tip = _T("输入新密码");
	In.DoModal();
	if (!In.check)
		return;
	if (role == 1)
		reInfor(con, T2A((LPTSTR)(LPCTSTR)In.input), T2A((LPTSTR)(LPCTSTR)account));
	else
		reInfor2(con, T2A((LPTSTR)(LPCTSTR)In.input), T2A((LPTSTR)(LPCTSTR)account));
}

void CLibraryManageView::Borrow()
{
	// TODO: 在此添加命令处理程序代码
	InfoDlg In;//单个信息查询或者修改的对话框,都是按了取消键就不添加
	In.tip = _T("输入借的图书编号");
	In.DoModal();
	if (!In.check)
		return;
	borrowBook(con, T2A((LPTSTR)(LPCTSTR)account), T2A((LPTSTR)(LPCTSTR)In.input));
}


void CLibraryManageView::Return()
{
	// TODO: 在此添加命令处理程序代码
	InfoDlg In;//单个信息查询或者修改的对话框,都是按了取消键就不添加
	In.tip = _T("输入还的图书编号");
	In.DoModal();
	if (!In.check)
		return;
	returnBook(con, T2A((LPTSTR)(LPCTSTR)account), T2A((LPTSTR)(LPCTSTR)In.input));
}


void CLibraryManageView::AddBook()
{
	// TODO: 在此添加命令处理程序代码
	BookDlg b;
	b.setSql(con);
	b.DoModal();
}


void CLibraryManageView::DelBook()
{
	// TODO: 在此添加命令处理程序代码
	InfoDlg In;//单个信息查询或者修改的对话框,都是按了取消键就不添加
	In.tip = _T("输入删除的图书编号");
	In.DoModal();
	if (!In.check)
		return;
	delBook(con, T2A((LPTSTR)(LPCTSTR)In.input));
}


void CLibraryManageView::AddVIP()
{
	// TODO: 在此添加命令处理程序代码
	VIPDlg v;
	v.setSql(con);
	v.DoModal();
}


void CLibraryManageView::DelVip()
{
	// TODO: 在此添加命令处理程序代码
	InfoDlg In;//单个信息查询或者修改的对话框,都是按了取消键就不添加
	In.tip = _T("输入删除的会员编号");
	In.DoModal();
	if (!In.check)
		return;
	delVip(con, T2A((LPTSTR)(LPCTSTR)In.input));
}


void CLibraryManageView::CreateRep()
{
	// TODO: 在此添加命令处理程序代码
	int nColumnCount = m_cListCtrl.GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i = 0; i < nColumnCount; i++)
	{
		m_cListCtrl.DeleteColumn(0);
	}

	m_cListCtrl.InsertColumn(0, _T("借书证号"), LVCFMT_CENTER, 290);
	m_cListCtrl.InsertColumn(1, _T("身份"), LVCFMT_CENTER, 290);
	m_cListCtrl.InsertColumn(2, _T("备注"), LVCFMT_CENTER, 290);
	m_cListCtrl.InsertColumn(3, _T("书号"), LVCFMT_CENTER, 290);
	m_cListCtrl.InsertColumn(4, _T("借书日期"), LVCFMT_CENTER, 290);
	m_cListCtrl.ShowWindow(SW_SHOWNORMAL);
	m_cListCtrl.DeleteAllItems();
	
	MYSQL_ROW row;
	MYSQL_RES * res = creRep(con);
	int m = 0;
	while (row = mysql_fetch_row(res))
	{
		m_cListCtrl.InsertItem(m, row[0]);//添加行及首数据
		m_cListCtrl.SetItemText(m, 1, row[1]);
		m_cListCtrl.SetItemText(m, 2, row[2]);
		m_cListCtrl.SetItemText(m, 3, row[3]);
		m_cListCtrl.SetItemText(m, 4, row[4]);
		m++;
	}
}





void CLibraryManageView::EditVIP()
{
	// TODO: 在此添加命令处理程序代码
	InfoDlg In;//单个信息查询或者修改的对话框,都是按了取消键就不添加
	In.tip = _T("输入编辑的会员编号");
	In.DoModal();
	if (!In.check)
		return;
	MYSQL_ROW row;
	MYSQL_RES * res= reVcard1(con, T2A((LPTSTR)(LPCTSTR)In.input));
	row = mysql_fetch_row(res);

	RegisterDlg r;
	r.tip1 = "姓名";
	r.tip2 = "截止日期";
	r.account = row[0];
	r.Password = row[1];
	r.DoModal();
	UpdateData();
	reVcard2(con, T2A((LPTSTR)(LPCTSTR)In.input),T2A((LPTSTR)(LPCTSTR)r.account), T2A((LPTSTR)(LPCTSTR)r.Password));
}



void CLibraryManageView::AddManager()
{
	// TODO: 在此添加命令处理程序代码
	RegisterDlg r;
	r.tip1 = "请输入账号";
	r.tip2 = "请输入密码";
	r.DoModal();
	if (r.check)
		regM(con, T2A((LPTSTR)(LPCTSTR)r.account),T2A((LPTSTR)(LPCTSTR)r.account), T2A((LPTSTR)(LPCTSTR)r.Password));
}


void CLibraryManageView::OnUpdateborrow(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(role==2)
		pCmdUI->Enable(FALSE);
}


void CLibraryManageView::OnUpdateReturn(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (role == 2)
		pCmdUI->Enable(FALSE);
}


void CLibraryManageView::OnUpdateAdd1(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (role == 1)
		pCmdUI->Enable(FALSE);
}


void CLibraryManageView::OnUpdateDel1(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (role == 1)
		pCmdUI->Enable(FALSE);
}


void CLibraryManageView::OnUpdateAdd2(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (role == 1)
		pCmdUI->Enable(FALSE);
}


void CLibraryManageView::OnUpdateManager(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (role == 1)
		pCmdUI->Enable(FALSE);
}


void CLibraryManageView::OnUpdateDel2(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (role == 1)
		pCmdUI->Enable(FALSE);
}


void CLibraryManageView::OnUpdateEdit(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (role == 1)
		pCmdUI->Enable(FALSE);
}


void CLibraryManageView::OnUpdateRep(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (role == 1)
		pCmdUI->Enable(FALSE);
}


bool CLibraryManageView::init()
{
	char dbuser[30] = "root";
	char dbpasswd[30] = "system";
	char dbip[30] = "localhost";
	char dbname[50] = "mysql";

	char tablename[50] = "book";
	const char *query = NULL;

	int x;
	int y;
	int rt;//return value  

	int count = 0;

	con = mysql_init((MYSQL*)0);

	if (con != NULL && mysql_real_connect(con, dbip, dbuser, dbpasswd, dbname, 3306, NULL, 0)) {
		if (!mysql_select_db(con, dbname)) {
			MessageBox("连接数据库成功!");
			con->reconnect = 1;
			query = "set names \'GBK\'";
			rt = mysql_real_query(con, query, strlen(query));
			if (rt) {
				MessageBox("Error making query ");
			}
			else {
				MessageBox(" 成功!");
			}
		}
	}
	else {
		MessageBoxA("连接数据库失败，请检查配置!");
	}
	mysql_autocommit(con, 1);


	int finish = 0;
	int choice;
	char tmp[400];
	bool passFlag = false;
	char account[50] = "13922387344";////前端输入
	char account2[50] = "20172137899";
	char password[50] = "tiger";////前端输入
	char bookNo[50] = "01";////前端输入
	char account3[50] = "20172137365";
	char BNa[10] = "软工";
	char vname[50] = "Tommy";
	char vbdate[50] = "19980326";
	char bda[10] = "19990204";
	char bpu[50] = "华师出版社";
	char bpi[50] = "一楼B区15架2层";
	char bnu[2] = "3";
	char bwriter[50] = "denniel lee";
	char btype[50] = "工具书";
	char bremark[50] = "无";
	MYSQL_RES * res;
	bool flag = 0;
	rt = mysql_real_query(con, "use mysql", strlen("use mysql"));
	if (rt) {
		MessageBox("有错误 ");
		system("pause");
		system("cls");
		return false;
	}
	return true;
}





void CLibraryManageView::ShowAllBook()
{
	// TODO: 在此添加命令处理程序代码
	int nColumnCount = m_cListCtrl.GetHeaderCtrl()->GetItemCount();
	// Delete all of the columns.
	if (nColumnCount != 9) {
		for (int i = 0; i < nColumnCount; i++)
		{
			m_cListCtrl.DeleteColumn(0);
		}

		m_cListCtrl.InsertColumn(0, _T("图书编号"), LVCFMT_CENTER, 160);
		m_cListCtrl.InsertColumn(1, _T("图名名称"), LVCFMT_CENTER, 160);
		m_cListCtrl.InsertColumn(2, _T("出版日期"), LVCFMT_CENTER, 160);
		m_cListCtrl.InsertColumn(3, _T("出版社"), LVCFMT_CENTER, 170);
		m_cListCtrl.InsertColumn(4, _T("存放位置"), LVCFMT_CENTER, 160);
		m_cListCtrl.InsertColumn(5, _T("总量"), LVCFMT_CENTER, 160);
		m_cListCtrl.InsertColumn(6, _T("作者"), LVCFMT_CENTER, 160);
		m_cListCtrl.InsertColumn(7, _T("图书类型"), LVCFMT_CENTER, 160);
		m_cListCtrl.InsertColumn(8, _T("备注"), LVCFMT_CENTER, 160);
		m_cListCtrl.ShowWindow(SW_SHOWNORMAL);
	}

	m_cListCtrl.DeleteAllItems();


	MYSQL_ROW row;
	MYSQL_RES * res = findBook(con, "", "", "", "", "");
	int m = 0;
	while (row = mysql_fetch_row(res))
	{
		m_cListCtrl.InsertItem(m, row[0]);//添加行及首数据
		m_cListCtrl.SetItemText(m, 1, row[1]);
		m_cListCtrl.SetItemText(m, 2, row[2]);
		m_cListCtrl.SetItemText(m, 3, row[3]);
		m_cListCtrl.SetItemText(m, 4, row[4]);
		m_cListCtrl.SetItemText(m, 5, row[5]);
		m_cListCtrl.SetItemText(m, 6, row[6]);
		m_cListCtrl.SetItemText(m, 7, row[7]);
		m_cListCtrl.SetItemText(m, 8, row[8]);
		m++;
	}
}


void CLibraryManageView::ShowAllReader()
{
	// TODO: 在此添加命令处理程序代码
	int nColumnCount = m_cListCtrl.GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i = 0; i < nColumnCount; i++)
	{
		m_cListCtrl.DeleteColumn(0);
	}

	m_cListCtrl.InsertColumn(0, _T("身份"), LVCFMT_CENTER, 290);
	m_cListCtrl.InsertColumn(1, _T("最大借阅时间"), LVCFMT_CENTER, 290);
	m_cListCtrl.InsertColumn(2, _T("最大借阅数量"), LVCFMT_CENTER, 290);
	m_cListCtrl.InsertColumn(3, _T("登陆账号"), LVCFMT_CENTER, 290);
	m_cListCtrl.InsertColumn(4, _T("登陆密码"), LVCFMT_CENTER, 290);
	m_cListCtrl.ShowWindow(SW_SHOWNORMAL);
	m_cListCtrl.DeleteAllItems();

	MYSQL_ROW row;
	MYSQL_RES * res = findR(con);
	int m = 0;
	while (row = mysql_fetch_row(res))
	{
		m_cListCtrl.InsertItem(m, row[0]);//添加行及首数据
		m_cListCtrl.SetItemText(m, 1, row[1]);
		m_cListCtrl.SetItemText(m, 2, row[2]);
		m_cListCtrl.SetItemText(m, 3, row[3]);
		m_cListCtrl.SetItemText(m, 4, row[4]);
		m++;
	}
}


void CLibraryManageView::OnUpdateShowR(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (role == 1)
		pCmdUI->Enable(FALSE);
}


void CLibraryManageView::InitPwd()
{
	// TODO: 在此添加命令处理程序代码
	RegisterDlg r;
	r.tip1 = "请输入账号";
	r.tip2 = "请输入密码";
	r.DoModal();
	if (r.check)
		reInfor(con, T2A((LPTSTR)(LPCTSTR)r.Password), T2A((LPTSTR)(LPCTSTR)r.account));
}


void CLibraryManageView::OnUpdateInitPwd(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (role == 1)
		pCmdUI->Enable(FALSE);
}
