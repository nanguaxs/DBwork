// adminBookBorrowRecord.cpp: 实现文件
//顾名扬添加

#include "pch.h"
#include "DBwork.h"
#include "afxdialogex.h"
#include "adminBookBorrowRecord.h"
#include "adminmanage.h"
#include"sql.h"
#include "framework.h"
#include "CDBwork_adminDlg.h"
#include< windows.h >

MYSQL m_sqlCon_borrowrecord;
char query_borrowrecord[1024] = "";

// adminBookBorrowRecord 对话框

IMPLEMENT_DYNAMIC(adminBookBorrowRecord, CDialogEx)

adminBookBorrowRecord::adminBookBorrowRecord(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{

}

adminBookBorrowRecord::~adminBookBorrowRecord()
{
}

void adminBookBorrowRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Control(pDX, IDC_LIST3, m_list3);
}


BEGIN_MESSAGE_MAP(adminBookBorrowRecord, CDialogEx)
	//ON_BN_CLICKED(IDOK, &adminBookBorrowRecord::OnBnClickedOk)
	//ON_BN_CLICKED(IDOK2, &adminBookBorrowRecord::OnBnClickedOk2)
	ON_EN_CHANGE(IDC_EDIT_NAME2, &adminBookBorrowRecord::OnEnChangeEditName2)
	ON_EN_CHANGE(IDC_EDIT_ID2, &adminBookBorrowRecord::OnEnChangeEditId2)
	ON_EN_CHANGE(IDC_EDIT_NAME1, &adminBookBorrowRecord::OnEnChangeEditName1)
	ON_EN_CHANGE(IDC_EDIT_ID1, &adminBookBorrowRecord::OnEnChangeEditId1)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &adminBookBorrowRecord::OnLvnItemchangedList2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &adminBookBorrowRecord::OnLvnItemchangedList3)
	ON_BN_CLICKED(IDC_BUTTON1, &adminBookBorrowRecord::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &adminBookBorrowRecord::OnBnClickedButton2)
END_MESSAGE_MAP()


