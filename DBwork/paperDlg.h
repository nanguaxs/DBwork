#pragma once
#include "afxdialogex.h"
#include"sql.h"

// paperDlg 对话框

class paperDlg : public CDialogEx
{
	DECLARE_DYNAMIC(paperDlg)

public:
	paperDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~paperDlg();
	char* user_id;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton4();
	virtual BOOL OnInitDialog();
	CListCtrl m_list;
	int showdata(MYSQL_RES* m_res);
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton5();
};
