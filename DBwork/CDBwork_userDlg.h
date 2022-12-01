#pragma once
#include "afxdialogex.h"
#include "sql.h"

// CDBwork_userDlg 对话框

class CDBwork_userDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDBwork_userDlg)

public:
	CDBwork_userDlg(CWnd* pParent = nullptr) ;   // 标准构造函数
	virtual ~CDBwork_userDlg();
	char *user_id;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_user };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public://顾名扬修改
	CString c_id;
	CString c_name;
	CString c_author;
	//CString c_publisher;
	//CString c_state;
	CListCtrl c_list;
	CListCtrl c_list2;
	void showdata( MYSQL_RES* m_res);
	void showdata2(MYSQL_RES* m_res);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnEnChangeEdit16();
	afx_msg void OnStnClickedBookId();
	afx_msg void OnBnClickedBookQuery();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEditBookId2();
	afx_msg void OnBnClickedDonation();
	afx_msg void OnEnChangeEditBookPublisher2();
	afx_msg void OnEnChangeEditBookAuthor2();
	afx_msg void OnEnChangeEditBookName2();
	afx_msg void OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedReturnback();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEditBookId();
	afx_msg void OnEnChangeEditBookName();
	afx_msg void OnEnChangeEditBookAuthor();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnBnClickedBorrow();
	afx_msg void OnStnClickedBookAuthor();
	afx_msg void OnBnClickedBookQuery2();
};
