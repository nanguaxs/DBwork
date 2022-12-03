#pragma once
#include "afxdialogex.h"


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
};
