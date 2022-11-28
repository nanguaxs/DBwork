// user.cpp: 实现文件
//

#include "pch.h"
#include "DBwork.h"
#include "afxdialogex.h"
#include "user.h"
#include"sql.h"
#include"CDBwork_userDlg.h"
#include"paperDlg.h"
// user 对话框

IMPLEMENT_DYNAMIC(user, CDialogEx)

user::user(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

user::~user()
{
}

void user::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(user, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &user::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &user::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &user::OnBnClickedButton3)
END_MESSAGE_MAP()


// user 消息处理程序


void user::OnBnClickedButton1()//修改密码按钮
{
	// TODO: 在此添加控件通知处理程序代码
	MYSQL m_sqlCon;
	char query[1024];
	MYSQL_RES* m_res;
	MYSQL_ROW row;
	CString oldpass, newpass;
	GetDlgItem(IDC_EDIT1)->GetWindowText(oldpass);

	GetDlgItem(IDC_EDIT2)->GetWindowText(newpass);
	USES_CONVERSION;
	char* m_oldpass = T2A(oldpass);

	char* m_newpass = T2A(newpass);
	connectsql(&m_sqlCon);
	sprintf_s(query, "select user_key from user_account where user_id='%s';",
		this->user_id);
	mysql_query(&m_sqlCon, query);
	m_res = mysql_store_result(&m_sqlCon);
	row = mysql_fetch_row(m_res);
	if (strcmp(row[0], m_oldpass)) {
		AfxMessageBox(_T("密码错误!"));
		return;
	}
	sprintf_s(query, "UPDATE user_account"
		" SET user_key='%s'"
		" WHERE user_id=%s",
		m_newpass, this->user_id);
	if (mysql_query(&m_sqlCon, query)) {
		AfxMessageBox(_T("修改密码失败!"));
		return;
	};
	AfxMessageBox(_T("修改密码成功!"));
	return;
	mysql_close(&m_sqlCon);
}


void user::OnBnClickedButton2()//书籍操作
{
	// TODO: 在此添加控件通知处理程序代码
	CDBwork_userDlg dlg;
	dlg.user_id = this->user_id;
	dlg.DoModal();
}


void user::OnBnClickedButton3()//论文操作
{
	// TODO: 在此添加控件通知处理程序代码
	paperDlg dlg;
	dlg.user_id = this->user_id;
	dlg.DoModal();
}
