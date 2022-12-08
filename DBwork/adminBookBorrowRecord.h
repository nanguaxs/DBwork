#pragma once//顾名扬添加
#include "afxdialogex.h"
#include "sql.h"


// adminBookBorrowRecord 对话框

class adminBookBorrowRecord : public CDialogEx
{
	DECLARE_DYNAMIC(adminBookBorrowRecord)

public:
	adminBookBorrowRecord(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~adminBookBorrowRecord();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnBnClickedOk();
	//afx_msg void OnBnClickedOk2();
	virtual BOOL OnInitDialog();
	//CListCtrl m_list2;
	void showdata2(MYSQL_RES* m_res);
	afx_msg void OnEnChangeEditName2();
	afx_msg void OnEnChangeEditId2();
	afx_msg void OnEnChangeEditName1();
	afx_msg void OnEnChangeEditId1();
	CListCtrl m_list3;
	afx_msg void OnLvnItemchangedList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
