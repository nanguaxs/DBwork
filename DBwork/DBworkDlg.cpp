
// DBworkDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DBwork.h"
#include "DBworkDlg.h"
#include "afxdialogex.h"
#include"sql.h"
#include "user.h"

#include"CDBwork_adminDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
int connected=0;
MYSQL m_sqlCon;
char query[1024];




//CString query;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
//CDBworkDlg* CDBworkDlg::pCDBworkDlg = NULL;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDBworkDlg 对话框



CDBworkDlg::CDBworkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DBWORK_DIALOG, pParent)
	, m_num(_T(""))
	, m_pass(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDBworkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_num);
	DDX_Text(pDX, IDC_EDIT_PASS, m_pass);
}

BEGIN_MESSAGE_MAP(CDBworkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_connect, &CDBworkDlg::OnBnClickedButtonconnect)
	ON_BN_CLICKED(IDC_BUTTON_enter, &CDBworkDlg::OnBnClickedButtonenter)
END_MESSAGE_MAP()


// CDBworkDlg 消息处理程序

BOOL CDBworkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	((CButton*)GetDlgItem(IDC_admin))->SetCheck(FALSE);//选上
	((CButton*)GetDlgItem(IDC_user))->SetCheck(TRUE);//不选上
	//if (connectsql(&m_sqlCon) == 0)
	//{
	//	AfxMessageBox(_T("数据库连接失败!"));
	//	
	//}
	//else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	//{
	//	AfxMessageBox(_T("数据库连接成功!"));
	//	connected = 1;
	//	
	//}
	//pCDBworkDlg = this;

	//localhost:服务器地址，可以直接填入IP;root:账号;
	//123:密码;test:数据库名;3306:网络端口  
	
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDBworkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDBworkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDBworkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDBworkDlg::OnBnClickedButtonconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	connectsql(&m_sqlCon);
	//初始化数据库对象
	//mysql_init(&m_sqlCon);

	////localhost:服务器地址，可以直接填入IP;root:账号;
	////123:密码;test:数据库名;3306:网络端口  
	if (connectsql(&m_sqlCon)==0)
	{
		AfxMessageBox(_T("数据库连接失败!"));
		return;
	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		AfxMessageBox(_T("数据库连接成功!"));
		connected = 1;
		return;
	}
}


void CDBworkDlg::OnBnClickedButtonenter()//登录界面
{
	// TODO: 在此添加控件通知处理程序代码
	
	MYSQL_RES* m_res;
	//m_res = NULL;
	MYSQL_ROW row;/* return data as array of strings */
	CString temp_id,temp_pass;
	if (connected == 0) {
		AfxMessageBox(_T("请先连接数据库!"));
		return;
	}
	if (((CButton*)GetDlgItem(IDC_user))->GetCheck()) {//用户登录
		GetDlgItem(IDC_EDIT_ID)->GetWindowText(temp_id);
		GetDlgItem(IDC_EDIT_PASS)->GetWindowText(temp_pass);
		USES_CONVERSION;
		char *num = T2A(temp_id);
		
		char* pass = T2A(temp_pass);
		sprintf_s(query, "select user_key from user_account where user_id='%s';",
			num);
		/*query.Format(TEXT("select * from book"));*/
		
		//i=mysql_real_query(&m_sqlCon, query, (unsigned long)strlen(query));
		mysql_query(&m_sqlCon, query);
		if ((m_res = mysql_store_result(&m_sqlCon))==NULL) {
			AfxMessageBox(_T("查询账号失败!"));
			return;
		}
		
		if ((row = mysql_fetch_row(m_res)) != NULL) {
			if (!strcmp(row[0],pass)) {
				user dlg;
				dlg.user_id = num;//能这么做是因为user_id没初始化
				dlg.DoModal();
			}
			else {
				AfxMessageBox(_T("密码错误!"));
				return;
			}
		}
		else {
			AfxMessageBox(_T("用户不存在!"));
			return;
		}
	}
	else {//管理员登录
		MYSQL_RES* m_res;
		//m_res = NULL;
		MYSQL_ROW row;
		CString temp_id, temp_pass;
		if (connected == 0) {
			AfxMessageBox(_T("请先连接数据库!"));
			return;
		}
		
		GetDlgItem(IDC_EDIT_ID)->GetWindowText(temp_id);
		GetDlgItem(IDC_EDIT_PASS)->GetWindowText(temp_pass);
		USES_CONVERSION;
		char* num = T2A(temp_id);//CString ==> char*

		char* pass = T2A(temp_pass);
		sprintf_s(query, "select admin_key from admin_account where admin_id='%s';",
				num);
			
		mysql_query(&m_sqlCon, query);
		if ((m_res = mysql_store_result(&m_sqlCon)) == NULL) {
			AfxMessageBox(_T("查询账号失败!"));
			return;
		}

		if ((row = mysql_fetch_row(m_res)) != NULL) {
			if (strcmp(row[1], pass)) {
				CDBwork_adminDlg dlg;
				dlg.DoModal();
				
			}
			else {
				AfxMessageBox(_T("密码错误!"));
				return;
			}
		}
		else {
			AfxMessageBox(_T("用户不存在!"));
			return;
		}
		
	}
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
