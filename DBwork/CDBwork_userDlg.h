#pragma once
#include "afxdialogex.h"


// CDBwork_userDlg 对话框

class CDBwork_userDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDBwork_userDlg)

public:
	CDBwork_userDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDBwork_userDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_user };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
