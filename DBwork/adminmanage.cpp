// adminmanage.cpp: 实现文件
//顾名扬添加

#include "pch.h"
#include "DBwork.h"
#include "afxdialogex.h"
#include "adminmanage.h"
#include"sql.h"
#include "framework.h"
#include "CDBwork_adminDlg.h"
#include< windows.h >
#include "adminBookBorrowRecord.h"

MYSQL m_sqlCon_adminbook;
char query_adminbook[1024] = "";

// adminmanage 对话框

IMPLEMENT_DYNAMIC(adminmanage, CDialogEx)

adminmanage::adminmanage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

adminmanage::~adminmanage()
{
}

void adminmanage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
}


BEGIN_MESSAGE_MAP(adminmanage, CDialogEx)
	ON_BN_CLICKED(IDC_BOOK_QUERY, &adminmanage::OnBnClickedBookQuery)
	ON_EN_CHANGE(IDC_EDIT_BOOK_ID, &adminmanage::OnEnChangeEditBookId)
	ON_EN_CHANGE(IDC_EDIT_BOOK_NAME, &adminmanage::OnEnChangeEditBookName)
	ON_EN_CHANGE(IDC_EDIT_BOOK_AUTHOR, &adminmanage::OnEnChangeEditBookAuthor)
	ON_BN_CLICKED(IDC_DONATION, &adminmanage::OnBnClickedDonation)
	ON_BN_CLICKED(IDC_RETURNBACK2, &adminmanage::OnBnClickedReturnback2)
	ON_BN_CLICKED(IDC_BORROW, &adminmanage::OnBnClickedBorrow)
END_MESSAGE_MAP()


// adminmanage 消息处理程序

