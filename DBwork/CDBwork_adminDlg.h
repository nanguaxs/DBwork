#pragma once
#include "afxdialogex.h"
#include"sql.h"

// CDBwork_adminDlg 对话框

class CDBwork_adminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDBwork_adminDlg)

public:
	CDBwork_adminDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDBwork_adminDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_admin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_id;
	CString m_name;

	virtual BOOL OnInitDialog();
	CListCtrl m_list;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	void showdata( MYSQL_RES* m_res);
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton5();
};
