#pragma once
#include "afxdialogex.h"


// user 对话框

class user : public CDialogEx
{
	DECLARE_DYNAMIC(user)

public:
	user(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~user();
	char* user_id;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
