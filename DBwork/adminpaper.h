#pragma once
#include "afxdialogex.h"
#include"sql.h"

// adminpaper 对话框

class adminpaper : public CDialogEx
{
	DECLARE_DYNAMIC(adminpaper)

public:
	adminpaper(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~adminpaper();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton4();
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	int showdata(MYSQL_RES* m_res);
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton1();
};
