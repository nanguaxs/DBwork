﻿// paperDlg.cpp: 实现文件
//

#include "pch.h"
#include "DBwork.h"
#include "afxdialogex.h"
#include "paperDlg.h"
#include"sql.h"

// paperDlg 对话框

IMPLEMENT_DYNAMIC(paperDlg, CDialogEx)
MYSQL sql_paper;
char query_paper[1024];
paperDlg::paperDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

paperDlg::~paperDlg()
{
}

void paperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_list);
}


BEGIN_MESSAGE_MAP(paperDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON4, &paperDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &paperDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &paperDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// paperDlg 消息处理程序


void paperDlg::OnBnClickedButton4()//查询
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.DeleteAllItems();
	connectsql(&sql_paper);
	CString id, name, author;
	GetDlgItem(IDC_EDIT7)->GetWindowText(id);
	GetDlgItem(IDC_EDIT8)->GetWindowText(name);
	GetDlgItem(IDC_EDIT9)->GetWindowText(author);
	USES_CONVERSION;
	char* m_name = T2A(name);
	char* m_id = T2A(id);
	char* m_author = T2A(author);
	if (id.IsEmpty()&&name.IsEmpty()&&author.IsEmpty()) {
		sprintf_s(query_paper, "select P_id,P_name,P_author,download"
			" from paper "
		);
	}
	else if (id.IsEmpty() && name.IsEmpty()) {
		sprintf_s(query_paper, "select P_id,P_name,P_author,download"
			" from paper "
			"where P_author like '%%%s%%'",m_author
		);
	}
	else if (id.IsEmpty() && author.IsEmpty()) {
		sprintf_s(query_paper, "select P_id,P_name,P_author,download"
			" from paper "
			"where P_name like '%%%s%%'", m_name
		);
	}
	else if (author.IsEmpty() && name.IsEmpty()) {
		sprintf_s(query_paper, "select P_id,P_name,P_author,download"
			" from paper "
			"where P_id  = %s", m_id
		);
	}
	else if (author.IsEmpty() ) {
		sprintf_s(query_paper, "select P_id,P_name,P_author,download"
			" from paper "
			"where P_id  = %s AND P_name like '%%%s%%'", m_id,m_name
		);
	}
	else if (name.IsEmpty()) {
		sprintf_s(query_paper, "select P_id,P_name,P_author,download"
			" from paper "
			"where P_id  = %s AND P_author like '%%%s%%'", m_id, m_author
		);
	}
	else if (id.IsEmpty()) {
		sprintf_s(query_paper, "select P_id,P_name,P_author,download"
			" from paper "
			"where P_author like '%%%s%%' AND P_name like '%%%s%%'", m_author, m_name
		);
	}
	else {
		sprintf_s(query_paper, "select P_id,P_name,P_author,download"
			" from paper "
			"where P_author like '%%%s%%' AND P_name like '%%%s%%' AND P_id = %s", m_author, m_name,m_id
		);
	}
	mysql_query(&sql_paper, query_paper);
	MYSQL_RES *m_res;
	m_res = mysql_store_result(&sql_paper);
	this->showdata(m_res);
	mysql_close(&sql_paper);
}


BOOL paperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_list.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加列   
	m_list.InsertColumn(0, _T("编号"), LVCFMT_CENTER, rect.Width() / 4, 0);
	m_list.InsertColumn(1, _T("名称"), LVCFMT_CENTER, rect.Width() / 4, 1);
	m_list.InsertColumn(2, _T("作者"), LVCFMT_CENTER, rect.Width() / 4, 2);
	m_list.InsertColumn(3, _T("下载次数"), LVCFMT_CENTER, rect.Width() / 4, 3);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


int paperDlg::showdata(MYSQL_RES* m_res)
{
	// TODO: 在此处添加实现代码.
	CString data[4];
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(m_res)) != NULL) {
		for (int i = 0; i < 4; i++) {
			data[i] = row[i];
		}
		m_list.InsertItem(0, data[0]);
		m_list.SetItemText(0, 1, data[1]);
		m_list.SetItemText(0, 2, data[2]);
		m_list.SetItemText(0, 3, data[3]);
		

	}
	return 0;
}


void paperDlg::OnBnClickedButton6()//上传
{
	// TODO: 在此添加控件通知处理程序代码
	CString id, name, author;
	MYSQL_RES* m_res;
	MYSQL_ROW m_row;
	GetDlgItem(IDC_EDIT10)->GetWindowText(id);
	GetDlgItem(IDC_EDIT11)->GetWindowText(name);
	GetDlgItem(IDC_EDIT12)->GetWindowText(author);
	USES_CONVERSION;
	char* m_name = T2A(name);
	char* m_id = T2A(id);
	char* m_author = T2A(author);
	connectsql(&sql_paper);
	sprintf_s(query_paper, "select P_id"
		" from paper "
		"where P_id = %s",  m_id
	);
	mysql_query(&sql_paper, query_paper);
	
	m_res = mysql_store_result(&sql_paper);
	m_row = mysql_fetch_row(m_res);
	if (m_row != NULL)
	{
		AfxMessageBox(TEXT("使用该编号的论文已存在！"));
		mysql_close(&sql_paper);
		return;
	}
	sprintf_s(query_paper, "INSERT INTO paper"
		" VALUES ('%s','%s','%s',0); "
		, m_id,m_name,m_author);
	if (mysql_query(&sql_paper, query_paper))
	{
		AfxMessageBox(TEXT("上传论文失败！"));
		mysql_close(&sql_paper);
		return;
	}
	sprintf_s(query_paper, "select P_id,P_name,P_author,download"
		" from paper "
	);
	mysql_query(&sql_paper, query_paper);
	m_res = mysql_store_result(&sql_paper);
	m_list.DeleteAllItems();
	this->showdata(m_res);
	AfxMessageBox(TEXT("上传论文成功！"));
	mysql_close(&sql_paper);


}


void paperDlg::OnBnClickedButton5()//论文下载
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_list.GetSelectionMark();   //获取选中行的行号
	CString P_id = m_list.GetItemText(nIndex, 0);   //获取第0列内容
	MYSQL_RES* m_res;
	MYSQL_ROW m_row;
	USES_CONVERSION;
	char* m_id = T2A(P_id);
	connectsql(&sql_paper);
	sprintf_s(query_paper, "select download"
		" from paper "
		"where P_id=%s",m_id
	);
	mysql_query(&sql_paper, query_paper);
	m_res = mysql_store_result(&sql_paper);
	m_row = mysql_fetch_row(m_res);
	int old = atoi(m_row[0]);
	int new_download = old + 1;
	sprintf_s(query_paper, "UPDATE paper"
		" SET download = %d "
		"where P_id=%s", new_download,m_id
	);
	if (mysql_query(&sql_paper, query_paper))
	{
		AfxMessageBox(TEXT("下载失败！"));
		mysql_close(&sql_paper);
		return;
	}
	sprintf_s(query_paper, "select P_id,P_name,P_author,download"
		" from paper "
	);
	mysql_query(&sql_paper, query_paper);
	m_res = mysql_store_result(&sql_paper);
	m_list.DeleteAllItems();
	this->showdata(m_res);
	AfxMessageBox(TEXT("下载成功！"));
	mysql_close(&sql_paper);
}
