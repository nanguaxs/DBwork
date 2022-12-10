#pragma once
#include "afxdialogex.h"
#include "sql.h"

// bookBorrowQuery 对话框

class bookBorrowQuery : public CDialogEx
{
	DECLARE_DYNAMIC(bookBorrowQuery)

public:
	bookBorrowQuery(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~bookBorrowQuery();
	char* user_id;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonQuery();
	CListCtrl c_list3;
	virtual BOOL OnInitDialog();
	void showdata( MYSQL_RES* m_res);
	afx_msg void OnBnClickedButtonReturn();
};