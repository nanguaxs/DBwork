// CDBwork_adminDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DBwork.h"
#include "afxdialogex.h"
#include "CDBwork_adminDlg.h"
#include "sql.h"
#include< windows.h >


MYSQL m_sqlCon_admin;

//#include "pch.h"
//#include "framework.h"
//#include "DBwork.h"
//#include "DBworkDlg.h"
//#include "afxdialogex.h"
//#include"sql.h"
// CDBwork_adminDlg 对话框

IMPLEMENT_DYNAMIC(CDBwork_adminDlg, CDialogEx)

char query_admin[1024]="";
CDBwork_adminDlg::CDBwork_adminDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_admin, pParent)
	, m_id(_T(""))
	, m_name(_T(""))
{

}

CDBwork_adminDlg::~CDBwork_adminDlg()
{
}

void CDBwork_adminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
	DDX_Text(pDX, IDC_EDIT2, m_name);

	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CDBwork_adminDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDBwork_adminDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDBwork_adminDlg::OnBnClickedButton2)
	//ON_EN_CHANGE(IDC_EDIT1, &CDBwork_adminDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &CDBwork_adminDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDBwork_adminDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CDBwork_adminDlg 消息处理程序


BOOL CDBwork_adminDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_list.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加列   
	m_list.InsertColumn(0, _T("学号"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_list.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, rect.Width() / 5, 1);
	m_list.InsertColumn(2, _T("密码"), LVCFMT_CENTER, rect.Width() / 5, 2);
	m_list.InsertColumn(3, _T("性别"), LVCFMT_CENTER, rect.Width() / 5, 3);
	m_list.InsertColumn(4, _T("年龄"), LVCFMT_CENTER, rect.Width() / 5, 4);
	//CDBworkDlg* p=CDBworkDlg::pCDBworkDlg;
	SetConsoleOutputCP(65001);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDBwork_adminDlg::OnBnClickedButton1()//查询
{
	// TODO: 在此添加控件通知处理程序代码
	CString name,id;
	m_list.DeleteAllItems();
	MYSQL_RES* m_res;
	//m_res = NULL;
	//MYSQL_ROW row;
	GetDlgItem(IDC_EDIT_ID)->GetWindowText(id);
	GetDlgItem(IDC_EDIT2)->GetWindowText(name);
	USES_CONVERSION;
	char *m_name=T2A(name);
	char *m_id = T2A(id);
	if (id.IsEmpty()&&name.IsEmpty()) {
		sprintf_s(query_admin, "select S_id,S_name,user_key,S_sex,S_age"
			" from user_account,students "
			"where S_id = user_id;"
		);
	}
	else if (id.IsEmpty()) {
		sprintf_s(query_admin, "select S_id,S_name,user_key,S_sex,S_age"
			" from user_account,students "
			"where S_id = user_id AND S_name='%s';",m_name);
	}
	else if (name.IsEmpty()) {
		sprintf_s(query_admin, "select S_id,S_name,user_key,S_sex,S_age"
			" from user_account,students "
			"where S_id = user_id AND S_id='%s';",m_id);
	}
	else {
		sprintf_s(query_admin, "select S_id,S_name,user_key,S_sex,S_age"
			" from user_account,students "
			"where S_id = user_id AND S_id='%s' AND S_name='%s';",m_id,m_name
		);
	}
	
	connectsql(&m_sqlCon_admin);
	
	mysql_query(&m_sqlCon_admin, query_admin);
	if ((m_res = mysql_store_result(&m_sqlCon_admin)) == NULL) {
		AfxMessageBox(_T("查询账号失败!"));
		return;
	}
	this->showdata(m_res);
	mysql_close(&m_sqlCon_admin);
}


void CDBwork_adminDlg::OnBnClickedButton2()//删除按钮
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_list.GetSelectionMark();   //获取选中行的行号
	CString s_id = m_list.GetItemText(nIndex, 0);   //获取第0列内容
	MYSQL_RES* m_res;
	connectsql(&m_sqlCon_admin);
	USES_CONVERSION;
	char* m_id = T2A(s_id);
	sprintf_s(query_admin, "DELETE FROM  user_account "
		"where user_id=%s;",m_id);
	if (mysql_query(&m_sqlCon_admin, query_admin))
	{
		AfxMessageBox(TEXT("删除数据失败！"));
		return;
	}
	
	m_list.DeleteItem(nIndex);//删除列表中的项
	
	mysql_close(&m_sqlCon_admin);
}




