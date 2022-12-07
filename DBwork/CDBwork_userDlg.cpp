// CDBwork_userDlg.cpp: 实现文件
//

#include "pch.h"
#include "DBwork.h"
#include "afxdialogex.h"
#include "CDBwork_userDlg.h"
#include"sql.h"

#include"CDBwork_adminDlg.h"

MYSQL m_sqlCon_client;
char query_client[1024] = "";


// CDBwork_userDlg 对话框

IMPLEMENT_DYNAMIC(CDBwork_userDlg, CDialogEx)

CDBwork_userDlg::CDBwork_userDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_user, pParent)
	//顾名扬修改
	, c_id(_T(""))
	, c_name(_T(""))
	, c_author(_T(""))
{
	
}

CDBwork_userDlg::~CDBwork_userDlg()
{
}

void CDBwork_userDlg::DoDataExchange(CDataExchange* pDX)
{//顾名扬修改
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BOOK_ID, c_id);
	DDX_Text(pDX, IDC_EDIT_BOOK_NAME, c_name);
	DDX_Text(pDX, IDC_EDIT_BOOK_AUTHOR, c_author);
	DDX_Control(pDX, IDC_LIST1, c_list);
	DDX_Control(pDX, IDC_LIST2, c_list2);
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
	ON_BN_CLICKED(IDC_BORROW, &CDBwork_userDlg::OnBnClickedBorrow)
	ON_STN_CLICKED(IDC_BOOK_AUTHOR, &CDBwork_userDlg::OnStnClickedBookAuthor)
	ON_BN_CLICKED(IDC_BOOK_QUERY2, &CDBwork_userDlg::OnBnClickedBookQuery2)
	ON_BN_CLICKED(IDC_RETURNBACK2, &CDBwork_userDlg::OnBnClickedReturnback2)
END_MESSAGE_MAP()


// CDBwork_userDlg 消息处理程序


void CDBwork_userDlg::OnBnClickedButton1()//修改密码
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


