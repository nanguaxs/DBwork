// bookBorrowQuery.cpp: 实现文件
//顾名扬添加

#include "pch.h"
#include "DBwork.h"
#include "afxdialogex.h"
#include "bookBorrowQuery.h"
#include "CDBwork_userDlg.h"
#include"sql.h"

#include"CDBwork_adminDlg.h"

MYSQL m_sqlCon_borrow;
char query_borrow[1024] = "";
// bookBorrowQuery 对话框

IMPLEMENT_DYNAMIC(bookBorrowQuery, CDialogEx)

bookBorrowQuery::bookBorrowQuery(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

bookBorrowQuery::~bookBorrowQuery()
{
}

void bookBorrowQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, c_list3);
}


BEGIN_MESSAGE_MAP(bookBorrowQuery, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, &bookBorrowQuery::OnBnClickedButtonQuery)
	ON_BN_CLICKED(IDC_BUTTON_RETURN, &bookBorrowQuery::OnBnClickedButtonReturn)
END_MESSAGE_MAP()


// bookBorrowQuery 消息处理程序

BOOL bookBorrowQuery::OnInitDialog()
{
	//图书查询框
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	c_list3.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格   
	c_list3.SetExtendedStyle(c_list3.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加列   
	c_list3.InsertColumn(0, _T("书籍编号"), LVCFMT_CENTER, rect.Width() / 5, 0);
	c_list3.InsertColumn(1, _T("书名"), LVCFMT_CENTER, rect.Width() / 5, 1);
	c_list3.InsertColumn(2, _T("作者"), LVCFMT_CENTER, rect.Width() / 5, 2);
	c_list3.InsertColumn(3, _T("出版社"), LVCFMT_CENTER, rect.Width() / 5, 3);
	c_list3.InsertColumn(4, _T("借阅状态"), LVCFMT_CENTER, rect.Width() / 5, 4);
	//CDBworkDlg* p=CDBworkDlg::pCDBworkDlg;
	SetConsoleOutputCP(65001);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void bookBorrowQuery::showdata(MYSQL_RES* m_res)
{
	// TODO: 在此处添加实现代码.
	CString data[5];
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(m_res)) != NULL) {
		for (int i = 0; i < 5; i++) {
			data[i] = row[i];
		}
		c_list3.InsertItem(0, data[0]);
		c_list3.SetItemText(0, 1, data[1]);
		c_list3.SetItemText(0, 2, data[2]);
		c_list3.SetItemText(0, 3, data[3]);
		c_list3.SetItemText(0, 4, data[4]);

	}
	return;
}

void bookBorrowQuery::OnBnClickedButtonQuery()//借阅查询
{
	// TODO: 在此添加控件通知处理程序代码
	c_list3.DeleteAllItems();
	MYSQL_RES* m_res;
	USES_CONVERSION;
	sprintf_s(query_borrow, "select B.book_id,B.book_name,B.book_author,B.book_publisher,B.book_state"
		" from book B,record R,user_account U,students S"
		" where U.user_id='%s' AND U.user_id = S.S_id AND U.user_id = R.id_user AND B.book_state = R.state AND R.id_book=B.book_id;", this->user_id);
	//SQL语句出现问题，需要修改
	connectsql(&m_sqlCon_borrow);
	mysql_query(&m_sqlCon_borrow, query_borrow);
	if ((m_res = mysql_store_result(&m_sqlCon_borrow)) == NULL) {
		AfxMessageBox(_T("查询失败!"));
		mysql_close(&m_sqlCon_borrow);
		return;
	}
	this->showdata(m_res);
	mysql_close(&m_sqlCon_borrow);
}

void bookBorrowQuery::OnBnClickedButtonReturn()//归还图书
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = c_list3.GetSelectionMark();   //获取查询框选中行的行号
	CString s_id = c_list3.GetItemText(nIndex, 0);   //获取查询框第0列内容
	CString s_state = c_list3.GetItemText(nIndex, 4);   //获取查询框第4列内容
	MYSQL_RES* m_res;
	connectsql(&m_sqlCon_borrow);
	USES_CONVERSION;
	char* m_id = T2A(s_id);
	char* m_state = T2A(s_state);
	sprintf_s(query_borrow, "UPDATE book "
		"SET book_state='在册' "
		"where book_id=%s;", m_id);
	if (mysql_query(&m_sqlCon_borrow, query_borrow))
	{
		AfxMessageBox(TEXT("归还书籍失败，请重新尝试！"));
		mysql_close(&m_sqlCon_borrow);
		return;
	}
	if (s_state == "在册")
	{
		AfxMessageBox(TEXT("此书已被归还，请勿重复尝试！"));
		mysql_close(&m_sqlCon_borrow);
		return;
	}
	else {
		sprintf_s(query_borrow, "DELETE FROM record"
			" WHERE id_book='%s' AND id_user='%s' AND state='%s';", m_id, this->user_id, "被借阅");
		mysql_query(&m_sqlCon_borrow, query_borrow);
		AfxMessageBox(TEXT("归还成功！"));
		mysql_close(&m_sqlCon_borrow);
		return;
	}
}
