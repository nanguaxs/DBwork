#pragma once
#include "afxdialogex.h"


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
};