BOOL CDBwork_userDlg::OnInitDialog()//顾名扬增加
{//图书查询框
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	c_list.GetClientRect(&rect);
	c_list2.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格   
	c_list.SetExtendedStyle(c_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	c_list2.SetExtendedStyle(c_list2.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加列   
	c_list.InsertColumn(0, _T("书籍编号"), LVCFMT_CENTER, rect.Width() / 5, 0);
	c_list.InsertColumn(1, _T("书名"), LVCFMT_CENTER, rect.Width() / 5, 1);
	c_list.InsertColumn(2, _T("作者"), LVCFMT_CENTER, rect.Width() / 5, 2);
	c_list.InsertColumn(3, _T("出版社"), LVCFMT_CENTER, rect.Width() / 5, 3);
	c_list.InsertColumn(4, _T("借阅状态"), LVCFMT_CENTER, rect.Width() / 5, 4);
	c_list2.InsertColumn(0, _T("书籍编号"), LVCFMT_CENTER, rect.Width() / 5, 0);
	c_list2.InsertColumn(1, _T("书名"), LVCFMT_CENTER, rect.Width() / 5, 1);
	c_list2.InsertColumn(2, _T("作者"), LVCFMT_CENTER, rect.Width() / 5, 2);
	c_list2.InsertColumn(3, _T("出版社"), LVCFMT_CENTER, rect.Width() / 5, 3);
	c_list2.InsertColumn(4, _T("借阅状态"), LVCFMT_CENTER, rect.Width() / 5, 4);
	//CDBworkDlg* p=CDBworkDlg::pCDBworkDlg;
	SetConsoleOutputCP(65001);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDBwork_userDlg::OnBnClickedBookQuery()//书籍查询
{
	// TODO: 在此添加控件通知处理程序代码
	//顾名扬完成
	CString name, id, author;
	c_list.DeleteAllItems();
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
		sprintf_s(query_client, "select book_id,book_name,book_author,book_publisher,book_state"
			" from book ;"
		);
	}
	else if (id.IsEmpty() && name.IsEmpty() == 0 && author.IsEmpty() == 0) {//id不知道
		sprintf_s(query_client, "select book_id,book_name,book_author,book_publisher,book_state"
			" from book "
			"where book_name = '%s' AND book_author='%s';", b_name, b_author);
	}
	else if (id.IsEmpty()==0 && name.IsEmpty()  && author.IsEmpty() == 0) {//name不知道
		sprintf_s(query_client, "select book_id,book_name,book_author,book_publisher,book_state"
			" from book "
			"where book_id = '%s' AND book_author='%s';", b_id, b_author);
	}
	else if (id.IsEmpty() == 0 && name.IsEmpty()==0 && author.IsEmpty()) {//author不知道
		sprintf_s(query_client, "select book_id,book_name,book_author,book_publisher,book_state"
			" from book "
			"where book_id = '%s' AND book_name='%s';", b_id, b_name);
	}
	else if (id.IsEmpty() == 0 && name.IsEmpty()  && author.IsEmpty()) {//只知道id
		sprintf_s(query_client, "select book_id,book_name,book_author,book_publisher,book_state"
			" from book "
			"where book_id = '%s' ;", b_id);
	}
	else if (id.IsEmpty()  && name.IsEmpty()==0 && author.IsEmpty()) {//只知道name
		sprintf_s(query_client, "select book_id,book_name,book_author,book_publisher,book_state"
			" from book "
			"where book_name = '%s' ;", b_name);
	}
	else if (id.IsEmpty() && name.IsEmpty() && author.IsEmpty()==0) {//只知道author
		sprintf_s(query_client, "select book_id,book_name,book_author,book_publisher,book_state"
			" from book "
			"where book_author = '%s' ;", b_author);
	}
	else {//三个都知道，其实和只知道id一样
		sprintf_s(query_client, "select book_id,book_name,book_author,book_publisher,book_state"
			" from book "
			"where book_id = '%s' AND book_name = '%s' AND book_author='%s';", b_id, b_name, b_author);
	}

	connectsql(&m_sqlCon_client);

	mysql_query(&m_sqlCon_client, query_client);
	if ((m_res = mysql_store_result(&m_sqlCon_client)) == NULL) {
		AfxMessageBox(_T("查询书籍失败!"));
		mysql_close(&m_sqlCon_client);
		return;
	}
	this->showdata(m_res);
	mysql_close(&m_sqlCon_client);
	
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
	//完全解决
	MYSQL_RES* m_res;
	//m_res = NULL;
	MYSQL_ROW row;
	CString DonateBookID,DonateBookName,DonateBookAuthor,DonateBookPublisher;
	connectsql(&m_sqlCon_client);
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
		AfxMessageBox(_T("捐赠失败，请填写完整信息"));
		mysql_close(&m_sqlCon_client);
		return;
	}
	sprintf_s(query_client, "select book_id"
		" from book "
		"where book_id=%s", bid);
	mysql_query(&m_sqlCon_client, query_client);
	m_res = mysql_store_result(&m_sqlCon_client);
	row = mysql_fetch_row(m_res);
	if (row != NULL)
	{
		AfxMessageBox(TEXT("该书籍已存在！"));
		mysql_close(&m_sqlCon_client);
		return;
	}
	sprintf_s(query_client, "INSERT INTO book VALUES('%s','%s','%s','%s','%s');",bid, bname, bauthor, bpublisher,"在册");  
	if (DonateBookID.IsEmpty() || DonateBookName.IsEmpty() || DonateBookAuthor.IsEmpty() || DonateBookPublisher.IsEmpty())
	{
		AfxMessageBox(_T("捐赠失败，请填写完整信息"));
		mysql_close(&m_sqlCon_client);
		return;
	}
	if (DonateBookID.IsEmpty() || DonateBookName.IsEmpty() || DonateBookAuthor.IsEmpty() || DonateBookPublisher.IsEmpty())
	{
		AfxMessageBox(TEXT("捐赠成功，感谢您的捐赠！"));
		mysql_close(&m_sqlCon_client);
		return;
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


void CDBwork_userDlg::OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult)//借阅框
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


void CDBwork_userDlg::showdata(MYSQL_RES* m_res)//用来显示查询框的内容
{
	// TODO: 在此处添加实现代码.
	CString data[5];
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(m_res)) != NULL) {
		for (int i = 0; i < 5; i++) {
			data[i] = row[i];
		}
		c_list.InsertItem(0, data[0]);
		c_list.SetItemText(0, 1, data[1]);
		c_list.SetItemText(0, 2, data[2]);
		c_list.SetItemText(0, 3, data[3]);
		c_list.SetItemText(0, 4, data[4]);

	}
	return;
}
void CDBwork_userDlg::showdata2(MYSQL_RES* m_res)//用来显示借阅框的内容
{
	// TODO: 在此处添加实现代码.
	CString data[5];
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(m_res)) != NULL) {
		for (int i = 0; i < 5; i++) {
			data[i] = row[i];
		}
		c_list2.InsertItem(0, data[0]);
		c_list2.SetItemText(0, 1, data[1]);
		c_list2.SetItemText(0, 2, data[2]);
		c_list2.SetItemText(0, 3, data[3]);
		c_list2.SetItemText(0, 4, data[4]);

	}
	return;
}

