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
	ON_BN_CLICKED(IDC_BUTTON4, &CDBwork_userDlg::OnBnClickedButton4)
	//ON_EN_CHANGE(IDC_EDIT16, &CDBwork_userDlg::OnEnChangeEdit16)
	ON_STN_CLICKED(IDC_BOOK_ID, &CDBwork_userDlg::OnStnClickedBookId)
	ON_BN_CLICKED(IDC_BOOK_QUERY, &CDBwork_userDlg::OnBnClickedBookQuery)
	ON_EN_CHANGE(IDC_EDIT3, &CDBwork_userDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CDBwork_userDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT_BOOK_ID2, &CDBwork_userDlg::OnEnChangeEditBookId2)
	ON_BN_CLICKED(IDC_DONATION, &CDBwork_userDlg::OnBnClickedDonation)
	ON_EN_CHANGE(IDC_EDIT_BOOK_PUBLISHER2, &CDBwork_userDlg::OnEnChangeEditBookPublisher2)
	ON_EN_CHANGE(IDC_EDIT_BOOK_AUTHOR2, &CDBwork_userDlg::OnEnChangeEditBookAuthor2)
	ON_EN_CHANGE(IDC_EDIT_BOOK_NAME2, &CDBwork_userDlg::OnEnChangeEditBookName2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CDBwork_userDlg::OnLvnItemchangedList2)
	ON_BN_CLICKED(IDC_RETURNBACK, &CDBwork_userDlg::OnBnClickedReturnback)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CDBwork_userDlg::OnLvnItemchangedList1)
	ON_EN_CHANGE(IDC_EDIT_BOOK_ID, &CDBwork_userDlg::OnEnChangeEditBookId)
	ON_EN_CHANGE(IDC_EDIT_BOOK_NAME, &CDBwork_userDlg::OnEnChangeEditBookName)
	ON_EN_CHANGE(IDC_EDIT_BOOK_AUTHOR, &CDBwork_userDlg::OnEnChangeEditBookAuthor)
	ON_EN_CHANGE(IDC_EDIT6, &CDBwork_userDlg::OnEnChangeEdit6)
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


void CDBwork_userDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDBwork_userDlg::OnEnChangeEdit16()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDBwork_userDlg::OnStnClickedBookId()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDBwork_userDlg::OnBnClickedBookQuery()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDBwork_userDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDBwork_userDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDBwork_userDlg::OnEnChangeEditBookId2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDBwork_userDlg::OnBnClickedDonation()//图书捐赠按钮
{
	// TODO: 在此添加控件通知处理程序代码
	// 顾名扬完成
	CString DonateBookID;
	CString DonateBookName;
	CString DonateBookAuthor;
	CString DonateBookPublisher;
	GetDlgItemText(IDC_EDIT_BOOK_ID2, DonateBookID);
	GetDlgItemText(IDC_EDIT_BOOK_NAME2, DonateBookName);
	GetDlgItemText(IDC_EDIT_BOOK_AUTHOR2, DonateBookAuthor);
	GetDlgItemText(IDC_EDIT_BOOK_PUBLISHER2, DonateBookPublisher);
	if (DonateBookID == "" || DonateBookName == "" || DonateBookAuthor == "" || DonateBookPublisher == "")
	{
		AfxMessageBox(_T("捐赠失败，请填写完整信息"));
	}
	else {
		AfxMessageBox(_T("捐赠成功，感谢您的捐赠"));
	}
}


void CDBwork_userDlg::OnEnChangeEditBookPublisher2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDBwork_userDlg::OnEnChangeEditBookAuthor2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDBwork_userDlg::OnEnChangeEditBookName2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDBwork_userDlg::OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CDBwork_userDlg::OnBnClickedReturnback()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDBwork_userDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CDBwork_userDlg::OnEnChangeEditBookId()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDBwork_userDlg::OnEnChangeEditBookName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDBwork_userDlg::OnEnChangeEditBookAuthor()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDBwork_userDlg::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
