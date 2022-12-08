#pragma once//顾名扬添加
#include "afxdialogex.h"
#include "sql.h"

// adminmanage 对话框

class adminmanage : public CDialogEx
{
	DECLARE_DYNAMIC(adminmanage)

public:
	adminmanage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~adminmanage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBookQuery();
	virtual BOOL OnInitDialog();
	CListCtrl m_list1;
	void showdata( MYSQL_RES* m_res);
	afx_msg void OnEnChangeEditBookId();
	afx_msg void OnEnChangeEditBookName();
	afx_msg void OnEnChangeEditBookAuthor();
	afx_msg void OnBnClickedDonation();
	afx_msg void OnBnClickedReturnback2();
	afx_msg void OnBnClickedBorrow();
};