void CDBwork_userDlg::OnBnClickedBorrow()//借阅图书
{
	// TODO: 在此添加控件通知处理程序代码
	//顾名扬完成
	//问题：实际上表里的数据已经改为借阅模式，但是未能够成功实现在显示框内展现借阅的书籍
	int nIndex = c_list.GetSelectionMark();   //获取查询框选中行的行号
	CString s_id = c_list.GetItemText(nIndex, 0);   //获取查询框第0列内容
	CString s_state = c_list.GetItemText(nIndex, 4);   //获取查询框第4列内容
	MYSQL_RES* m_res;
	connectsql(&m_sqlCon_client);
	USES_CONVERSION;
	char* m_id = T2A(s_id);
	char* m_state = T2A(s_state);
	sprintf_s(query_client, "UPDATE book "
		"SET book_state='被借阅' "
		"where book_id=%s;", m_id);
	if (mysql_query(&m_sqlCon_client, query_client))
	{
		AfxMessageBox(TEXT("借阅书籍失败，请重新尝试！"));
		mysql_close(&m_sqlCon_client);
		return;
	}
	if (s_state == "被借阅")
	{
		AfxMessageBox(TEXT("此书已被借阅，请借阅其他书籍！"));
		mysql_close(&m_sqlCon_client);
		return;
	}
	else{
		AfxMessageBox(TEXT("借阅成功！"));
		mysql_close(&m_sqlCon_client);
		return;
	}
	//OnBnClickedBookQuery2();//在借阅框中显示所有自己借过的书
	/*sprintf_s(query_client, "select book_id,book_name,book_author,book_publisher,book_state"
		" from book "
		"where book_state = '被借阅';");
	mysql_query(&m_sqlCon_client, query_client);
	m_res = mysql_store_result(&m_sqlCon_client);
	c_list.DeleteAllItems();
	this->showdata(m_res);//待定
	mysql_close(&m_sqlCon_client);*/
}


void CDBwork_userDlg::OnStnClickedBookAuthor()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDBwork_userDlg::OnBnClickedBookQuery2()//用户借阅书籍查询
{
	// TODO: 在此添加控件通知处理程序代码
	//顾名扬完成
	MYSQL_RES* m_res;
	connectsql(&m_sqlCon_client);
	USES_CONVERSION;
	sprintf_s(query_client, "select book_id,book_name,book_author,book_publisher,book_state"
		" from user_account,students，book, record "
		"where S_id = user_id AND user_id = id_user AND book_state = '被借阅';");
	mysql_query(&m_sqlCon_client, query_client);
	m_res = mysql_store_result(&m_sqlCon_client);
	c_list2.DeleteAllItems();
	this->showdata2(m_res);
	mysql_close(&m_sqlCon_client);
}


void CDBwork_userDlg::OnBnClickedReturnback2()//借阅书籍归还
{
	// TODO: 在此添加控件通知处理程序代码
	//顾名扬完成
	int nIndex = c_list2.GetSelectionMark();   //获取查询框选中行的行号
	CString s_id = c_list2.GetItemText(nIndex, 0);   //获取查询框第0列内容
	CString s_state = c_list2.GetItemText(nIndex, 4);   //获取查询框第4列内容
	MYSQL_RES* m_res;
	connectsql(&m_sqlCon_client);
	USES_CONVERSION;
	char* m_id = T2A(s_id);
	char* m_state = T2A(s_state);
	sprintf_s(query_client, "UPDATE book "
		"SET book_state='在册' "
		"where book_id=%s;", m_id);
	if (mysql_query(&m_sqlCon_client, query_client))
	{
		AfxMessageBox(TEXT("归还书籍失败，请重新尝试！"));
		mysql_close(&m_sqlCon_client);
		return;
	}
	if (s_state == "在册")
	{
		AfxMessageBox(TEXT("此书已被归还，请勿重复尝试！"));
		mysql_close(&m_sqlCon_client);
		return;
	}
	else {
		AfxMessageBox(TEXT("归还成功！"));
		mysql_close(&m_sqlCon_client);
		return;
	}
}