BOOL adminmanage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_list1.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格   
	m_list1.SetExtendedStyle(m_list1.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加列   
	m_list1.InsertColumn(0, _T("书籍编号"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_list1.InsertColumn(1, _T("书名"), LVCFMT_CENTER, rect.Width() / 5, 1);
	m_list1.InsertColumn(2, _T("作者"), LVCFMT_CENTER, rect.Width() / 5, 2);
	m_list1.InsertColumn(3, _T("出版社"), LVCFMT_CENTER, rect.Width() / 5, 3);
	m_list1.InsertColumn(4, _T("借阅状态"), LVCFMT_CENTER, rect.Width() / 5, 4);
	//CDBworkDlg* p=CDBworkDlg::pCDBworkDlg;
	SetConsoleOutputCP(65001);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void adminmanage::showdata(MYSQL_RES* m_res)//用来显示查询框的内容
{
	// TODO: 在此处添加实现代码.
	CString data[5];
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(m_res)) != NULL) {
		for (int i = 0; i < 5; i++) {
			data[i] = row[i];
		}
		m_list1.InsertItem(0, data[0]);
		m_list1.SetItemText(0, 1, data[1]);
		m_list1.SetItemText(0, 2, data[2]);
		m_list1.SetItemText(0, 3, data[3]);
		m_list1.SetItemText(0, 4, data[4]);

	}
	return;
}

void adminmanage::OnBnClickedBookQuery()//书籍查询
{
	// TODO: 在此添加控件通知处理程序代码
	CString name, id, author;
	m_list1.DeleteAllItems();
	MYSQL_RES* m_res;
	//m_res = NULL;
	//MYSQL_ROW row;
	GetDlgItem(IDC_EDIT_BOOK_ID)->GetWindowText(id);
	GetDlgItem(IDC_EDIT_BOOK_NAME)->GetWindowText(name);
	GetDlgItem(IDC_EDIT_BOOK_AUTHOR)->GetWindowText(author);
	USES_CONVERSION;
	char* b_name = T2A(name);
	char* b_id = T2A(id);
	char* b_author = T2A(author);
	if (id.IsEmpty() && name.IsEmpty() && author.IsEmpty()) {//三个都不知道，则查询所有在库书籍
		sprintf_s(query_adminbook, "select book_id,book_name,book_author,book_publisher,book_state"
			" from book ;"
		);
	}
	else if (id.IsEmpty() && name.IsEmpty() == 0 && author.IsEmpty() == 0) {//id不知道
		sprintf_s(query_adminbook, "select book_id,book_name,book_author,book_publisher,book_state"
			" from book "
			"where book_name = '%s' AND book_author='%s';", b_name, b_author);
	}
	else if (id.IsEmpty() == 0 && name.IsEmpty() && author.IsEmpty() == 0) {//name不知道
		sprintf_s(query_adminbook, "select book_id,book_name,book_author,book_publisher,book_state"
			" from book "
			"where book_id = '%s' AND book_author='%s';", b_id, b_author);
	}
	else if (id.IsEmpty() == 0 && name.IsEmpty() == 0 && author.IsEmpty()) {//author不知道
		sprintf_s(query_adminbook, "select book_id,book_name,book_author,book_publisher,book_state"
			" from book "
			"where book_id = '%s' AND book_name='%s';", b_id, b_name);
	}
	else if (id.IsEmpty() == 0 && name.IsEmpty() && author.IsEmpty()) {//只知道id
		sprintf_s(query_adminbook, "select book_id,book_name,book_author,book_publisher,book_state"
			" from book "
			"where book_id = '%s' ;", b_id);
	}
	else if (id.IsEmpty() && name.IsEmpty() == 0 && author.IsEmpty()) {//只知道name
		sprintf_s(query_adminbook, "select book_id,book_name,book_author,book_publisher,book_state"
			" from book "
			"where book_name = '%s' ;", b_name);
	}
	else if (id.IsEmpty() && name.IsEmpty() && author.IsEmpty() == 0) {//只知道author
		sprintf_s(query_adminbook, "select book_id,book_name,book_author,book_publisher,book_state"
			" from book "
			"where book_author = '%s' ;", b_author);
	}
	else {//三个都知道，其实和只知道id一样
		sprintf_s(query_adminbook, "select book_id,book_name,book_author,book_publisher,book_state"
			" from book "
			"where book_id = '%s' AND book_name = '%s' AND book_author='%s';", b_id, b_name, b_author);
	}

	connectsql(&m_sqlCon_adminbook);

	mysql_query(&m_sqlCon_adminbook, query_adminbook);
	if ((m_res = mysql_store_result(&m_sqlCon_adminbook)) == NULL) {
		AfxMessageBox(_T("查询书籍失败!"));
		mysql_close(&m_sqlCon_adminbook);
		return;
	}
	this->showdata(m_res);
	mysql_close(&m_sqlCon_adminbook);
}

void adminmanage::OnBnClickedDonation()//添加书籍
{
	// TODO: 在此添加控件通知处理程序代码
	MYSQL_RES* m_res;
	//m_res = NULL;
	MYSQL_ROW row;
	CString DonateBookID, DonateBookName, DonateBookAuthor, DonateBookPublisher;
	GetDlgItem(IDC_EDIT_BOOK_ID2)->GetWindowText(DonateBookID);
	GetDlgItem(IDC_EDIT_BOOK_NAME2)->GetWindowText(DonateBookName);
	GetDlgItem(IDC_EDIT_BOOK_AUTHOR2)->GetWindowText(DonateBookAuthor);
	GetDlgItem(IDC_EDIT_BOOK_PUBLISHER2)->GetWindowText(DonateBookPublisher);
	USES_CONVERSION;
	char* bid = T2A(DonateBookID);//CString ==> char*
	char* bname = T2A(DonateBookName);
	char* bauthor = T2A(DonateBookAuthor);
	char* bpublisher = T2A(DonateBookPublisher);
	if (DonateBookID.IsEmpty() || DonateBookName.IsEmpty() || DonateBookAuthor.IsEmpty() || DonateBookPublisher.IsEmpty())
	{
		AfxMessageBox(_T("添加书籍失败，请填写完整信息"));
		mysql_close(&m_sqlCon_adminbook);
		return;
	}
	connectsql(&m_sqlCon_adminbook);
	sprintf_s(query_adminbook, "select book_id"
		" from book "
		"where book_id=%s", bid);
	mysql_query(&m_sqlCon_adminbook, query_adminbook);
	m_res = mysql_store_result(&m_sqlCon_adminbook);
	row = mysql_fetch_row(m_res);
	if (row != NULL)
	{
		AfxMessageBox(TEXT("该书籍已存在！"));
		mysql_close(&m_sqlCon_adminbook);
		return;
	}
	if (DonateBookID.IsEmpty() == 0 && DonateBookName.IsEmpty() == 0 && DonateBookAuthor.IsEmpty() == 0 && DonateBookPublisher.IsEmpty() == 0)
	{
		sprintf_s(query_adminbook, "INSERT INTO book VALUES('%s','%s','%s','%s','%s');", bid, bname, bauthor, bpublisher, "在册");
		mysql_query(&m_sqlCon_adminbook, query_adminbook);
		AfxMessageBox(TEXT("成功添加书籍！"));
		mysql_close(&m_sqlCon_adminbook);
		return;
	}
}

void adminmanage::OnBnClickedReturnback2()//删除书籍
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_list1.GetSelectionMark();   //获取查询框选中行的行号
	CString b_id = m_list1.GetItemText(nIndex, 0);   //获取查询框第0列内容
	CString b_state = m_list1.GetItemText(nIndex, 4);   //获取查询框第4列内容
	MYSQL_RES* m_res;
	connectsql(&m_sqlCon_adminbook);
	USES_CONVERSION;
	char* m_id = T2A(b_id);
	char* m_state = T2A(b_state);
	sprintf_s(query_adminbook, "DELETE FROM book"
		" WHERE book_id='%s' AND book_state='在册'; ", m_id);
	if (mysql_query(&m_sqlCon_adminbook, query_adminbook))
	{
		AfxMessageBox(TEXT("书籍删除失败，请重新尝试！"));
		mysql_close(&m_sqlCon_adminbook);
		return;
	}
	if (b_state == "被借阅")
	{
		AfxMessageBox(TEXT("此书已被借阅，请勿尝试删除！"));
		mysql_close(&m_sqlCon_adminbook);
		return;
	}
	else {
		AfxMessageBox(TEXT("成功删除书籍！"));
		mysql_close(&m_sqlCon_adminbook);
		return;
	}
}

void adminmanage::OnBnClickedBorrow()
{
	// TODO: 在此添加控件通知处理程序代码
	adminBookBorrowRecord dlg;
	dlg.DoModal();
}


void adminmanage::OnEnChangeEditBookId()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void adminmanage::OnEnChangeEditBookName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void adminmanage::OnEnChangeEditBookAuthor()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