// adminBookBorrowRecord 消息处理程序
BOOL adminBookBorrowRecord::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_list3.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格   
	m_list3.SetExtendedStyle(m_list3.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加列   
	m_list3.InsertColumn(0, _T("书籍编号"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_list3.InsertColumn(1, _T("书名"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_list3.InsertColumn(2, _T("作者"), LVCFMT_CENTER, rect.Width() / 6, 2);
	m_list3.InsertColumn(3, _T("出版社"), LVCFMT_CENTER, rect.Width() / 6, 3);
	m_list3.InsertColumn(4, _T("借阅人学号"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_list3.InsertColumn(5, _T("借阅人姓名"), LVCFMT_CENTER, rect.Width() / 6, 5);
	//CDBworkDlg* p=CDBworkDlg::pCDBworkDlg;
	SetConsoleOutputCP(65001);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void adminBookBorrowRecord::showdata2(MYSQL_RES* m_res)
{
	CString data[6];
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(m_res)) != NULL) {
		for (int i = 0; i < 6; i++) {
			data[i] = row[i];
		}
		m_list3.InsertItem(0, data[0]);
		m_list3.SetItemText(0, 1, data[1]);
		m_list3.SetItemText(0, 2, data[2]);
		m_list3.SetItemText(0, 3, data[3]);
		m_list3.SetItemText(0, 4, data[4]);
		m_list3.SetItemText(0, 5, data[5]);

	}
	return;
}

void adminBookBorrowRecord::OnBnClickedButton1()//通过借阅人信息查询
{
	// TODO: 在此添加控件通知处理程序代码
	CString name, id;
	m_list3.DeleteAllItems();
	MYSQL_RES* m_res;
	//m_res = NULL;
	//MYSQL_ROW row;
	GetDlgItem(IDC_EDIT_ID1)->GetWindowText(id);
	GetDlgItem(IDC_EDIT_NAME1)->GetWindowText(name);
	USES_CONVERSION;
	char* b_name = T2A(name);
	char* b_id = T2A(id);
	if (id.IsEmpty() && name.IsEmpty()) {//两个都不知道，则查询所有被借阅书籍
		/*sprintf_s(query_borrowrecord, "select B.book_id,B.book_name,B.book_author,B.book_publisher,R.id_user,S.S_name"
			" from book B,record R,students S "
			"where R.id_user=S.S_id AND R.id_book=B.book_name AND B.book_state=R.state AND B.book_state='被借阅';");
		sprintf_s(query_borrowrecord,  "select book.book_id,book.book_name,book.book_author,book.book_publisher,m.id_user,m.S_name"
					  " from book left outer join m on book.book_id=m.id_book "
					  "where("
					           "select record.id_user,students.S_name,record.id_book"
					           " from record left outer join students on record.id_user=students.S_id "
							   "where record.state='被借阅'"
							 ")as m;");
		*/
		sprintf_s(query_borrowrecord, 
			          "select book.book_id,book.book_name,book.book_author,book.book_publisher,record.id_user,students.S_name"
					  " from book left outer join record on book.book_id=record.id_book,students "
					  "where book.book_state='被借阅' AND students.S_id=record.id_user;"
		);
		
	}
	else if (id.IsEmpty()) {//只知道name
		sprintf_s(query_borrowrecord, "select B.book_id,B.book_name,B.book_author,B.book_publisher,R.id_user,S.S_name"
			" from book B,record R,students S "
			"where S.S_name = '%s' AND R.id_user=S.S_id AND R.id_book=B.book_id AND B.book_state=R.state AND B.book_state='被借阅';", b_name);
	}
	else if (name.IsEmpty()) {//只知道id
		sprintf_s(query_borrowrecord, "select B.book_id,B.book_name,B.book_author,B.book_publisher,R.id_user,S.S_name"
			" from book B,record R,students S "
			"where S.S_id = '%s' AND R.id_user=S.S_id AND R.id_book=B.book_id AND B.book_state=R.state AND B.book_state='被借阅';", b_id);
	}
	else {//两个都知道，其实和只知道id一样
		sprintf_s(query_borrowrecord, "select B.book_id,B.book_name,B.book_author,B.book_publisher,R.id_user,S.S_name"
			" from book B,record R,students S "
			"where S.S_name = '%s' AND S.S_id='%s' AND R.id_user=S.S_id AND R.id_book=B.book_name AND B.book_state=R.state AND B.book_state='被借阅';", b_name, b_id);
	}

	connectsql(&m_sqlCon_borrowrecord);

	mysql_query(&m_sqlCon_borrowrecord, query_borrowrecord);
	if ((m_res = mysql_store_result(&m_sqlCon_borrowrecord)) == NULL) {
		AfxMessageBox(_T("查询记录失败!"));
		mysql_close(&m_sqlCon_borrowrecord);
		return;
	}
	this->showdata2(m_res);
	mysql_close(&m_sqlCon_borrowrecord);
}


void adminBookBorrowRecord::OnBnClickedButton2()//通过被借阅的书籍查询
{
	// TODO: 在此添加控件通知处理程序代码
	CString name, id;
	m_list3.DeleteAllItems();
	MYSQL_RES* m_res;
	//m_res = NULL;
	//MYSQL_ROW row;
	GetDlgItem(IDC_EDIT_ID2)->GetWindowText(id);
	GetDlgItem(IDC_EDIT_NAME2)->GetWindowText(name);
	USES_CONVERSION;
	char* b_name = T2A(name);
	char* b_id = T2A(id);
	if (id.IsEmpty() && name.IsEmpty()) {//两个都不知道，则查询所有被借阅书籍
		sprintf_s(query_borrowrecord,
			"select book.book_id,book.book_name,book.book_author,book.book_publisher,record.id_user,students.S_name"
			" from book left outer join record on book.book_id=record.id_book,students "
			"where book.book_state='被借阅' AND students.S_id=record.id_user;"
			);
	}
	else if (id.IsEmpty()) {//只知道name
		sprintf_s(query_borrowrecord, "select B.book_id,B.book_name,B.book_author,B.book_publisher,R.id_user,S.S_name"
			" from book B,record R,students S "
			"where B.book_name = '%s' AND R.id_user=S.S_id AND R.id_book=B.book_id AND B.book_state=R.state AND B.book_state='被借阅';", b_name);
	}
	else if (name.IsEmpty()) {//只知道id
		sprintf_s(query_borrowrecord, "select B.book_id,B.book_name,B.book_author,B.book_publisher,R.id_user,S.S_name"
			" from book B,record R,students S "
			"where B.book_id = '%s' AND R.id_user=S.S_id AND R.id_book=B.book_id AND B.book_state=R.state AND B.book_state='被借阅';", b_id);
	}
	else {//两个都知道，其实和只知道id一样
		sprintf_s(query_borrowrecord, "select B.book_id,B.book_name,B.book_author,B.book_publisher,R.id_user,S.S_name"
			" from book B,record R,students S "
			"where B.book_name = '%s' AND B.book_id='%s' AND R.id_user=S.S_id AND R.id_book=B.book_name AND B.book_state=R.state AND B.book_state='被借阅';", b_name, b_id);
	}

	connectsql(&m_sqlCon_borrowrecord);

	mysql_query(&m_sqlCon_borrowrecord, query_borrowrecord);
	if ((m_res = mysql_store_result(&m_sqlCon_borrowrecord)) == NULL) {
		AfxMessageBox(_T("查询记录失败!"));
		mysql_close(&m_sqlCon_borrowrecord);
		return;
	}
	this->showdata2(m_res);
	mysql_close(&m_sqlCon_borrowrecord);
}

void adminBookBorrowRecord::OnEnChangeEditName2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void adminBookBorrowRecord::OnEnChangeEditId2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void adminBookBorrowRecord::OnEnChangeEditName1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void adminBookBorrowRecord::OnEnChangeEditId1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


/*void adminBookBorrowRecord::OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
*/

void adminBookBorrowRecord::OnLvnItemchangedList3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
