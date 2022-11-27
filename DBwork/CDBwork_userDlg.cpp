// CDBwork_userDlg.cpp: 实现文件
//

#include "pch.h"
#include "DBwork.h"
#include "afxdialogex.h"
#include "CDBwork_userDlg.h"
#include"sql.h"

// CDBwork_userDlg 对话框

IMPLEMENT_DYNAMIC(CDBwork_userDlg, CDialogEx)

CDBwork_userDlg::CDBwork_userDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_user, pParent)
{
	
}

CDBwork_userDlg::~CDBwork_userDlg()
{
}

void CDBwork_userDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDBwork_userDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDBwork_userDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDBwork_userDlg 消息处理程序


void CDBwork_userDlg::OnBnClickedButton1()
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
	if (strcmp(row[0],m_oldpass)) {
		AfxMessageBox(_T("密码错误!"));
		return;
	}
	sprintf_s(query, "UPDATE user_account"
		" SET user_key='%s'"
		" WHERE user_id=%s",
		m_newpass,this->user_id);
	if (mysql_query(&m_sqlCon, query)) {
		AfxMessageBox(_T("修改密码失败!"));
		return;
	};
	AfxMessageBox(_T("修改密码成功!"));
	return;
	mysql_close(&m_sqlCon);
}
