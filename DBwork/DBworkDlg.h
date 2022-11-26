
#pragma once


// CDBworkDlg 对话框
class CDBworkDlg : public CDialogEx
{
// 构造
public:
	CDBworkDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DBWORK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonconnect();
	afx_msg void OnBnClickedButtonenter();
	CString m_num;
	CString m_pass;
	//static CDBworkDlg* pCDBworkDlg;
	
};