void CDBwork_adminDlg::OnBnClickedButton3()//插入
{
	// TODO: 在此添加控件通知处理程序代码
	CString name, id,sex,age;
	MYSQL_RES* m_res;
	MYSQL_ROW row;
	connectsql(&m_sqlCon_admin);
	GetDlgItem(IDC_EDIT3)->GetWindowText(id);
	GetDlgItem(IDC_EDIT1)->GetWindowText(name);
	GetDlgItem(IDC_EDIT4)->GetWindowText(age);
	GetDlgItem(IDC_EDIT5)->GetWindowText(sex);
	USES_CONVERSION;
	char* m_name = T2A(name);
	char* m_id = T2A(id);
	char* m_age = T2A(age);
	char* m_sex = T2A(sex);
	sprintf_s(query_admin, "select user_id"
			" from user_account "
			"where user_id=%s",m_id);
	mysql_query(&m_sqlCon_admin, query_admin);
	m_res = mysql_store_result(&m_sqlCon_admin);
	row = mysql_fetch_row(m_res);
	if (row!=NULL)
	{
		AfxMessageBox(TEXT("该账户已存在！"));
		mysql_close(&m_sqlCon_admin);
		return ;
	}
	sprintf_s(query_admin, "INSERT INTO user_account"
		" VALUES (%s,123456); "//默认密码123456
		, m_id);
	if (mysql_query(&m_sqlCon_admin, query_admin))
	{
		AfxMessageBox(TEXT("插入账户数据失败！"));
		mysql_close(&m_sqlCon_admin);
		return;
	}
	sprintf_s(query_admin, "INSERT INTO students"
		" VALUES (%s,'%s','%s','%s') "
		, m_id,m_name,m_sex,m_age);
	if (mysql_query(&m_sqlCon_admin, query_admin))
	{
		AfxMessageBox(TEXT("插入学生数据失败！"));
		mysql_close(&m_sqlCon_admin);
		return;
	}
	sprintf_s(query_admin, "select S_id,S_name,user_key,S_sex,S_age"
		" from user_account,students "
		"where S_id = user_id;");
	mysql_query(&m_sqlCon_admin, query_admin);
	m_res = mysql_store_result(&m_sqlCon_admin);
	m_list.DeleteAllItems();
	this->showdata(m_res);
	mysql_close(&m_sqlCon_admin);
}


void CDBwork_adminDlg::OnBnClickedButton4()//修改
{
	// TODO: 在此添加控件通知处理程序代码
	CString name, id, sex, age;
	MYSQL_RES* m_res;
	MYSQL_ROW row;
	connectsql(&m_sqlCon_admin);
	GetDlgItem(IDC_EDIT3)->GetWindowText(id);
	GetDlgItem(IDC_EDIT1)->GetWindowText(name);
	GetDlgItem(IDC_EDIT4)->GetWindowText(age);
	GetDlgItem(IDC_EDIT5)->GetWindowText(sex);
	USES_CONVERSION;
	char* m_name = T2A(name);
	char* m_id = T2A(id);
	char* m_age = T2A(age);
	char* m_sex = T2A(sex);
	sprintf_s(query_admin, "INSERT INTO user_account"
		" VALUES (%s,123456) "//默认密码123456
		, m_id);
	
	if (mysql_query(&m_sqlCon_admin, query_admin))
	{
		AfxMessageBox(TEXT("插入账户数据失败！"));
		mysql_close(&m_sqlCon_admin);
		return;
	}
	sprintf_s(query_admin, "INSERT INTO students"
		" VALUES (%s,'%s','%s','%s') "//默认密码123456
		, m_id, m_name, m_sex, m_age);
	if (mysql_query(&m_sqlCon_admin, query_admin))
	{
		AfxMessageBox(TEXT("插入学生数据失败！"));
		mysql_close(&m_sqlCon_admin);
		return;
	}
	mysql_close(&m_sqlCon_admin);
}


void CDBwork_adminDlg::showdata(MYSQL_RES* m_res)
{
	// TODO: 在此处添加实现代码.
	CString data[5];
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(m_res)) != NULL) {
		for (int i = 0; i < 5; i++) {
			data[i] = row[i];
		}
		m_list.InsertItem(0, data[0]);
		m_list.SetItemText(0, 1, data[1]);
		m_list.SetItemText(0, 2, data[2]);
		m_list.SetItemText(0, 3, data[3]);
		m_list.SetItemText(0, 4, data[4]);

	}
	return ;
}
